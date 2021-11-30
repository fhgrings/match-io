import Vue from 'vue'
import App from './App.vue'
import router from './router'
import feather from 'vue-icon'
import VModal from 'vue-js-modal'

Vue.config.productionTip = false

Vue.use(feather, 'v-icon')
Vue.use(VModal)

new Vue({
  router,
  render: function (h) { return h(App) }
}).$mount('#app')
