import { defineStore } from "pinia";
import { ref } from 'vue-demi'

export const useRecordsStore = defineStore('records', {
    state: () => ({
        nowSteps: 1,
        logs: ref([])
    }),
    getters: {

    },
    actions: {

    }
});