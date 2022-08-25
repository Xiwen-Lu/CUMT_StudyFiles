import { createRouter, createWebHistory } from 'vue-router'
// import Home from '../views/Home.vue'
import masterInfoRead from "@/components/masterInfoRead";
import masterInfoEdit from "@/components/masterInfoEdit";
import picdetect from "@/components/picdetect";

const routes = [
  {
    path: '/',
    name: 'Home',
    component: picdetect
  },
  {
    path: '/about',
    name: 'About',
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
    component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
  },
  {
    path: '/masterInfoRead',
    name: 'masterInfoRead',
    component: masterInfoRead
  },
  {
    path: '/masterInfoEdit',
    name: 'masterInfoEdit',
    component: masterInfoEdit
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
