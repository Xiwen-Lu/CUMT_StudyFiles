<template>
  <div class="home">
<!--    <img alt="Vue logo" src="../assets/logo.png">-->
<!--    <HelloWorld msg="Welcome to Your Vue.js App"/>-->
<!--    <HelloElement></HelloElement>-->
    <el-container>
      <el-header>
        布匹缺陷检测系统
<!--        <el-button>更换主题颜色</el-button>-->
      </el-header>
      <el-container>
        <el-aside :xs="16" :sm="6" style="width: 170px">
          <el-button style="background-color: gainsboro">图片检测</el-button>
        </el-aside>
        <el-main>
          <router-view/>
        </el-main>
      </el-container>
    </el-container>
  </div>
</template>

<script>
// @ is an alias to /src
// import HelloWorld from '@/components/HelloWorld.vue'
// import HelloElement from "@/components/HelloElement";
export default {
  name: 'Home',
  components: {
    // HelloElement
  }
}
</script>

<style>
.el-aside{
  border: 5px solid #2c3e50;
  background-color: darkgrey;
}

.el-header{
  border: 5px solid #2c3e50;
  height: 100px;
  background-color: darkgrey;
  font-size: xx-large;
}

.el-container{

}

</style>
