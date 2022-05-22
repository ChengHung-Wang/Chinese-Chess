import { defineStore } from "pinia";
import { ref } from 'vue-demi'
import pinia from "../store.js";
import { useBoardStore } from "./board";

export const useFlagStore = defineStore('flag', {
    state: () => ({
        styleConfig: {
            width: ref(useBoardStore(pinia)).value.cubeSize + 'px',
            height: ref(useBoardStore(pinia)).value.cubeSize + 'px',
            borderStyle: "solid",
            borderWidth: 5 + 'px'
        }
    }),
    getters: {
        red: () => "rgba(220, 53, 69, .5)",
        black: () => "rgba(0, 0, 0, .5)"
    },
    actions: {
        // get absolute position
        getStyle(x, y, color, specialStyle = {}) {
            let result = this.styleConfig;
            let width = this.styleConfig.width;
            let offset = (ref(useBoardStore(pinia)).value.boardSize.borderWidth / 2) + 'px';
            result.left = `calc(((${width} + ${offset}) / 2) * (-1 + 2 * ${x})`;
            result.top = `calc(((${width} + ${offset}) / 2) * (-1 + 2 * ${y})`;
            result.color = color;
            result.borderColor = color
            return Object.assign(result, specialStyle);
        }
    },

});