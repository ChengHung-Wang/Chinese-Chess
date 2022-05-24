import Vue from 'vue'
import VueCompositionAPI from "@vue/composition-api";
import axios from 'axios'
import App from './App'
import router from './router'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
import childProcess from "child_process"
import { createPinia, PiniaVuePlugin } from 'pinia'
import "bootstrap/dist/css/bootstrap.min.css"
import "bootstrap/dist/js/bootstrap.js"
import "./assets/css/style.css"

Vue.use(VueCompositionAPI);
Vue.use(PiniaVuePlugin)
Vue.use(ElementUI);
Vue.use(childProcess);

const pinia = createPinia();

// childProcess.exec("g++ ../Chinese-Chess/Chinese-Chess/run.cpp -o run");

if (!process.env.IS_WEB) Vue.use(require('vue-electron'))
Vue.http = Vue.prototype.$http = axios
Vue.config.productionTip = false

/* eslint-disable no-new */
new Vue({
  components: { App },
  router,
  template: '<App/>',
  pinia
}).$mount('#app')