<template>
  <div id="app">
    <el-button type="primary">主要按钮</el-button>
    <el-button icon="el-icon-search" circle></el-button>
    <router-view></router-view>
  </div>
</template>

<script>
  import childProcess from "child_process";
  export default {
    name: 'chinese-chess',
    created() {
      const binary = childProcess.exec("./run", {});
      binary.stdout.on("data", data => {
        console.log('stdout', data);
      });
      setInterval(() => {
        binary.stdin.write( Date.now() + "\n");
      }, 1000);
      setInterval(() => {
        binary.stdin.write( "do something" + "\n");
      }, 2000);
    }
  }
</script>

<style>
  /* CSS */
</style>
