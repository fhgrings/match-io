<template>
    <div class="device-container">
        <div class="line" style="width: 10px">
            <input type="checkbox" id="checkbox">
        </div>
        <div class="device-start" style="display: flex; width:10%;">
            <div class="device-type">
                <div class="icon"><v-icon :name="icon" style="width:20px"/></div>
            </div>
            <div class="device-name">{{device.name}}</div>

        </div>
        <div class="device-midle" style="width: 60%; display: flex; align-content:center">
            <div class="device-description">{{device.description}}</div>

        </div>
        <div class="device-end" style="display:flex">
            <div class="device-lastUpdate">ID: {{device.id}}</div>
            <div class="device-edit" @click="updateDevice()">
                <div class="icon"><v-icon name="edit" style="width:20px"/></div>
            </div>
            <div class="device-edit" @click="removeDevice()">
                <div class="icon"><v-icon name="x" style="width:20px"/></div>
            </div>
        </div>
    </div>
</template>
<script>
export default {
    methods: {
        updateDevice() {
            this.$emit("update-device", this.device)
        },
        removeDevice() {
            this.$emit("remove-device", this.device)
        }
    },
    props: {
        device: Object
    },
    computed: {
        icon: function(){
            if (this.device.id_type == 1) {
                return "thermometer"
            }
            if (this.device.id_type == 2) {
                return "droplet"
            }
            return "bluetooth"
        }
    },
}
</script>
<style>
    .author {
        font-size: 13px;
    }
    .device-container {
        width: 100%;
        height: 25px;
        background-color: #FFFFFF;
        border-style: solid;
        border-color: #dfdfdf;
        border-radius: 10px;
        border-width: 1px;
        padding: 20px;
        margin: 10px 0px;
        display: flex;
        flex-direction: row;
        justify-content: space-between;
        width: 100%;

    }
    .device-name {
        width: 100%;
        text-align: start;
        margin-left: 20px;
        align-items: center;
        display: flex;

    }
    .device-description {
        width: 55%;
        text-align: start;
        color: #666;
        align-self: center;
        display: flex;

    }
    .device-lastUpdate {
        width: 100%;
        text-align: start;
        align-items: center;
        display: flex;
        margin-right: 15px;
    }
    .device-edit {
        display: flex;
        align-items: center;
        margin: 0px 5px;
    }

    .icon{
    color:#666
    }
    .icon:hover{
        color:#000
    }
    .icon-close{
        color:red
    }
</style>