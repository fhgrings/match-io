<template>
  <div class="sidebar-container">
    <div class="header">
      <div><v-icon name="grid" style="width:20px; color:#4989a7" /></div>
      <div>Menu Options</div>
      <div><v-icon name="chevron-down" style="width:20px;"/></div>
    </div>
    <!-- <div @click="createCard()"> -->
    <Button :text="mainButton"/>
    <div  class="options_container">
      <div class="options" v-for="option in menuOptions" :key="option.id">
        <div class="option_selected"></div>
        <div>
          <MenuOptions :text="option.text" :icon="option.icon" :route="option.route"/>
        </div>
        <div></div>
      </div>
    </div>
    
  </div>
</template>

<script>
  import Button from '@/components/utils/Button.vue'
  import MenuOptions from '@/components/utils/MenuOptions.vue'
  import { HTTP } from '@/utils/http-commons.js'
  export default {
  name: 'Sidebar',
  
  data() {
    return {
        mainButton: "Dashboard",
        menuOptions: [
            {
              id:1,
              text: "Dispositivos",
              icon: "list",
              route: "/dispositivos"
            },
            {
              id:2,
              text: "Alerts",
              icon: "alert-triangle",
              route: "/about"

            },
            {
              id:3,
              text: "Messages",
              icon: "book-open",
              route: "/about"
            }]

    }
  },
  
  components: {
    Button,
    MenuOptions
  },
  methods: {
    createCard() {
      alert("Creating")
      var card =   {
        "title": "Add",
        "body": "Add Ad aDAD AD A AD LDAP",
        "color": "#FFFFFF",
        "position": 0
      }
      HTTP.post('/card/add', card).then((response) => {
        console.log(response.data)
        this.$root.$emit('refresh-board');
      })
    }
  }
}
</script>

<style scoped>
.sidebar-container{
    width: 230px;
    position: 0px;
    height: 100vh;
    background-color: #484D5E;
    position: fixed;
    display: flex;
    justify-content: top;
    align-content: center;
    align-items: center;
    flex-direction: column;
}

.header {
  background-color: #3B404F;
  display: flex;
  color: rgb(224, 224, 224);
  justify-content: center;
  align-items: center;
  height: 50px;
  width: 100%;
  margin-bottom: 20px;
}
.header > div {
  padding: 5px;
}
.options_container {
  margin-top: 20px;
  width: 100%;
}
.options {
  display: flex;
  color: #FFF;
  align-items: center;
  height: 40px;
  margin-bottom: 10px;
} 

.option_selected {
  width: 4px;
  /* background-color: #7B7DE5; */
  height: 100%;
}

.options > :nth-child(2){
  margin-left: 20px;
}

</style>