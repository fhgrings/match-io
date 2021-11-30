<template>
  <div class="main">
    <Filters/>
    <Board/>
  </div>
</template>

<script>
  import Filters from '@/components/main/Filters.vue'
  import Board from '@/components/main/Board.vue'
  export default {
  name: 'Sidebar',
  components: {
    Filters,
    Board
  }
}
</script>

<style>
.main  {
  height: 100%;
  margin: 10px 50px 10px 50px 
}
</style>
