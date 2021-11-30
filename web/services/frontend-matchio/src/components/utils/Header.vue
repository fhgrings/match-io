<template>
  <div id="header-container">
    <div class="header-menu">
        <div class="header-logo">MatchIO</div>
        <v-icon name="menu" style="width:30px; color: white"/>
    </div>
    
    <div class="input">
        <input type="text" name="" id="">
        <v-icon name="search" style="width: 25px; margin: 5px"/>
    </div>

      
  </div>
</template>

<script>
export default {

}
</script>

<style>
 @import url('https://fonts.googleapis.com/css2?family=Fredoka+One&display=swap');
    input {
        background: none;
        border: none;
    }
    .input {
        display: flex;
        justify-content: space-between;
        align-items: center;
        background-color: #6A6CD1;
        height: 60%;
        width: 500px;
        border-radius: 7px;
        margin-left: 30px;
    }
    #header-container {
        width: 100%;
        background-color: #7B7DE5;
        height: 50px;
        position: absolute;
        color: white;
        font-family: 'Fredoka One', cursive;
        font-size: 30px;
        letter-spacing: 0.5px;
        position: fixed;
        display: flex;
        flex-direction: row;
        /* justify-content: 'center'; */
        align-items: center;

    }
    .header-menu {
        width: 230px;
        display: flex;
        flex-direction: row;
        justify-content: space-around;
        align-items: center
    }
    .header-logo {
        margin-left: 15px;
    }
</style>