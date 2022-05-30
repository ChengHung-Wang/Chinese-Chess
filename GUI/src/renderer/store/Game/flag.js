import { defineStore } from "pinia";
import { useBoardStore } from "./board";
export const useFlagStore = defineStore('flag', {
    state: () => ({
        styleConfig: {
            borderStyle: "solid",
            borderWidth: 5 + 'px'
        },
    }),
    getters: {
        red: () => "rgba(220, 53, 69, .8)",
        black: () => "rgba(0, 0, 0, .5)",
        getStyleConfig: (state) => {
            const boardStore = useBoardStore();
            let result = state.styleConfig;
            let width = boardStore.cubeSize;
            result.width = width + 'px';
            result.height = width + 'px';
            return result;
        },
        getOffset: () => {
            const result = useBoardStore();
            return result.boardSize.borderWidth / 2;
        }
    },
    actions: {
        // get absolute position
        getStyle(x, y, color, specialStyle = {}) {
            let result = this.getStyleConfig;
            let width = result.width;
            let offset = this.getOffset + 'px';
            if (x > -1 && y > -1) {
                result.left = `calc(((${width} + ${offset}) / 2) * (-1 + 2 * ${x}))`;
                result.top = `calc(((${width} + ${offset}) / 2) * (-1 + 2 * ${y}))`;
            }else {
                result.left = "unset";
                result.top = "unset";
                result.position = "relative";
            }
            result.color = color;
            result.borderColor = color
            return Object.assign(result, specialStyle);
        }
    },

});