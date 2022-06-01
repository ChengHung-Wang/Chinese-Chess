<template>
  <div class="container">
    <div class="row">
      <div class="col-1">
        <el-slider
            v-model="nowSteps"
            :min="0" :max="(logs.length === 0 ? 0 : (logs.length - 1))"
            style="height: 100%;"
            :format-tooltip="formatTooltip"
            :show-stops="true"
            :show-tooltip="true"
            vertical>
        </el-slider>
      </div>
      <div class="col-11 board-frame">
        <div>
          <Board />
          <Flag
              v-for="item in getRoundChess(nowSteps)"
              v-if="item.disabled === false"
              :name="item.name"
              :x="item.x" :y="item.y" :color="item.color" :uni="item.uni">
          </Flag>
        </div>
      </div>
    </div>
  </div>
</template>
<style scoped>
  .board-frame {
    height: calc(100vh - 150px);
  }
  .flag {
    background-color: white!important;
  }
</style>

<script>
  import onBeforeMount from "@vue/composition-api";
  import { defineComponent, ref } from 'vue-demi'
  import { useGlobalStore } from "../../store/global";
  import { useGameStore } from "../../store/game"
  import { useRecordsStore } from "../../store/game/records"
  import Board from "./Board";
  import Flag from "./Flag";
  import { storeToRefs } from "pinia";
  export default defineComponent({
    name: "records",
    data() {
      return {
        bool: true
      }
    },
    setup() {
      const globalStore = ref(useGlobalStore());
      const gameStore = ref(useGameStore());
      const recordsStore = ref(useRecordsStore());
      const { nowSteps } = storeToRefs(useRecordsStore());
      const { logs } = storeToRefs(useRecordsStore());
      return {
        globalStore,
        gameStore,
        recordsStore,
        nowSteps,
        logs
      }
    },
    components: {
      Board,
      Flag
    },
    methods: {
      formatTooltip(val) {
        try {
          const thisData = this.logs[this.nowSteps];
          return `(${thisData.fromX}, ${thisData.fromY}) move to (${thisData.toX}, ${thisData.toY})`;
        }catch (e) {
          return val;
        }
      },
      getRoundChess(index) {
        if (this.logs[index] != undefined) {
          let result = [...Array(32)].fill({
            disabled: true
          });
          this.logs[index].chess.forEach(flag => {
            if (parseInt(flag.color) === 1 || parseInt(flag.color) === 2) {
              flag.color = this.gameStore.getNumColor(flag.color);
            }
            flag.specialStyle = {
              'pointer-events': "auto"
            };
            if (flag.name == '帥') {
              flag.specialStyle.animation = "faceMeme 1s steps(1, end) infinite";
              flag.specialStyle.fontWeight = "900";
            }else {
              flag.specialStyle.animation = "unset";
            }
            flag.specialStyle.zIndex = 1;
            flag.specialStyle.opacity = 1;
            flag.disabled = false;
            result[flag.uni - 1] = flag;
          });
          return result;
        }else {
          return [];
        }
      },
      getRoundDiff(targetIndex) {

      }
    }
  });
</script>