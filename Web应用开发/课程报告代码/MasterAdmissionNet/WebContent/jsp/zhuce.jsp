<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>齐心抗疫，共克时艰——注册</title>
<link type="text/css" rel="stylesheet" href="../css/zhuce.css" />
<script type="text/javascript" src="../js/jquery-1.11.1.min.js"></script>
<script type="text/javascript">
$(document).ready(function () {
	var height=$(document).height();
	$('.main').css('height',height);
})
</script>
</head>

<body>
<jsp:useBean id="user" class="vo.Users" scope="session"/>
<form action="../jsp/zhuceCheck.jsp" method="post" name="loginForm" class="info">
<div class="main">
  <div class="main0">
     <div class="main_left">
        <img src="../images/zhuce-image-1.png" class="firimg"/>
     </div>
     <div class="main_right">
        <div class="main_r_up">
            <img src="../images/user.png" />
            <div class="pp">注册</div>
        </div>
        <div class="sub"><p>已经注册？<a href="./login.html"><span class="blue">请登录</span></a></p></div>
        <div class="txt">
            <span style="letter-spacing:10px;">账号:</span>
            <input name="ID" type="text" class="txtphone" placeholder="请设置账号"/>

        </div>
        <div class="txt">
            <span style="letter-spacing:10px;">密码:</span>
            <input name="password" type="password" class="txtphone" placeholder="请设置密码"/>

        </div>
        <input type="submit" value="提交" class="xiayibu">
     </div>
  </div>
</div>
</form>

<footer>
     制作：陆玺文&emsp;计科6班&emsp;03170908&ensp;.
</footer>

<!-- 下面是针对性的错误提示  -->

<%String str=user.getErrorMsg("errID");if(str!=null){ %>
            <script type="text/javascript" lang="javascript"> alert("<%=str%>"); </script>
<%} %>
<%String pass=user.getErrorMsg("errpass");if(pass!=null){ %>
            <script type="text/javascript" lang="javascript"> alert("<%=pass%>"); </script>
<%} %>

</body>
</html>
