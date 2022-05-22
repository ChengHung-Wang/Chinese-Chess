import { defineStore } from "pinia";
export const useBoardStore = defineStore('board', {
    state: () => ({
        padding: 5,
        boardDom: null, // jquery event
        boardSize: {
            width: null, // int(px, but only int)
            height: null, // same
            borderWidth: 3
        },
        cubeSize: null,
        init: false // init status
    }),
    actions: {
        getCubePosition(width, height) {
            return {
                width: width + 'px',
                height: height + 'px'
            }
        }
    }
});