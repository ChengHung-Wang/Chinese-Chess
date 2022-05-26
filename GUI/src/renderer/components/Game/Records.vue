<template>
  <div class="container">

  </div>
</template>

<script>
  import { defineComponent, ref } from 'vue-demi'
  import { useGameStore } from "../../store/game"
  import Board from "./Board";
  import Flag from "./Flag";
  export default defineComponent({
    name: "records",
    setup() {
      const gameStore = ref(useGameStore());
      return {
        gameStore
      }
    },
    components: {
      Board,
      Flag
    }
  });
</script>