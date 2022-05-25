<template>
  <div
      class="flag"
      v-bind:style="flagStore.getStyle(x, y, color == 'red' ? flagStore.red : flagStore.black, specialStyle)"
      v-bind:class="{shadowDeep: x == selectedFlag.x && y == selectedFlag.y}">
    <p>{{ uni }}</p>
    <h4 class="m-0 fcc" v-if="name != '帥'">{{ name }}</h4>
    <h4 class="m-0 fcc op-50" v-if="name == '帥'">{{ name }}</h4>
  </div>
</template>

<script>
  import { storeToRefs } from 'pinia'
  import { useGameStore } from "../../store/game"
  import { useFlagStore } from "../../store/Game/flag"
  import { defineComponent, ref } from 'vue-demi'
  export default defineComponent({
    name: "flag",
    props: {
      x: Number,
      y: Number,
      uni: Number,
      name: String,
      color: String,
      specialStyle: Object,
    },
    data() {
      return {
      }
    },
    setup() {
      const { selectedFlag } = storeToRefs(useGameStore());
      const flagStore = ref(useFlagStore());
      return {
        flagStore,
        selectedFlag
      }
    }
  })
</script>
<style>
  h4 {
    width: 100%;
    height: 100%;
    cursor: pointer;
    overflow: hidden;
    font-size: 120%!important;
  }
  .op-50 {
    opacity: .4;
  }
  .shadowDeep {
     box-shadow: 0 .5rem 1rem rgba(0,0,0,.45)!important;
  }
  p {
    font-size: 14px;
  }
</style>