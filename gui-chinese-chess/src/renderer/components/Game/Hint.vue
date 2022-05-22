<template>
  <div class="hint"
       v-bind:style="hintStore.getStyle(x, y)">
  </div>
</template>

<script>
import { useHintStore } from "../../store/Game/hint";
import { defineComponent, ref } from 'vue-demi'

export default defineComponent({
  name: "hint",
  props: {
    x: Number,
    y: Number,
  },
  setup() {
    const hintStore = ref(useHintStore());
    return {
      hintStore
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
}
</style>