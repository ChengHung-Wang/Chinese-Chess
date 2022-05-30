<template>
  <div class="hint"
       v-bind:style="hintStore.getStyle(x, y)"
      v-bind:class="{'op-0': !gameStore.displayHint}">
<!--    <el-popconfirm :title="`移動到(${x}, ${y})?`" confirm-button-text="確認">-->
<!--      <el-button size="mini" slot="reference" type="primary">({{ x }}, {{ y }})</el-button>-->
<!--    </el-popconfirm>-->
    ({{x}}, {{y}})
  </div>
</template>

<script>
import { useHintStore } from "../../store/Game/hint";
import { useGameStore } from "../../store/game";
import { defineComponent, ref } from 'vue-demi'

export default defineComponent({
  name: "hint",
  props: {
    x: Number,
    y: Number,
  },
  setup() {
    const hintStore = ref(useHintStore());
    const gameStore = ref(useGameStore());
    return {
      hintStore,
      gameStore
    }
  }
})
</script>
<style scoped>
.hint {
  position: absolute;
  transition: .25s ease-in-out;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  background-size: contain;
  background-position: center;
  background-repeat: no-repeat;
  backdrop-filter: blur(30px) saturate(180%);
  opacity: .5;
  cursor: pointer;
  z-index: 2;
}
</style>