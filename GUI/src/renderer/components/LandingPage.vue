<template>
  <div id="content" class="fcc">
    <div class="container">
      <div class="row">
        <div class="col-12 fsc word-break">
          <h1 class="text-left w-100">
            歡迎！
          </h1>
          <p class="text-left">您希望怎麼開始遊戲？</p>
        </div>
        <div class="col-4" @click="selected = true; hasConfig = true; smartBattle = false;">
          <el-badge :value="'已選'" class="badge-item w-100" type="success" :hidden="!(selected && hasConfig && !smartBattle)">
            <el-card class="fst box-card w-100 el-card-1" :shadow="selected && hasConfig && !smartBattle ? 'always' : 'hover'">
              <h4 class="text-left mb-4">從上次的地方開始</h4>
              <el-upload
                  class="fsc"
                  ref="upload-sql"
                  action=''
                  accept=".txt,.sql, .js"
                  :auto-upload="false"
                  :on-change="changeFile"
                  :http-request="uploadHandler">
                <el-button type="warning" class="w-100" plain slot="trigger">
                  <i class="el-icon-upload mr-1 font-size-14"></i>上傳Running Config
                </el-button>
              </el-upload>
            </el-card>
          </el-badge>
        </div>
        <div class="col-4" @click="selected = true; hasConfig = false; smartBattle = false">
          <el-badge :value="'已選'" class="badge-item w-100" type="success" :hidden="!(selected && !hasConfig && !smartBattle)">
            <el-card class="box-card w-100 el-card-2" :shadow="selected && !hasConfig && !smartBattle ? 'always' : 'hover'"  >
              <h4 class="text-left mb-3">開始新的遊戲</h4>
              <span style="font-size: 25px; font-weight: 400; color: #409EFF">新的開始<br/>全由您來做主</span>
            </el-card>
          </el-badge>
        </div>
        <div class="col-4" @click="selected = true; hasConfig = false; smartBattle = true">
          <el-badge :value="'已選'" class="badge-item w-100" type="success" :hidden="!(selected && !hasConfig && smartBattle)">
            <el-card class="box-card w-100 el-card-3" :shadow="selected && !hasConfig && smartBattle ? 'always' : 'hover'"  >
              <div class="fsc mb-3">
                <h4 class="text-left mb-0 mr-3 w-auto">智能對戰</h4>
              </div>
              <span style="font-size: 25px; font-weight: 400; color: #67C23A">強大的威力<br/>來至強大的智能引擎</span>
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
  import {storeToRefs} from "pinia";

  export default defineComponent({
    name: 'landing-page',
    data() {
      return {
        configText: '',
        hasConfig: false,
        selected: false,
        smartBattle: false
      }
    },
    setup() {
      const globalStore = ref(useGlobalStore());
      const gameStore = ref(useGameStore())
      const smartMode = storeToRefs(useGameStore());

      return {
        globalStore,
        gameStore,
        smartMode
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
                if (this.smartBattle) {
                  this.gameStore.smartMode = true;
                }
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
      await this.globalStore.waitAllReqCompleted(true);
      this.globalStore.process.stdout.removeAllListeners();
      console.log("Completed: action beforeRouteLeave in LandingPage.vue");
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
    border: 2px solid #dddddd;
    height: 200px;
    background-position: right;
    background-size: contain;
    background-repeat: no-repeat;
  }
  .el-card-1 {
    background-image: url("../assets/images/corner-1.png");
  }
  .el-card-2 {
    background-image: url("../assets/images/corner-2.png");
  }
  .el-card-3 {
    background-image: url("../assets/images/corner-3.png");
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