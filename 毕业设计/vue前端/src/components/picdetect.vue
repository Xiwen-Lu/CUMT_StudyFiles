<template>
<!--  端口号：<input type="text" v-model="picpath">-->





      <el-upload
          class="upload-demo"
          style="width: 100%"
          drag
          action="uploadpic"
          @change="onChangeUpload"
          auto-upload="false"
          multiple>
        <i class="el-icon-upload" ></i>
        <div class="el-upload__text">将文件拖到此处，或<em>点击上传</em></div>
      </el-upload>

  <el-row>
    <el-col :span="12"><el-image :src=imgUrl></el-image></el-col>
    <el-col :span="12"><el-image :src="imgServerUrl"></el-image></el-col>
  </el-row>
</template>



<script>
import axios from 'axios'
export default {
  name: "picdetect",
  data() {

    return {
      imgUrl: "",
      imgServerUrl:"",
      src: require("../assets/test.jpg")

      // src: require("E:\\学习资源\\本科毕业设计\\目标检测代码\\bubbliiiing-yolov3\\img\\17.jpg")
    }


  },
  methods: {
    uploadpic:function() {
      let that = this;
      axios.post(`http://localhost:5000/test`,
          {"picture":`${that.imgUrl}`}).then(function (response) {
        console.log(response);
        that.imgServerUrl = response.data.img;
        that.ans = response.request.response;
      },function (err){
        console.log(err);
      })
    },

    onChangeUpload(file) {
      let that = this;
      this.getBase64(file.raw).then(res => {
        that.imgUrl = res;
      })
      axios.post(`http://localhost:5000/test`,
          {"picture":`${that.imgUrl}`}).then(function (response) {
        console.log(response);
        that.imgServerUrl = response.data.img;
        that.ans = response.request.response;
      },function (err){
        console.log(err);
      })
      console.log(this.imgUrl);
    },

    getBase64(file) {
      return new Promise(function (resolve, reject) {
        let reader = new FileReader();
        let imgResult = "";
        reader.readAsDataURL(file);
        reader.onload = function () {
          imgResult = reader.result;
        };
        reader.onerror = function (error) {
          reject(error);
        };
        reader.onloadend = function () {
          resolve(imgResult);
        };
      });
    }
  }

}

</script>

<style scoped>
.image-slot{

}

.el-icon-upload{
  width: 50%;
}
</style>