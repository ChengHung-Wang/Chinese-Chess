<template>
  <div id="content">
    <div class="container-fluid game"
         v-loading="gameStore.loading"
         v-bind:class="{'play-meme': memePlay}"
         :element-loading-text="gameStore.loadingText">
      <div class="row">
        <div class="col-3">
          <Menu @giveUp="giveUp" @save="save" />
        </div>
        <div class="col-9 board-frame">
          <div>
            <Board />
            <Flag
                v-if="boardStore.init && item.disabled === undefined"
                v-for="item in gameStore.flags"
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
              <Result @save="save" @getLogs="getLogs" />
            </el-dialog>
            <el-dialog title="Log Replay" :visible.sync="displayLogReplay" :fullscreen="true">
              <Records />
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
import Records from "./Game/Records";
import { storeToRefs } from 'pinia';
import { useGlobalStore } from "../store/global";
import { useGameStore } from "../store/game";
import { useBoardStore } from "../store/Game/board";
import { useRecordsStore } from "../store/Game/records";
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
    const recordsStore = ref(useRecordsStore());
    const { memePlay, displayLogReplay, smartMode, loading } = storeToRefs(useGameStore());
    const { logs } = storeToRefs(useRecordsStore());
    return {
      globalStore,
      gameStore,
      boardStore,
      recordsStore,
      memePlay,
      displayLogReplay,
      logs,
      loading,
      smartMode
    }
  },
  components: {
    Board,
    Menu,
    Flag,
    Hint,
    Result,
    Records
  },
  created() {
    this.gameStore.loading = true;
    this.gameStore.stop = true;
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
      const backup = JSON.parse(JSON.stringify(this.gameStore.flags));
      this.gameStore.flags = JSON.parse(JSON.stringify(this.gameStore.flags.map(e => {
        if (e.color == 'black') {
          e.x = 4;
          e.y = 0;
        }else {
          e.x = 4;
          e.y = 9;
        }
        return e;
      })));
      // init
      setTimeout(async () => {
        clearInterval(this.loopEnv);
        this.gameStore.flags = JSON.parse(JSON.stringify(backup));
        this.gameStore.stop = false;
        this.loopEvent();
        await this.getRound();
      }, 2000);
    }
  },
  methods: {
    // I don't have any more time to plan the architecture
    receiveData(response) {
      try {
        const data = JSON.parse(this.globalStore.responseStringCache + response);
        let thisResponseIndex = this.globalStore.responseStacks.map(e => e.token).indexOf(data.hash);
        if (thisResponseIndex > -1 && !this.globalStore.responseStacks[thisResponseIndex].completed) {
          this.globalStore.responseStringCache = "";
          this.globalStore.responseStacks[thisResponseIndex].completed = true;
          this.globalStore.responseStacks[thisResponseIndex].callback(data);
        }
      }catch (e) {
        this.globalStore.responseStringCache += response; // push some json string to cache
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

      await this.globalStore.waitAllReqCompleted();

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

      await this.globalStore.waitAllReqCompleted();

      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: async (response) => {
          /*
            move": {
              "id": 2,
              "fromX": 0,
              "fromY": 0,
              "toX": 1,
              "toY": 1,
              "uni": 1
            },
            "delete": {
              "id": 2,
              "x": 3,
              "y": 0,
              "uni": 1
            }
          */
          // remove flag
          if (response.delete) {
            this.gameStore.flags = JSON.parse(JSON.stringify(this.gameStore.flags.map(flag => {
              if (flag.uni === response.delete.uni) {
                flag.disabled = true;
              }
              return flag;
            })));
          }

          // change flag position
          if (response.move) {
            this.gameStore.flags[this.gameStore.flags.map(e => e.uni).indexOf(response.move.uni)].x = response.move.toX;
            this.gameStore.flags[this.gameStore.flags.map(e => e.uni).indexOf(response.move.uni)].y = response.move.toY;
            this.gameStore.selectedFlag = {x: null, y: null, uni: null};
          }

          // update actionAble
          this.gameStore.actionAble = response.color;
          // update winner
          this.gameStore.winner = response.winner;
          // update modal
          this.gameStore.modal = response.modal;
          // update mate
          this.gameStore.mate = response.checkmate;
          if (this.gameStore.mate > 0) {
            this.$message({
              message: `${this.gameStore.modal}`,
              type: 'warning',
              showClose: true
            });
          }
          if (this.smartMode && this.gameStore.actionAble === 2) {
            this.gameStore.loadingText = "智能引擎思考中"
            this.loading = true;
            setTimeout(async () => {
              await this.smartMove();
            }, 1500);
          }else {
            // hide loading animation
            this.loading = false;
          }
        }
      });
    },
    async getMove(position) {
      // getMove {hash} {x} {y} {uni}
      await this.globalStore.waitAllReqCompleted();
      const thisFlag = this.gameStore.flags[this.gameStore.getFlagIndex(position.x, position.y, position.uni)];
      if (this.gameStore.actionAble == 0 || thisFlag.color != this.gameStore.getNumColor(this.gameStore.actionAble)) {
        // this.$notify({
        //   title: 'flag not valid in gatMove',
        //   message: `thisFlag.color: ${thisFlag.color}, getNumColor: ${this.gameStore.getNumColor(this.gameStore.actionAble)}, actionAble: ${this.gameStore.actionAble}`,
        //   position: 'bottom-left'
        // });
        this.$message.error("不可移動的棋子");
        return ;
      }else {
        // this.$notify({
        //   title: 'getMove debug',
        //   message: `(${position.x}, ${position.y}) uni: ${position.uni}`,
        //   position: 'bottom-left'
        // });
        this.gameStore.selectedFlag = {
          x: position.x,
          y: position.y,
          uni: position.uni
        };
      }
      let token = this.globalStore.getHash();
      // let commend = `getMove ${token} ${thisFlag.x} ${thisFlag.y}`;
      let commend = `getMove ${token} ${position.uni}`;
      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
            completed: false,
            token: token,
            result: null,
            callback: (response) => {
              this.gameStore.moveAble = response.canMove;
              this.gameStore.replaceAble = response.canEat;
            }
      })
    },
    async move(position) {
      let beforePosition = this.gameStore.selectedFlag;
      let token = this.globalStore.getHash();
      let commend = `move ${token} ${beforePosition.x} ${beforePosition.y} ${position.x} ${position.y}`;

      await this.globalStore.waitAllReqCompleted();

      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: async (response) => {
          await this.getRound();
          this.gameStore.moveAble = [];
          this.gameStore.replaceAble = [];
        }
      })
    },
    async save() {
      let token = this.globalStore.getHash();
      let commend = `save ${token}`;

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
    },
    async getLogs() {
      let token = this.globalStore.getHash();
      let commend = `logs ${token}`;

      await this.globalStore.waitAllReqCompleted();

      this.globalStore.process.stdin.write(commend + '\n');
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: async (response) => {
          this.logs = response.logs;
        }
      });
    },
    async smartMove() {
      this.gameStore.loading = true;
      let token = this.globalStore.getHash();
      let commend = `moveRandom ${token}`;

      await this.globalStore.waitAllReqCompleted();

      this.globalStore.process.stdin.write(commend + '\n');
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: async (response) => {
          console.log(response);
          // remove flag
          if (response.delete) {
            this.gameStore.flags = JSON.parse(JSON.stringify(this.gameStore.flags.map(flag => {
              if (flag.uni === response.delete.uni) {
                flag.disabled = true;
              }
              return flag;
            })));
          }

          // change flag position
          if (response.move) {
            this.gameStore.flags[this.gameStore.flags.map(e => e.uni).indexOf(response.move.uni)].x = response.move.toX;
            this.gameStore.flags[this.gameStore.flags.map(e => e.uni).indexOf(response.move.uni)].y = response.move.toY;
            this.gameStore.selectedFlag = {x: null, y: null, uni: null};
          }

          // update actionAble
          this.gameStore.actionAble = response.color;
          // update winner
          this.gameStore.winner = response.winner;
          // update modal
          this.gameStore.modal = response.modal;
          // update mate
          this.gameStore.mate = response.checkmate;
          if (this.gameStore.mate > 0) {
            this.$message({
              message: `${this.gameStore.modal}`,
              type: 'warning',
              showClose: true
            });
          }
          // hide loading animation
          this.gameStore.loading = false;
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