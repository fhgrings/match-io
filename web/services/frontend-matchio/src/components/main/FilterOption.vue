<template>
    <div class="filter-option-button" @click="clicked()">
        <div class="text">{{this.text}}</div>
        <div class="icon"><v-icon name="x" style="width:15px"/></div>
    </div>
</template>
<script>
export default {
    methods: {
        clicked() {
            alert("Hello Click")
        }
    },
    props: {
        text: String
    }
}
</script>
<style>
.filter-option-button {
    background-color: #7B7DE5;
    color: #FFF;
    height: 25px;
    
    padding-left: 15px;
    padding-right: 15px;
    margin-right: 15px;
    font-size: 0.8em;
    border-radius: 8px;
    display: flex;
    justify-content: center;
    align-items: center;
}
.filter-option-button > div:first-child {
    margin-right: 10px;
}

.filter-option-button:hover {
    background-color:  #595aa7;
}
</style>