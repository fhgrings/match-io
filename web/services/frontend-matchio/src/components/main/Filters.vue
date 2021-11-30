<template>
    <div class="filter-container">
        <div class="filters">
            <div v-for="filter in filters" :key="filter.id">
                <FilterOption :text="filter.text"/>
            </div>
        </div>
        <div @click="addNewDevice()">Adicionar Novo</div>
    </div>
</template>
<script>
import FilterOption from '@/components/main/FilterOption.vue'
export default {
    auto: "auto",
    name: "Filters",
    data() {
        return {
            filters: [
                {id: 1,text: "Node 5B5C"},
                {id: 1,text: "Node A9A4"},
            ],
        }        
    },
    methods: {
        addNewDevice() {
            this.$modal.show('form-device')
        },
        
    },
    components: {
        FilterOption
    },     
}
</script>
<style>
.filter-container {
    height: 50px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.filters {
    display: flex;
}
</style>