<template>
  <div class="flag"
       v-bind:style="flagStore.getStyle(x, y, color == 'red' ? flagStore.red : flagStore.black, specialStyle)">
    {{ name }}
  </div>
</template>

<script>
  import { defineComponent, ref } from 'vue-demi'
  import { pinia } from '../../store/store.js'
  import { useFlagStore } from "../../store/Game/flag";

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
      const flagStore = ref(useFlagStore(pinia));
      return {
        flagStore
      }
    },
    mounted() {
      console.log(this.flagStore.$);
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