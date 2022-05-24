<template>
  <div
      class="flag"
      v-bind:style="flagStore.getStyle(x, y, color == 'red' ? flagStore.red : flagStore.black, specialStyle)">
    <h4 class="m-0 fcc" v-if="name != '帥'">{{ name }}</h4>
    <h4 class="m-0 fcc op-50" v-if="name == '帥'">{{ name }}</h4>
  </div>
</template>

<script>
  import { useFlagStore } from "../../store/Game/flag";
  import { defineComponent, ref } from 'vue-demi'
  export default defineComponent({
    name: "flag",
    props: {
      x: Number,
      y: Number,
      name: String,
      color: String,
      specialStyle: Object
    },
    data() {
      return {
        bool: true
      }
    },
    setup() {
      const flagStore = ref(useFlagStore());
      return {
        flagStore
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
</style>