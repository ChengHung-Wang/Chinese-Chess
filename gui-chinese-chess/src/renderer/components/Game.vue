<template>
  <div id="content">
    <div class="container-fluid game" v-loading="gameStore.loading" v-bind:class="{'play-meme': memePlay}">
      <div class="row">
        <div class="col-3">
          <Menu @giveUp="giveUp" @save="save"/>
        </div>
        <div class="col-9 board-frame">
          <div>
            <Board />
            <Flag
                v-if="boardStore.init"
                v-for="item in gameStore.flags"
                :name="item.name"
                :x="item.x" :y="item.y" :color="item.color"
                :special-style="item.specialStyle">
            </Flag>
            <Hint v-if="boardStore.init" v-for="item in hints" :x="item.x" :y="item.y" />
            <el-dialog
                title="遊戲結束"
                :visible.sync="gameStore.winner != 0"
                :show-close="false"
                width="80%">
              <Result @save="save" />
            </el-dialog>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Menu from "./Game/Menu";
import Board from "./Game/Board";
import Flag from "./Game/Flag";
import Hint from "./Game/Hint";
import Result from "./Game/Result";
import { storeToRefs } from 'pinia';
import { useGlobalStore } from "../store/global";
import { useGameStore } from "../store/game";
import { useBoardStore } from "../store/Game/board";
import { defineComponent, ref } from 'vue-demi';

