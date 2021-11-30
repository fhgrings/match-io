<template>
  <div class="menu-options-container">
        <v-icon :name="this.icon" style="width:25px; color:white"/>
        <div class="text" @click="$router.push('/dispositivos')">{{this.text}}</div>
  </div>
</template>

<script>
export default {
    props: {
        text: String,
        icon: String,
        route: String
    }
}
</script>

<style>
.menu-options-container {
    font-size: 1em;
    display: flex;
    justify-content: flex-start;
    align-items: center;
}
.menu-options-container > div {
    margin-left: 20px;
    text-align: start;
}
</style>