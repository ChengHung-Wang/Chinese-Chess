<template>
  <div id="content">
    <div class="container-fluid">
      <div class="row">
        <div class="col-3">
          <Menu></Menu>
        </div>
        <div class="col-9">
          <Board></Board>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Menu from "./Game/Menu";
import Board from "./Game/Board";
export default {
  name: "game",
  data() {
    return {

    }
  },
  components: {
    Board,
    Menu
  }
}
</script>
<style scoped>

</style>