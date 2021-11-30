<template>
  <div class="dashboard_container">
    <iframe id="grafana_frame" :src="baseUrlGrafana" frameborder="0"></iframe>
  </div>
</template>

<script>
import Filters from "@/components/main/Filters.vue";
import Board from "@/components/main/Board.vue";
import { HTTP } from "@/utils/http-commons.js";
export default {
  data() {
    return {
      baseUrlGrafana:
        "http://grings.life:3000/d/Anbrrc1Mz/aviario-elder?orgId=1&refresh=1m&from=now-6h&to=now&theme=light&kiosk=tv",
      grafanaVarTypes: ["temp", "humid"]
    };
  },
  name: "Sidebar",
  components: {
    Filters,
    Board,
  },
  methods: {
    getAllDevices() {
        HTTP.get('/device/get-all').then((response) => {
            var devices = response.data
            console.log("getAll")
            console.log(devices)

            //&var-temp=10&var-temp=20&var-temp=30&var-temp=40&var-humid=11&var-humid=21
            for (let device of devices) {
                let id_type = device.id_type - 1
                this.baseUrlGrafana+=  "&var-"+this.grafanaVarTypes[id_type]+"="+device.id
            }
        })
        console.log(this.baseUrlGrafana)
    }

  },
  created() {
    this.getAllDevices();
  },
};
</script>

<style>
.dashboard_container {
  height: 100%;
}
#grafana_frame {
  height: 100%;
  width: 100%;
}
</style>
