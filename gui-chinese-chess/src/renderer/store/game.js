import { defineStore } from "pinia";
import { ref } from 'vue-demi'
/**
 color definition
 > red - 1
 > black - 2
*/
export const useGameStore = defineStore('game', {
    state: () => ({
        flags: [],
        moveAble: null, // null || Array
        replaceAble: null,// null || Array
        flagToken: "",
        hintToken: "",
        rTime: 0,
        bTime: 0,
        mate: 0,
        displayHint: false,
        loading: true,
        actionAble: 0, // 0 => not set, 1 || 2 => member color
        stop: true, // It will turn to ture when the game being end or replaying log or landingPage
        winner: 0, // 0 means the game hasn't stop.( 0 | 1 | 2 ),
        modal: "", // return by API,
        memePlay: ref(false), // play meme background
        beforeMovePosition: ref({
            x: 0,
            y: 0
        })
    }),
    getters: {
        hints: (state) => {
            let result = [];
            if (Array.isArray(state.moveAble)) {
                state.moveAble.forEach(e => {
                    result.push({
                        x: e.x,
                        y: e.y
                    });
                })
            }
            if (Array.isArray(state.replaceAble)) {
                state.moveAble.forEach(e => {
                    result.push({
                        x: e.x,
                        y: e.y
                    });
                })
            }
            return Array.from(new Set(result)); // bring each item is unique in Array by ES6
        },
        flagsHasInit: (state) => { // check flag has init
            return state.flags.map(e => e.color).every(e => !Number.isInteger(e));
        }
    },
    actions: {
        getMemberName(id, side = 'black') {
            /*
                將/帥 - general - 1
                士/仕 - advisor - 2
                象/相 - elephant - 3
                馬/傌 - horse - 4
                車/俥 - chariot - 5
                砲/炮 - cannon - 6
                卒/兵 - soldier - 7
             */
            const config = {
                black: ["將", "士", "象", "馬", "車", "砲", "卒"],
                red: ["帥", "仕", "相", "傌", "俥", "炮", "兵"]
            };
            if (id > config.black.length || !Number.isInteger(id)) {
                return "";
            }
            if (side == "black") {
                return config.black[id];
            }else {
                return config.red[id];
            }
        },
        getNumColor(id) {
            return ["red", "black"][id - 1];
        }
    }
});