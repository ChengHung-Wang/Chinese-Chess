<template>
  <div class="flag"
       v-bind:style="flagStore.getStyle(x, y, color == 'red' ? flagStore.red : flagStore.black, specialStyle)">
    {{ name }}
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
    setup() {
      const flagStore = ref(useFlagStore());
      return {
        flagStore
      }
    }
  })
</script>
<style scoped>
  .flag {
    position: absolute;
    transition: .25s ease-in-out;
    border-radius: 50%;
    font-size: 30px;
    display: flex;
    align-items: center;
    justify-content: center;
    background-size: contain;
    background-position: center;
    background-repeat: no-repeat;
    background-color: rgba(255, 255, 255, .3);
    backdrop-filter: blur(30px) saturate(180%);
  }
</style>