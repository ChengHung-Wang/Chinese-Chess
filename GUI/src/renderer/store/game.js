import { defineStore } from "pinia";
import { ref } from 'vue-demi'
/**
 color definition
 > red - 1
 > black - 2
*/
export const useGameStore = defineStore('game', {
    state: () => ({
        flags: ref([]),
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
        selectedFlag: ref({x: null, y: null, uni: null}) // selected flag, {x: NULL, y: NULL} || {x: Number, y: Number, uni: Number}
    }),
    getters: {
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
        // get color string by color id
        getNumColor(id) {
            return ["red", "black"][id - 1];
        },
        getFlagIndex(x, y, uni = null) {
            let result = -1;
            if (x == null || y == null) {
                return result;
            }
            this.flags.forEach((flag, index) => {
                if (flag.x === x && flag.y === y) {
                    if (uni !== null) {
                        if (flag.uni === uni) {
                            result = index;
                        }
                    }else if (uni === null){
                        result = index;
                    }
                }
            })
            return result;
        },
        reset() {
            this.flags =  ref([]);
            this.moveAble =  null; // null || Array
            this.replaceAble =  null;// null || Array
            this.flagToken =  "";
            this.hintToken =  "";
            this.rTime =  0;
            this.bTime =  0;
            this.mate =  0;
            this.displayHint =  false;
            this.loading =  true;
            this.actionAble =  0; // 0 => not set; 1 || 2 => member color
            this.stop =  true; // It will turn to ture when the game being end or replaying log or landingPage
            this.winner =  0; // 0 means the game hasn't stop.( 0 | 1 | 2 );
            this.modal =  ""; // return by API
            this.memePlay =  ref(false); // play meme background
            this.selectedFlag =  ref({x: null, y: null, uni: null}); // selected flag, {x: NULL, y: NULL} || {x: Number, y: Number}
        }
    }
});