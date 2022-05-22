<template>
  <div id="content">
    <div class="container-fluid">
      <div class="row">
        <div class="col-3">
<!--          <Menu></Menu>-->
        </div>
        <div class="col-12 board-frame">
          <div>
            <Board></Board>
            <Flag v-if="boardStore.init" :name="'將'" :x="3" :y="0" :color="'black'" :special-style="{}" />
            <Hint v-if="boardStore.init" :x="4" :y="0" />
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
import { useBoardStore } from "../store/Game/board";
import { defineComponent, ref } from 'vue-demi';

export default defineComponent({
  name: "game",
  data() {
    return {}
  },
  setup() {
    const boardStore = ref(useBoardStore());
    return {
      boardStore
    }
  },
  components: {
    Board,
    Menu,
    Flag,
    Hint
  }
})
</script>
<style scoped>

</style>