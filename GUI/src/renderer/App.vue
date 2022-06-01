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

    },
    setup() {
      return {
      }
    },
    methods: {
    
    }
  }
</script>

<style>
  /* CSS */
</style>
