<template>
  <div class="board">
    <div class="top">
      <div
          v-for="item in 8*4" class="cube"
          v-bind:style="boardStore.getCubePosition(boardStore.cubeSize, boardStore.cubeSize)">
      </div>
    </div>
    <div class="center fac" v-bind:style="{'height': boardStore.cubeSize + 'px'}">
      <h2 class="m-0">楚河</h2>
      <p class="m-0">基隆路四段</p>
      <h2 class="m-0">漢界</h2>
    </div>
    <div class="bottom">
      <div
          v-for="item in 8*4" class="cube"
          v-bind:style="boardStore.getCubePosition(boardStore.cubeSize, boardStore.cubeSize)">
      </div>
    </div>
  </div>
</template>

<script>
import { useBoardStore } from "@/store/Game/board"
import { defineComponent, ref } from 'vue-demi'

export default defineComponent({
  name: "board",
  mounted() {
    this.initBoardSize();
  },
  setup() {
    const boardStore = ref(useBoardStore());
    return {
      boardStore
    }
  },
  methods: {
    initBoardSize() {
      let boardBorder = this.boardStore.boardSize;
      // get board dom
      this.boardStore.boardDom = window.$(".board");
      // get board height
      this.boardStore.boardSize.height = this.boardStore.boardDom.height();
      // set every cube size
      this.boardStore.cubeSize = (((boardBorder.height - boardBorder.borderWidth) - (this.boardStore.padding * 2)) / 9);
      // set board width for store env
      this.boardStore.boardSize.width = (this.boardStore.cubeSize * 8 + boardBorder.borderWidth) + this.boardStore.padding * 2 + this.boardStore.boardSize.borderWidth;
      // set board width for dom
      this.boardStore.boardDom.css("width", this.boardStore.boardSize.width);
      // update init status info
      this.boardStore.init = true;
    }
  }
})
</script>
<style scoped>
  .board {
    border: 3px #606666 solid;
    height: calc(100vh - 120px);
    width: 100px;
    padding: 5px;
    display: flex;
    align-items: center;
    flex-wrap: wrap;
    margin-top: -15px;
  }
  .top, .bottom {
    display: flex;
    flex-wrap: wrap;
  }
  .top::before, .bottom::before {
    content: '';
    position: absolute;
    margin: 60px;
    width: calc(100% - 120px);
    height: calc(100% - 120px);
    background-size: contain;
    background-position: center;
    background-repeat: no-repeat;
    opacity: .5;
  }
  .top::before {
    background-image: url('../../assets/images/ntu.png');
  }
  .bottom::before {
    background-image: url('../../assets/images/ntust.png');
    transform: rotate(180deg);
  }
  .cube {
    border: 1px solid #606666;
  }
  .board> .center {
    width: 100%;
    text-align: center;
  }
</style>