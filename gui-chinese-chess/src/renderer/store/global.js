import { defineStore } from "pinia";
import childProcess from "child_process";
export const useGlobalStore = defineStore('global', {
    state: () => {
        return {
            testEnv: "1234",
            process: childProcess.exec("./run", {})
        }
    },
    getters: {
        setNew :(state) => {
            state.process.stdin.write("setNew");
        }
    }

})