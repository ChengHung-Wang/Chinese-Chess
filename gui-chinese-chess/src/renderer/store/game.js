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
        hints: [],
        flagToken: "",
        hintToken: "",
        rTime: 0,
        bTime: 0,
        displayHint: false,
        loading: true,
        action: 1, // TODO: switchBy to getRound API. This is fake data,
        stop: false, // It will turn to ture when the game being end or replaying logs
        winner: 0, // 0 means the game hasn't stop.( 0 | 1 | 2 ),
        modal: "", // return by API,
        memePlay: ref(false)
    }),
    getters: {

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
        }
    }
});