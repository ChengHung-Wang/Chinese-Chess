import { defineStore } from "pinia";
import childProcess from "child_process";
import ElementUI from 'element-ui'
export const useGlobalStore = defineStore('global', {
    state: () => {
        return {
            process: childProcess.exec("../API/Chinese-Chess/cmake-build-debug/Chinese_Chess", {}),
            responseStacks: [],
            apiTimeOut: 2000
        }
    },
    getters: {
        // check all the api has response
        checkAllSet: (state) => {
            return state.responseStacks.every(e => {
                if (e.completed) {
                    return true;
                }
                return false;
            });
        }
    },
    actions: {
        getHash() {
            let random = [...Array(8).keys()].map(e => String.fromCharCode(Math.floor((Math.random() * (126 - 47)) + 48))).join("");
            let cacheToken = Date.now().toString(16) + random + "";
            let token = cacheToken.split('').sort((a, b) => Math.floor(Math.random() - 0.5)).join("");
            return token;
        },
        async downloadFile(filename, content) {
            const result = await new Promise(resolve => {
                const electron = require('electron');
                const path = require('path');
                const fs = require('fs');
                const dialog = electron.remote.dialog;
                dialog.showSaveDialog({
                    title: 'Select the File Path to save',
                    defaultPath: path.join(__dirname, '../assets/' + filename),
                    buttonLabel: 'Save',
                    // Restricting the user to only Text Files.
                    filters: [
                        {
                            name: 'Text Files',
                            extensions: ['txt']
                        },],
                    properties: []
                }).then((file) => {
                    if (!file.canceled) {
                        fs.writeFile(file.filePath.toString(), content, function (err) {
                            if (err) {
                                console.log(err);
                                resolve(false);
                            }
                            resolve(true);
                        });
                    } else {
                        resolve(false);
                    }
                }).catch(err => {
                    console.log(err);
                    resolve(false);
                });
            });
            return result;
        },
        // wait all the request are completed
        async waitAllReqCompleted(forceCompleted = false) {
            await new Promise(resolve => {
                const timeOut = setTimeout(() => {
                    // force complete all response
                    if (! this.checkAllSet) {
                        let fails= [];
                        this.responseStacks = this.responseStacks.map(e => {
                            if (! e.completed) {
                                fails.push(e);
                            }
                            if (forceCompleted) {
                                e.completed = true;
                            }
                            return e;
                        });
                        clearTimeout(timeOut);
                        clearInterval(interval);
                        console.error('ERROR: API response time out', fails, this.responseStacks);
                    }
                    resolve();
                }, this.apiTimeOut);
                const interval = setInterval(() => {
                    if (this.checkAllSet) {
                        clearInterval(interval);
                        clearTimeout(timeOut);
                        resolve();
                    }
                }, 50);
                if (this.checkAllSet) {
                    clearInterval(interval);
                    clearTimeout(timeOut);
                    resolve();
                }
            });
        }
    },
})