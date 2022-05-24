<template>
  <div class="container">
    <div class="row">
      <div class="col-12">
        <h3>遊戲結束</h3>
      </div>
    </div>
  </div>
</template>
<script>
import { defineComponent, ref } from 'vue-demi'
import { useGameStore } from "../../store/game"

export default defineComponent({
  name: "records",
  setup() {
    const gameStore = ref(useGameStore());
    return {
      gameStore
    }
  },
  props: {

  }
});
</script>