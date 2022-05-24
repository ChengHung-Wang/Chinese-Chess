<template>
  <div id="content">
    <div class="container-fluid" v-loading="gameStore.loading">
      <div class="row">
        <div class="col-3">
          <Menu></Menu>
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
import { useGameStore } from "../store/game";
import { useBoardStore } from "../store/Game/board";
import { defineComponent, ref } from 'vue-demi';

export default defineComponent({
  name: "game",
  data() {
    return {}
  },
  setup() {
    const gameStore = ref(useGameStore());
    const boardStore = ref(useBoardStore());
    return {
      gameStore,
      boardStore
    }
  },
  created() {
    this.gameStore.loading = true;
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
    // animation
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
  components: {
    Board,
    Menu,
    Flag,
    Hint
  },
  methods: {
    // I don't have any more time to plan the architecture

    // ************************************
    // *************** API ****************
    // ************************************


  }
})
</script>
<style scoped>

</style>