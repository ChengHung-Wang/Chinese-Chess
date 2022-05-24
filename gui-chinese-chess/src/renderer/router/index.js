import Vue from 'vue'
import Router from 'vue-router'
import { useGlobalStore } from "../store/global";

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'landing-page',
      component: require('@/components/LandingPage').default,
      // beforeEnter: (to, from, next) => {
      //   const globalStore = useGlobalStore();
      //   console.log(globalStore);
      //   next();
      // }
    },
    {
      path: '/game',
      name: 'game',
      component: require('@/components/Game').default
    }
  ]
})
