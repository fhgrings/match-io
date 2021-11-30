<template>
    <div class="board">
        <div class="board-container">
            <iframe id="grafana_frame" :src="baseUrlGrafana" frameborder="0"></iframe>

            <!-- <div v-for="device in devices" :key="device.id">
                <Device :device="device" @update-device="updateDevice($event)" @remove-device="removeDevice($event)"/>
            </div> -->
        </div>
    </div>
</template>

<script>
import Device from '@/components/main/Device.vue'
import {HTTP} from '@/utils/http-commons.js'

export default {
    components: {
        Device
    },
    mounted() {
        this.$root.$on('refresh-board', () => this.refreshBoard());
    },
    methods: {
        updateDevice($event) {
            console.log($event)
            this.$emit("update-device", $event)
        },
        removeDevice($event) {
            HTTP.get('/device/delete?id='+$event.id).then((response) => {
                this.devices = this.devices.filter(device => device.id != $event.id)
                console.log(this.devices)
            })            
        },
        refreshBoard() {
            HTTP.get('/device/get-all').then((response) => {
                console.log(response.data)
                this.devices = response.data
            })
        }
    },
    created() {
        this.refreshBoard()
    },
    data() {
        return {
            baseUrlGrafana: "http://35.202.231.164:3000/d/Anbrrc1Mz/aviario-elder?orgId=1&refresh=1m&from=now-6h&to=now&theme=light&kiosk=tv",
            devices: [],
        }
    }
}
</script>
<style>
.board {
    height: 100%;
    border-radius: 10px;
    box-shadow: 10;
    padding: 10px 20px;
    border-style: solid;
    border-width: 1px;
    border-color: #dfdfdf;
    border-radius: 10px;

    background-color: white;

}
.board-container {
    height: 100%;
        display: flex;
    flex-wrap: wrap;
    justify-content: space-between;
    align-content: flex-start;
}
.board-container > div {
    display: flex;
    width: 100%;
}
</style>