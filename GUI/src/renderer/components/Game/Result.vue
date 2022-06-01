<template>
  <div class="container">
    <div class="row">
      <div class="col-4 fcc">
        <div>
          <h5 class="mb-3 text-center">{{ gameStore.modal }}</h5>
          <Flag v-if="gameStore.winner == 1" :x="-1" :y="-1" :special-style="{}" color="red" name="帥"/>
          <Flag v-if="gameStore.winner == 2" :x="-1" :y="-1" :special-style="{}" color="black" name="將"/>
        </div>
      </div>
      <div class="col-8">
        <h4>雙方剩餘時間</h4>
        <h6 class="text-secondary">黑方剩餘時間：{{ gameStore.bTime }}</h6>
        <h6 class="text-danger">紅方剩餘時間：{{ gameStore.rTime }}</h6>
        <hr>
        <div class="row">
          <div class="col-3">
            <el-button @click="replay()" class="w-100" type="primary" icon="el-icon-refresh" plain>再來一局</el-button>
          </div>
          <div class="col-3">
            <el-button @click="$emit('getLogs'); displayLogReplay = true" class="w-100" type="primary" icon="el-icon-video-play" plain>
              重放遊戲
            </el-button>
          </div>
          <div class="col-3">
            <el-button @click="$emit('save')" class="w-100" type="primary" icon="el-icon-download" plain>儲存狀態</el-button>
          </div>
          <div class="col-3">
            <el-button id="closeApp" class="w-100" type="primary" icon="el-icon-close" plain>結束程式</el-button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { defineComponent, ref } from 'vue-demi'
import { storeToRefs } from 'pinia'
import { useGameStore } from "../../store/game"
import Flag from "./Flag";

export default defineComponent({
  name: "records",
  setup() {
    const gameStore = ref(useGameStore());
    const { displayLogReplay } = storeToRefs(useGameStore());
    return {
      gameStore,
      displayLogReplay
    }
  },
  components: {
    Flag
  },
  props: {

  },
  mounted() {
    const {ipcRenderer} = require('electron');
    const closeApp = document.getElementById('closeApp');
    closeApp.addEventListener('click', () => {
      ipcRenderer.send('close-me')
    });
  },
  methods: {
    replay() {
      window.location.reload();
    }
  }
});
</script>
<style scoped>
  .col-4 {
    border-right: .1px rgba(0, 0, 0, .1) solid;
  }
  h5, h4, h3 {
    height: auto;
  }
  h4 {
    font-size: 1.5rem!important;
  }
  .row>* {
    padding-left: calc(var(--bs-gutter-x) * .5)!important;
    padding-right: calc(var(--bs-gutter-x) * .5)!important;
  }
</style>