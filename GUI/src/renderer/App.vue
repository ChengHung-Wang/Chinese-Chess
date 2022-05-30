<template>
  <div id="app">
    <transition name="fade" mode="out-in">
      <router-view></router-view>
    </transition>
  </div>
</template>

<script>
  window.jQuery = window.$ = require('jquery');

  // import { ref } from 'vue-demi'
  // import { createPinia } from "pinia"
  // import { useGlobalStore } from "./store/global.js"

  export default {
    name: 'chinese-chess',
    created() {
      // this.globalStore.testEnv = "12334444";
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
    },
    setup() {
      // const pinia = createPinia();
      // const globalStore = useGlobalStore(pinia);
      return {
        // globalStore
      }
    },
    methods: {
      // I don't have any more time to plan the architecture

      // ************************************
      // *************** API ****************
      // ************************************

    }
  }
</script>

<style>
  /* CSS */
</style>
