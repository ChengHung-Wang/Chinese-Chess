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
                v-if="boardStore.init && item.disabled === undefined"
                v-for="item in flags"
                :name="item.name"
                :x="item.x" :y="item.y" :color="item.color" :uni="item.uni"
                :special-style="item.specialStyle"
                @click.native="item.disabled === undefined && getMove({x: item.x, y: item.y, uni: item.uni})">
            </Flag>
            <Hint v-if="boardStore.init" v-for="item in hints()" :x="item.x" :y="item.y" @click.native="move({x: item.x, y: item.y, uni: item.uni})" />
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
<style scoped>
  .row> *:last-child {
    padding-right: 0;
  }
  .row> *:first-child {
    padding-left: 0;
  }
</style>
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
    const { memePlay, flags } = storeToRefs(useGameStore());
    return {
      globalStore,
      gameStore,
      boardStore,
      memePlay,
      flags
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
    this.globalStore.process.stdout.on("data", (response) => {
      this.receiveData(response);
    })
    // no data
    if (this.flags.length == 0) {
      this.gameStore.stop = true;
      clearInterval(this.loopEnv);
      this.globalStore.process.stdout.removeAllListeners();
      this.$router.push("/");
    }else {
      if (! this.gameStore.flagsHasInit) {
        this.flags = this.flags.map(e => {
          let result = e;
          result.specialStyle = {
            'pointer-events': "auto"
          };
          result.color = this.gameStore.getNumColor(result.color);
          if (result.name == '帥') {
            result.specialStyle.animation = "faceMeme 1s steps(1, end) infinite";
            result.specialStyle.fontWeight = "900";
          }else {
            result.specialStyle.animation = "unset";
          }
          result.specialStyle.zIndex = 1;
          result.specialStyle.opacity = 1;
          return result;
        })
      }
      // flag animation
      const backup = JSON.parse(JSON.stringify(this.flags));
      this.flags = this.flags.map(e => {
        if (e.color == 'black') {
          e.x = 4;
          e.y = 0;
        }else {
          e.x = 4;
          e.y = 9;
        }
        return e;
      });
      // init
      setTimeout(async () => {
        clearInterval(this.loopEnv);
        this.flags = backup;
        this.gameStore.stop = false;
        this.loopEvent();
        await this.getRound();
      }, 1000);
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
        console.log(data);
      }
    },
    loopEvent() {
      this.loopEnv = setInterval(() => {
          if (! this.gameStore.stop && this.gameStore.winner == 0) {
            this.getTime();
          }
      }, 1000);
    },
    hints() {
      let result = [];
      if (Array.isArray(this.gameStore.moveAble)) {
        this.gameStore.moveAble.forEach(e => {
          result.push({
            x: e.x,
            y: e.y
          });
        })
      }
      if (Array.isArray(this.gameStore.replaceAble)) {
        this.gameStore.moveAble.forEach(e => {
          result.push({
            x: e.x,
            y: e.y
          });
        })
      }
      return Array.from(new Set(result)); // bring each item is unique in Array by ES6
    },
    // ************************************
    // *************** API ****************
    // ************************************
    async getTime() {
      let token = this.globalStore.getHash();
      let commend = `getTime ${token}`;
      console.log(commend);
      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: (response) => {
          this.gameStore.rTime = response.rTime;
          this.gameStore.bTime = response.bTime;
          this.gameStore.modal = response.modal;
          this.gameStore.winner = response.winner;
        }
      });
    },
    async giveUp() {
      let token = this.globalStore.getHash();
      let commend = `giveUp ${token}`;
      console.log(commend);

      await this.globalStore.waitAllReqCompleted();

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
      console.log(commend);

      await this.globalStore.waitAllReqCompleted();

      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: (response) => {
          // change flag position
          if (response.move) {
            const changeId = this.gameStore.getFlagIndex(response.move.fromX, response.move.fromY, response.uni);
            // remove flag
            if (response.delete) {
              const removeID = this.gameStore.getFlagIndex(response.delete.x, response.delete.y, response.uni);
              // if (removeID > -1) {
              //   let targetRemoveFlag = this.flags[removeID];
              //   if (targetRemoveFlag.uni == response.delete.uni) {
              //     debugger;
              //     this.flags[removeID].specialStyle.zIndex = -1;
              //     this.flags[removeID].specialStyle.opacity = 0;
              //     this.flags[removeID].specialStyle.pointerEvents = "none";
              //     this.flags[removeID].specialStyle.background = "green";
              //     this.flags[removeID].disabled = true;
              //   }
              // }
              this.flags[removeID].disabled = true;
              // this.flags = this.flags.map(flag => {
              //   flag = JSON.parse(JSON.stringify(flag));
              //   if (flag.uni === response.delete.uni) {
              //     flag.specialStyle.pointerEvents = "none";
              //     flag.specialStyle.display = "none";
              //     flag.specialStyle.zIndex = -1;
              //     setTimeout(() => {
              //       flag.disabled = true;
              //     }, 500);
              //   }else {
              //     flag.specialStyle.pointerEvents = "auto";
              //     flag.specialStyle.display = "flex";
              //     flag.specialStyle.zIndex = 2;
              //   }
              //   return flag;
              // })

            }
            if (changeId > -1) {
              if (this.flags[changeId].uni == response.move.uni) {
                // find target
                this.flags[changeId].x = response.move.toX;
                this.flags[changeId].y = response.move.toY;
              }
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
          // hide loading animation
          this.gameStore.loading = false;
        }
      });
    },
    async getMove(position) {
      // getMove {hash} {x} {y} {uni}
      console.log(position);
      const thisFlag = this.flags[this.gameStore.getFlagIndex(position.x, position.y, position.uni)];

      if (this.gameStore.actionAble == 0 || thisFlag.color != this.gameStore.getNumColor(this.gameStore.actionAble)) {
        this.$message.error("不可移動的棋子");
        return ;
      }else {
        this.gameStore.selectedFlag = {
          x: thisFlag.x,
          y: thisFlag.y,
          uni: thisFlag.uni
        };
      }
      let token = this.globalStore.getHash();
      // let commend = `getMove ${token} ${thisFlag.x} ${thisFlag.y}`;
      let commend = `getMove ${token} ${position.uni}`;
      console.log(commend);

      await this.globalStore.waitAllReqCompleted();

      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
            completed: false,
            token: token,
            result: null,
            callback: (response) => {
              // console.log('run getMove callback');
              this.gameStore.moveAble = response.canMove;
              this.gameStore.replaceAble = response.canEat;
            }
      })
    },
    async move(position) {
      let beforePosition = this.gameStore.selectedFlag;
      let token = this.globalStore.getHash();
      let commend = `move ${token} ${beforePosition.x} ${beforePosition.y} ${position.x} ${position.y}`;
      console.log(commend);
      await this.globalStore.waitAllReqCompleted();
      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: async (response) => {
          console.log(response, 'move callback')
          await this.getRound();
          this.gameStore.moveAble = [];
          this.gameStore.replaceAble = [];
        }
      })
    },
    async save() {
      let token = this.globalStore.getHash();
      let commend = `save ${token}`;
      console.log(commend);

      await this.globalStore.waitAllReqCompleted();

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
    this.gameStore.stop = true;
    this.gameStore.reset();
    clearInterval(this.loopEnv);
    await this.globalStore.waitAllReqCompleted(true);
    this.globalStore.process.stdout.removeAllListeners();
    console.log("Completed: action beforeRouteLeave in Game.vue");
    next();
  }
})
</script>