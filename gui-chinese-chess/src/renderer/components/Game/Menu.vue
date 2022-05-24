<template>
  <el-menu
      default-active="2"
      class="el-menu-vertical-demo">
    <el-menu-item class="fsc" index="1">
      <img class="mt-3 mb-3" style="height: 60px; width: 60px" src="../../assets/icon.png" />
      <p class="m-0" style="margin-left: 15px!important; font-size: 18px;">1102 - OOP<br>Chinese Chess</p>
    </el-menu-item>
    <el-menu-item index="2" @click="$router.push('/')">
      <i class="el-icon-s-home"></i>
      <span slot="title">返回首頁</span>
    </el-menu-item>
    <el-menu-item index="3">
      <i class="el-icon-circle-close"></i>
      <span slot="title">投降</span>
    </el-menu-item>
    <el-menu-item index="4">
      <i class="el-icon-download"></i>
      <span slot="title">儲存狀態</span>
    </el-menu-item>
    <el-menu-item index="5">
      <i class="el-icon-refresh-right"></i>
      <span slot="title">查看日誌</span>
    </el-menu-item>
    <hr>
    <el-menu-item index="6">
      <el-switch
          v-model="gameStore.displayHint"
          active-text="顯示提示"
          inactive-text="">
      </el-switch>
    </el-menu-item>
    <el-menu-item>
      <el-button class="w-100 m-0" type="info">剩餘時間：{{ gameStore.bTime }}秒</el-button>
      <el-button class="w-100 m-0" type="danger">剩餘時間：{{ gameStore.rTime }}秒</el-button>
    </el-menu-item>
  </el-menu>
</template>
<style scoped>
  .el-menu {
    min-height: 100vh;
    position: relative;
  }
  .el-menu-item {
    padding-left: 10px;
    height: 100%;
  }
  .el-menu-item:last-child {
    position: absolute;
    bottom: 15px;
    width: 100%;
    height: 100px;
    display: flex;
    align-items: center;
    justify-content: flex-start;
    flex-wrap: wrap;
    cursor: unset;
  }
  .el-menu-item button {
    cursor: unset;
  }
  p {
    line-height: 1;
  }
</style>
<script>
  import { useGlobalStore } from "../../store/global";
  import { useGameStore } from "../../store/game"
  import { ref, defineComponent } from "vue-demi"

  export default defineComponent({
    name: "game-menu",
    setup() {
      const globalStore = ref(useGlobalStore());
      const gameStore = ref(useGameStore());
      return {
        globalStore,
        gameStore
      }
    },
    methods: {

    }
  })
</script>
