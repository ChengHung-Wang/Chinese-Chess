import { defineStore } from "pinia";
import childProcess from "child_process";
export const useGlobalStore = defineStore('global', {
    state: () => {
        return {
            process: childProcess.exec("../Chinese-Chess/Chinese-Chess/cmake-build-debug/Chinese_Chess", {}),
            responseStacks: []
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
        },
        downloadFile(filename, content) {
            let blob = new Blob([content]);
            let evt = document.createEvent("HTMLEvents");
            evt.initEvent("click");
            $("<a>", {
                download: filename,
                href: webkitURL.createObjectURL(blob)
            }).get(0).dispatchEvent(evt);
        }
    }
})