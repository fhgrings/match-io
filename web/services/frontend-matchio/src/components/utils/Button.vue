<template>
    <div class="button" @click="$router.push('dashboard')">
        {{this.text}}
    </div>
</template>
<script>
import {HTTP} from '@/utils/http-commons.js'
export default {
    props: {
        text: String,
    },
    methods: {
    }
}
</script>
<style>
.button {
    background-color: #69DBA4;
    color: #FFF;
    height: 40px;
    width: 180px;
    border-radius: 3px;
    display: flex;
    justify-content: center;
    align-items: center;
}

.button:hover {
    background-color:  #6bb18f;
}
</style>