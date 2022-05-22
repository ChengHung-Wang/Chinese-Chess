import { defineStore } from "pinia";
import childProcess from "child_process";
export const useGlobalStore = defineStore('global', {
    state: () => {
        return {
            testEnv: "1234",
            process: childProcess.exec("./run", {})
        }
    },
    actions: {
        setNew() {
            this.process.stdin.write("setNew");
        },
        getHash() {
            let random = [...Array(8).keys()].map(e => String.fromCharCode(Math.floor((Math.random() * (126 - 47)) + 48))).join("");
            let cacheToken = Date.now().toString(16) + random + "";
            let token = cacheToken.split('').sort((a, b) => Math.floor(Math.random() - 0.5)).join("");
            return token;
        }
    }
})