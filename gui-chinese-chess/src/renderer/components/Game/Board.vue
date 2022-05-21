<template>
  <div style="height: 100vh">
    <div class="board">
      <div class="top">
        <div v-for="item in 8*4" class="cube" v-bind:style="{'width': cubeSize + 'px', 'height': cubeSize + 'px'}"></div>
      </div>
      <div class="center fac" v-bind:style="{'height': cubeSize + 'px'}">
        <h2 class="m-0">楚河</h2>
        <p class="m-0">基隆路四段</p>
        <h2 class="m-0">漢界</h2>
      </div>
      <div class="bottom">
        <div v-for="item in 8*4" class="cube" v-bind:style="{'width': cubeSize + 'px', 'height': cubeSize + 'px'}"></div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "board",
  data() {
    return {
      padding: 5,
      boradDom: null,
      boardSize: {
        width: null,
        height: null,
        borderWidth: 6
      },
      cubeSize: null
    }
  },
  mounted() {
    this.initBoardSize();
  },
  methods: {
    initBoardSize() {
      this.boradDom = window.$(".board");
      this.boardSize.height = this.boradDom.height();
      this.cubeSize = (((this.boardSize.height - this.boardSize.borderWidth) - (this.padding * 2)) / 9);
      this.boardSize.width = (this.cubeSize * 8) + this.padding * 2 + this.boardSize.borderWidth;
      this.boradDom.css("width", this.boardSize.width);
    }
  }
}
</script>
<style scoped>
  .board {
    border: 3px #606666 solid;
    position: absolute;
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
    height: calc(100vh - 60px);
    width: 100px;
    padding: 5px;
    display: flex;
    align-items: center;
    flex-wrap: wrap;
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
    opacity: .6;
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