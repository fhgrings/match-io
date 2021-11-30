<template>
  <div id="app">
    <div class="header">
      <Header/>
    </div>
    <div id="container">
      <div class="sidebar">
        <Sidebar />
      </div>
      <div class="app-router">
        <router-view/>
      </div>
    </div>
  </div>
</template>


<script>
  import Sidebar from '@/components/utils/Sidebar.vue'
  import Header from '@/components/utils/Header.vue'
  export default {
  name: 'App',
  components: {
    Sidebar,
    Header
  }
}
</script>
<style>
 @import url('https://fonts.googleapis.com/css2?family=Montserrat:ital,wght@0,600;0,800;1,200;1,400&display=swap');
  .sidebar {
    width: 230px;
    height: 100%;
    background-color: black;
  }
  .app-router {
    /* display: flex; */
    flex: 1 1;
  }
  body {
    margin: 0;
    padding: 0;
  }

  #app {
    font-family: 'Montserrat', sans-serif;
    font-size: 0.8rem;
    letter-spacing: 1px;
    color: #322F42;
    background-color: #F0F1F4;
  }

  #container {
    padding-top: 50px;
    display: flex;
    justify-content: space-between;

    width: 100%;
    min-height: 93vh;
    background-size: cover;
    overflow: hidden;

    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
  }
#nav {
  padding: 30px;
}

#nav a {
  font-weight: bold;
}

#nav a.router-link-exact-active {
  color: #42b983;
}
</style>
