import { defineStore } from "pinia";
import { useBoardStore } from "./board";

export const useHintStore = defineStore('hint', {
    state: () => ({
        scaleSize: '40px',
    }),
    getters: {
        elPrimaryBg: () => "#b3d8ff",
        elPrimaryText: () => "#409eff",
        darkBlueText: () => "rgb(0, 125, 255)",
        transparent: () => "transparent",
        styleConfig: (state) => {
            const boardStore = useBoardStore();
            return {
                width: `calc(${ boardStore.cubeSize }px - ${state.scaleSize})`,
                height: `calc(${ boardStore.cubeSize }px - ${state.scaleSize})`
            }
        },
        getBoardBorderWidth: () => {
            const boardStore = useBoardStore();
            return boardStore.boardSize.borderWidth / 2;
        },
        getWidthNum: () => {
            const boardStore = useBoardStore();
            return boardStore.cubeSize;
        },
        getScaleSizeNum: (state) => {
            return parseInt(state.scaleSize.split("px")[0]);
        }
    },
    actions: {
        // get absolute position
        getStyle(x, y) {
            let result = this.styleConfig;
            let cubeWidth = this.getWidthNum;
            let hintWidth = cubeWidth - this.getScaleSizeNum;
            let offset = this.getBoardBorderWidth;
            // left: calc((((48.1px + 30px) / 2) * -1) + 30px -6px)
            // top:  calc((((48.1px + 30px) / 2) * -1) + 30px - 6px)
            // result.left = `calc((((${hintWidth}px + ${this.getScaleSizeNum}px) / 2) * ${-1 + 2 * x}) + ${this.getScaleSizeNum}px - ${offset * 4}px)`
            // result.top = `calc((((${hintWidth}px + ${this.getScaleSizeNum}px) / 2) * ${-1 + 2 * y}) + ${this.getScaleSizeNum}px - ${offset * 4}px)`
            result.left = `calc(((${cubeWidth}px + ${offset}px) / 2) * (-1 + 2 * ${x}) + ${this.getScaleSizeNum / 2}px)`;
            result.top = `calc(((${cubeWidth}px + ${offset}px) / 2) * (-1 + 2 * ${y}) + ${this.getScaleSizeNum / 2}px)`;
            result.backgroundColor = this.elPrimaryBg;
            result.border = `1px ${this.elPrimaryBg} solid`;
            result.color = this.darkBlueText;
            return JSON.parse(JSON.stringify(result));
        }
    }
});