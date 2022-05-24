<template>
  <div id="content" class="fcc">
    <div class="container">
      <div class="row">
        <div class="col-12 fcc word-break">
          <h1 class="text-center w-100">
            歡迎！
          </h1>
          <p class="text-center">您希望怎麼開始遊戲？</p>
        </div>
        <div class="col-6" @click="selected = true; hasConfig = true">
          <el-badge :value="'已選'" class="badge-item w-100" type="success" :hidden="!(selected && hasConfig)">
            <el-card class="box-card w-100" :shadow="selected && hasConfig ? 'always' : 'hover'">
              <h4 class="text-center mb-3">從上次的地方開始</h4>
              <el-upload
                  class="fcc"
                  ref="upload-sql"
                  action=''
                  accept=".txt,.sql, .js"
                  :auto-upload="false"
                  :on-change="changeFile"
                  :http-request="uploadHandler">
                <el-button class="w-100" plain slot="trigger" size="small">
                  <i class="el-icon-upload mr-1 font-size-14"></i>上傳Config
                </el-button>
              </el-upload>
            </el-card>
          </el-badge>
        </div>
        <div class="col-6" @click="selected = true; hasConfig = false;">
          <el-badge :value="'已選'" class="badge-item w-100" type="success" :hidden="!(selected && !hasConfig)">
            <el-card class="box-card w-100" :shadow="selected && !hasConfig ? 'always' : 'hover'"  >
              <h4 class="text-center mb-5">開始新的遊戲</h4>
              <el-button type="primary" plain><i class="el-icon-right el-text-primary"></i></el-button>
            </el-card>
          </el-badge>
        </div>
        <div class="col-12 mt-5">
          <el-button type="primary" plain @click="goToGame()">
            <i class="el-icon-right el-text-primary"></i>
            開始遊戲
          </el-button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import { ref, defineComponent } from 'vue-demi'
  import { useGlobalStore } from "../store/global";
  import { useGameStore } from "../store/game";

  export default defineComponent({
    name: 'landing-page',
    data() {
      return {
        configText: '',
        hasConfig: false,
        selected: false
      }
    },
    setup() {
      const globalStore = ref(useGlobalStore());
      const gameStore = ref(useGameStore());
      return {
        globalStore,
        gameStore
      }
    },
    created() {
      this.gameStore.stop = true;
    },
    mounted() {
      this.globalStore.process.stdout.on("data", this.receiveData);
    },
    methods: {
      // I don't have any more time to plan the architecture
      handleRemove(file, fileList) {
        console.log(file, fileList);
      },
      getRandomNum (min, max) {
        return Math.floor(Math.random() * (max - min + 1) + min)
      },
      changeFile (file, fileList) {
        if (file.status === 'ready') {
          // 已上传文件列表如果存在 2 条记录，移除第一条，实现替换效果
          if (fileList.length === 2) {
            fileList.shift()
          }
          // 手动开始上传
          this.$refs['upload-sql'].submit()
        }
      },
      uploadHandler (params) {
        const isLt2M = params.file.size / 1024 / 1024 <= 2
        if (!isLt2M) {
          this.$notify({
            message: '檔案超過2MB限制',
            type: 'warning',
            title: '警告'
          })
          return
        }
        params.onProgress({ percent: this.getRandomNum(19, 99) })
        setTimeout(() => {
          this.readText(params)
        }, 100)
      },
      async readText (params) {
        const readFile = new FileReader()
        readFile.onload = (e) => {
          this.configText = e.target.result
          params.onProgress({ percent: 100 })
          params.onSuccess()
        }
        readFile.readAsText(params.file)
      },
      receiveData(response) {
        const data = JSON.parse(response);
        let thisResponseIndex = this.globalStore.responseStacks.map(e => e.token).indexOf(data.hash);
        if (thisResponseIndex > -1 && !this.globalStore.responseStacks[thisResponseIndex].completed) {
          this.globalStore.responseStacks[thisResponseIndex].completed = true;
          this.globalStore.responseStacks[thisResponseIndex].callback(data);
        }
        console.log('receiveData in LandingPage');
      },
      // ************************************
      // *************** API ****************
      // ************************************
      goToGame() {
        if (!this.selected) {
          this.$message({
            message: "尚未選擇遊戲模式",
            type: "error",
            showClose: true,
            closable: true
          });
        } else if (this.hasConfig && this.configText.length <= 0) {
          this.$message({
            message: "請上傳文件",
            type: "error",
            showClose: true,
            closable: true
          });
        }else {
          if (! this.hasConfig) {
            // call API(setNew)
            let token = this.globalStore.getHash();
            let commend = `setNew ${token}`;
            this.globalStore.process.stdin.write(commend + '\n');
            this.gameStore.flagToken = token;
            this.globalStore.responseStacks.push({
              completed: false,
              token: token,
              result: null,
              callback: (response) => {
                this.gameStore.flagToken = response.hash;
                this.gameStore.flags = response.chess;
                this.gameStore.rTime = response.rTime;
                this.gameStore.bTime = response.bTime;
                this.$router.push("/game");
              }
            });
          }else {
            // call API(setFile)
            let token = this.globalStore.getHash();
            let commend = `setFile ${token} ${this.configText}\n@~!~@`;
            this.globalStore.process.stdin.write(commend + '\n');
            this.gameStore.flagToken = token;

            this.globalStore.responseStacks.push({
              completed: false,
              token: token,
              result: null,
              callback: (response) => {
                this.gameStore.flagToken = response.hash;
                this.gameStore.flags = response.chess;
                this.gameStore.rTime = response.rTime;
                this.gameStore.bTime = response.bTime;
                this.$router.push("/game");
              }
            });
          }
        }
      }
    },
    async beforeRouteLeave(to, from, next) {
      await new Promise(resolve => {
        const timeOut = setTimeout(() => {
          // force complete all response
          this.globalStore.responseStacks.map(e => {
            e.completed = true;
            clearTimeout(timeOut);
            clearInterval(interval);
            resolve();
          });
        }, this.globalStore.apiTimeOut);
        const interval = setInterval(() => {
          // if all api has response
          if (this.globalStore.checkAllSet) {
            clearInterval(interval);
            clearTimeout(timeOut);
            resolve();
          }
        }, 50);
        if (this.globalStore.checkAllSet) {
          clearInterval(interval);
          clearTimeout(timeOut);
          resolve();
        }
      });
      this.globalStore.process.stdout.removeAllListeners();
      next();
    }
  })
</script>

<style scoped>
  #content {
    position: absolute;
    left: 0;
    right: 0;
    height: 100vh;
  }
  .el-card {
    border: 2px solid #c6e2ff;
    height: 200px;
  }
  button {
    width: 100%!important;
  }
</style>
<style>
  .el-upload-list {
    width: 100% !important;
  }
  .el-badge__content.is-fixed {
    right: 20px!important;
  }
</style>