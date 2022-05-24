<template>
  <div id="content">
    <div class="container-fluid game" v-loading="gameStore.loading" v-bind:class="{'play-meme': memePlay}">
      <div class="row">
        <div class="col-3">
          <Menu @giveUp="giveUp"></Menu>
        </div>
        <div class="col-9 board-frame">
          <div>
            <Board></Board>
            <Flag
                v-if="boardStore.init"
                v-for="item in gameStore.flags"
                :name="item.name"
                :x="item.x" :y="item.y" :color="item.color"
                :special-style="item.specialStyle">
            </Flag>
            <Hint v-if="boardStore.init" v-for="item in gameStore.flags" :x="item.x" :y="item.y" />
            <el-dialog
                title="遊戲結束"
                :visible.sync="gameStore.winner != 0"
                width="80%">
              <Result></Result>
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
    return {}
  },
  setup() {
    const globalStore = ref(useGlobalStore());
    const gameStore = ref(useGameStore());
    const boardStore = ref(useBoardStore());
    const { memePlay } = storeToRefs(useGameStore());
    return {
      globalStore,
      gameStore,
      boardStore,
      memePlay,
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
    this.globalStore.process.stdout.on("data", (response) => {
      this.receiveData(response);
    })
    if (this.gameStore.flags.length == 0) {
      this.$router.push("/");
    }else {
      this.gameStore.flags = this.gameStore.flags.map(e => {
        let result = e;
        result.specialStyle = {};
        if (result.color == 2) {
          result.color = 'black';
        }else {
          result.color = 'red';
        }
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
      this.gameStore.flags = backup;
      this.gameStore.loading = false;
    }, 1000);
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
      console.log('receiveData in Game.vue');
    },
    // ************************************
    // *************** API ****************
    // ************************************
    getTime() {

    },
    giveUp() {
      let token = this.globalStore.getHash();
      let commend = `setNew ${token}`;
      this.globalStore.process.stdin.write(commend + '\n');
      this.gameStore.flagToken = token;
      this.globalStore.responseStacks.push({
        completed: false,
        token: token,
        result: null,
        callback: (response) => {
          // this.gameStore.flagToken = response.hash;
          // this.gameStore.flags = response.chess;
          // this.gameStore.rTime = response.rTime;
          // this.gameStore.bTime = response.bTime;
        }
      });
      console.log('giveUp');
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
    this.globalStore.process.stdout.removeListener('data', this.receiveData);
    next();
  }
})
</script>