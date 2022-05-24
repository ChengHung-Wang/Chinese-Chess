<template>
  <div class="container">
    <div class="row">
      <div class="col-12 mb-4">
        <h3>遊戲結束</h3>
      </div>
      <div class="col-4 fcc">
        <div>
          <h5 class="mb-3 text-center">{{ gameStore.modal }}</h5>
          <Flag v-if="gameStore.winner == 1" :x="-1" :y="-1" :special-style="{}" color="red" name="帥"/>
          <Flag v-if="gameStore.winner == 2" :x="-1" :y="-1" :special-style="{}" color="black" name="將"/>
        </div>
      </div>
      <div class="col-8">
        <div class="row">
          <div class="col-12">
            <h4>雙方剩餘時間</h4>
            <hr>
          </div>
          <div class="col-6">
            <h6 class="text-secondary">黑方剩餘時間：{{ gameStore.bTime }}</h6>
          </div>
          <div class="col-6">
            <h6 class="text-danger">紅方剩餘時間：{{ gameStore.rTime }}</h6>
          </div>
        </div>
        <div class="row">
          <div class="col-4">
            <el-button type="primary" icon="el-icon-refresh" class="w-100" plain>再來一局</el-button>
          </div>
          <div class="col-4">
            <el-button type="primary" icon="el-icon-video-play" class="w-100" plain>重放遊戲</el-button>
          </div>
          <div class="col-4">
            <el-button type="primary" icon="el-icon-close" class="w-100" plain>結束程式</el-button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { defineComponent, ref } from 'vue-demi'
import { useGameStore } from "../../store/game"
import Flag from "./Flag";

export default defineComponent({
  name: "records",
  setup() {
    const gameStore = ref(useGameStore());
    return {
      gameStore
    }
  },
  components: {
    Flag
  },
  props: {

  }
});
</script>
<style scoped>
  .col-4 {
    border-right: .1px rgba(0, 0, 0, .1) solid;
  }
</style>