export default defineComponent({
  name: "game",
  data() {
    return {
      loopEnv: null
    }
  },
  setup() {
    const globalStore = ref(useGlobalStore());
    const gameStore = ref(useGameStore());
    const boardStore = ref(useBoardStore());
    const { memePlay, hints } = storeToRefs(useGameStore());
    return {
      globalStore,
      gameStore,
      boardStore,
      memePlay,
      hints
    }
  },
  components: {
    Board,
    Menu,
    Flag,
    Hint,
    Result
  },
  created() {
    this.gameStore.loading = true;
    this.gameStore.stop = true;
    console.log('enter Game.vue created');
    this.globalStore.process.stdout.on("data", (response) => {
      this.receiveData(response);
    })
    // no data
    if (this.gameStore.flags.length == 0) {
      this.gameStore.stop = true;
      clearInterval(this.loopEnv);
      this.globalStore.process.stdout.removeAllListeners();
      this.$router.push("/");
    }else {
      if (! this.gameStore.flagsHasInit) {
        this.gameStore.flags = this.gameStore.flags.map(e => {
          let result = e;
          result.specialStyle = {};
          result.color = this.gameStore.getNumColor(result.color);
          if (result.name == '帥') {
            result.specialStyle.animation = "faceMeme 1s steps(1, end) infinite";
            result.specialStyle.fontWeight = "900";
          }else {
            result.specialStyle.animation = "unset";
          }
          return result;
        })
      }
      // flag animation
      const backup = JSON.parse(JSON.stringify(this.gameStore.flags));
      this.gameStore.flags = this.gameStore.flags.map(e => {
        if (e.color == 'black') {
          e.x = 4;
          e.y = 0;
        }else {
          e.x = 4;
          e.y = 9;
        }
        return e;
      })
      setTimeout(() => {
        clearInterval(this.loopEnv);
        this.gameStore.flags = backup;
        this.gameStore.loading = false;
        this.gameStore.stop = false;
        this.loopEvent();
      }, 1000);
      // init
      // TODO: getRound
    }
  },
  methods: {
    // I don't have any more time to plan the architecture
    receiveData(response) {
      const data = JSON.parse(response);
      let thisResponseIndex = this.globalStore.responseStacks.map(e => e.token).indexOf(data.hash);
      if (thisResponseIndex > -1 && !this.globalStore.responseStacks[thisResponseIndex].completed) {
        this.globalStore.responseStacks[thisResponseIndex].completed = true;
        this.globalStore.responseStacks[thisResponseIndex].callback(data);
      }
      console.log('receiveData in Game.vue', response);
    },
    loopEvent() {
      this.loopEnv = setInterval(() => {
          if (! this.gameStore.stop && this.gameStore.winner == 0) {
            this.getTime();
          }
      }, 1000);
    },
    // ************************************
    // *************** API ****************
    // ************************************
    getTime() {
      let token = this.globalStore.getHash();
      let commend = `getTime ${token}`;
      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: (response) => {
          this.gameStore.rTime = response.rTime;
          this.gameStore.bTime = response.bTime;
        }
      });
    },
    giveUp() {
      let token = this.globalStore.getHash();
      let commend = `giveUp ${token}`;
      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: (response) => {
          this.gameStore.modal = response.modal;
          this.gameStore.winner = response.winner;
        }
      });
    },
    async getRound() {
      let token = this.globalStore.getHash();
      let commend = `getRound ${token}`;

      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: (response) => {
          // remove flag
          if (response.delete) {
            this.gameStore.flags = this.gameStore.flags.filter(flag => {
              return !(flag.x == response.delete.x && flag.y == response.delete.y);
            })
          }
          // change flag position
          if (response.move) {
            const changeId = this.gameStore.flags.map(flag => {
              return {
                x: flag.x,
                y: flag.y
              }
            }).indexOf({
              x: response.move.fromX,
              y: response.move.fromY
            });
            // find target
            if (changeId > -1) {
              this.gameStore.flags[changeId].x = response.move.ToX;
              this.gameStore.flags[changeId].y = response.move.ToY;
            }
          }
          // update actionAble
          this.gameStore.actionAble = response.color;
          // update winner
          this.gameStore.winner = response.winner;
          // update modal
          this.gameStore.modal = response.modal;
          // update mate
          this.gameStore.mate = response.mate;
          if (this.gameStore.mate > 0) {
            this.$message({
              message: `${this.gameStore.getNumColor(this.gameStore.mate)}方 ${this.gameStore.modal}`,
              type: 'warning',
              showClose: true
            });
          }

        }
      });
    },
    async getMove() {
      // getMove {hash} {x} {y}
      /*
        {
          "canMove": [ //可以移動的位置
            {
              "x": 1,
              "y": 1
            },
            {
              "x": 2,
              "y": 2
            }..
          ],
          "canEat": [ //可以吃的子的位置
            {
              "x": 1,
              "y": 1,
            },
            {
              "x": 2,
              "y": 2
            }
          ],
          "hash": "hash"
          }
      */
    },
    async save() {
      let token = this.globalStore.getHash();
      let commend = `save ${token}`;
      this.globalStore.process.stdin.write(commend + '\n');
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: async (response) => {
          const content = response.content;
          const saveResult = await this.globalStore.downloadFile("status.txt", content);
          if (saveResult) {
            this.$message({
              showClose: true,
              message: '成功儲存遊戲狀態',
              type: 'success'
            });
          }
        }
      });
    }
  },
  async beforeRouteLeave(to, from, next) {
    await new Promise(resolve => {
      const timeOut = setTimeout(() => {
        // force complete all response
        this.globalStore.responseStacks.map(e => {
          e.completed = true;
          clearTimeout(timeOut);
          clearInterval(interval);
          resolve();
        });
      }, this.globalStore.apiTimeOut);
      const interval = setInterval(() => {
        // if all api has response
        if (this.globalStore.checkAllSet) {
          clearInterval(interval);
          clearTimeout(timeOut);
          resolve();
        }
      }, 50);
      if (this.globalStore.checkAllSet) {
        clearInterval(interval);
        clearTimeout(timeOut);
        resolve();
      }
    });
    this.gameStore.stop = true;
    clearInterval(this.loopEnv);
    this.globalStore.process.stdout.removeAllListeners();
    console.log("Completed: action beforeRouteLeave in Game.vuw");
    next();
  }
})
</script>