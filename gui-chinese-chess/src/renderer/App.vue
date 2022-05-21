<template>
  <div id="app">
    <transition name="fade" mode="out-in">
      <router-view></router-view>
    </transition>
  </div>
</template>

<script>
  window.jQuery = window.$ = require('jquery');
  import childProcess from "child_process";
  import pinia from "@/store/store.js";
  import { useGlobalStore } from "@/store/global.js";
  const globalStore = useGlobalStore(pinia);
  export default {
    name: 'chinese-chess',
    created() {
      console.log(globalStore.testEnv);
      globalStore.testEnv = "12334444";
      console.log(globalStore.testEnv);
      // console.log(global.testEnv);
      // const binary = childProcess.exec("./run", {});
      // binary.stdout.on("data", data => {
      //   console.log('stdout', data);
      // });
      // setInterval(() => {
      //   binary.stdin.write( Date.now() + "\n");
      // }, 1000);
      // setInterval(() => {
      //   binary.stdin.write( "do something" + "\n");
      // }, 2000);
    }
  }
</script>

<style>
  /* CSS */
</style>
