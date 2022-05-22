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
            <Flag v-if="boardStore.init" :name="'將'" :x="0" :y="0" :color="'black'" :special-style="{}"></Flag>
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

import pinia from "../store/store";
import { useBoardStore } from "../store/Game/board";
import { defineComponent, ref } from 'vue-demi'

export default defineComponent({
  name: "game",
  data() {
    return {}
  },
  setup() {
    const boardStore = ref(useBoardStore(pinia));
    return {
      boardStore
    }
  },
  components: {
    Board,
    Menu,
    Flag
  }
})
</script>
<style scoped>

</style>