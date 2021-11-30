<template>
  <div class="device-list-container">
    <Filters />
    <Board @update-device="updateDevice($event)" />
    <modal
      name="form-device"
      height="auto"
      @before-open="beforeOpen"
      @before-close="beforeClose"
    >
      <div class="form-device">
        <div class="form-device-title">
          <h1 v-if="!this.deviceCopy.id">Novo Dispositivo</h1>
          <h1 v-else>Editar Dispositivo - ID: {{ deviceCopy.id }}</h1>
        </div>
        <div class="form-device-body">
          <div class="id">
            ID *
            <input type="text" name="" id="" v-model="deviceCopy.new_id" />
          </div>
          <div class="name">
            Nome *
            <input type="text" name="" id="" v-model="deviceCopy.name" />
          </div>
          <div class="description">
            Descrição
            <input type="text" name="" id="" v-model="deviceCopy.description" />
          </div>
          <div class="type">
            Tipo *
            <select v-model="deviceCopy.id_type" name="type" id="">
              <option v-bind:value="type.id" :key="type.id" v-for="type in types">
                {{ type.name }}
              </option>
            </select>
          </div>
          <div class="perfil">
            Perfil *
            <select v-model="deviceCopy.id_perfil" name="perfil">
              <option v-bind:value="perfil.id" :key="perfil.id" v-for="perfil in perfils">
                {{ perfil.name }}
              </option>
            </select>
          </div>
        </div>
        <div class="form-device-bottom">
          <button @click="send()">Concluir</button>
          <button @click="hide()">Fechar</button>
        </div>
      </div>
    </modal>
  </div>
</template>

<script>
import Filters from "@/components/main/Filters.vue";
import Board from "@/components/main/Board.vue";
import { HTTP } from "@/utils/http-commons.js";

export default {
  name: "Sidebar",
  components: {
    Filters,
    Board,
  },
  data() {
    return {
      device: { id: null, name: null, description: null },
      deviceCopy: { id: null, name: null, description: null },
      perfils: [],
      types: [],
      isModalClosable: false,
    };
  },

  methods: {
    updateDevice($event) {
      this.deviceCopy = JSON.parse(JSON.stringify($event));;
      this.deviceCopy.new_id = this.deviceCopy.id
      console.log(this.deviceCopy.id)
      this.$modal.show("form-device");
    },

    clicked() {
      this.$modal.show("form-device");
    },
    send() {
      if (this.deviceCopy.id) {
          this.updateDeviceHTTP()
      } else {
          this.addNewDevice()
      }
      this.isModalClosable = true;
      this.$modal.hide("form-device");


    },
    hide() {
      this.isModalClosable = true;
      this.$modal.hide("form-device");
    },
    beforeOpen(event) {
      this.isModalClosable = false;
      
    },
    beforeClose(event) {
      if (!this.isModalClosable) {
        event.cancel();
        return
      }
      this.device = {};
    },

    refreshAPIdata() {
      HTTP.get("/perfil/get-all").then((response) => {
        console.log(response.data);
        this.perfils = response.data;
      });
      HTTP.get("/type/get-all").then((response) => {
        console.log(response.data);
        this.types = response.data;
      });
    },

    updateDeviceHTTP() {
      HTTP.post('/device/update', this.deviceCopy).then((response) => {
        console.log(response.data)
        this.$root.$emit('refresh-board');
      })

    },
    addNewDevice() {
      HTTP.post('/device/add', this.deviceCopy).then((response) => {
        console.log(response.data)
        this.$root.$emit('refresh-board');
      })
    }
  },

  created() {
    console.log("Refresh");
    this.refreshAPIdata();
  },
};
</script>

<style>
.device-list-container {
  height: 100%;
  margin: 10px 50px 10px 50px;
}

.form-device {
  display: flex;
  flex-direction: column;
  height: 100%;
  justify-content: space-between;
  padding: 20px;
}

.form-device-title {
  text-align: start;
  border-bottom: 1px solid #dfdfdf;
}

.form-device-body {
  height: 100%;
  text-align: start;
  margin: 10px 0px;
}
.form-device-body > div {
  display: flex;
  justify-content: space-between;
  margin: 25px 5px;
  color: gray;
  font-size: 15px;
}

.form-device-body > div > input {
  background-color: rgb(236, 236, 236);
  padding: 8px;
  border-radius: 5px;
  height: 20px;
  width: 400px;
}

.form-device-body > div > select {
  width: 400px;
}

.form-device-bottom {
  display: flex;
  justify-content: space-between;
}
</style>
