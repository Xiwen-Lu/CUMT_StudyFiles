<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>齐心抗疫，共克时艰——登录成功</title>
<link type="text/css" rel="stylesheet" href="../css/zhuce.css" />

</head>
<body>

<jsp:useBean id="simple" scope="session" class="vo.Users"/>
<jsp:setProperty property="*" name="simple"/>

<%
session.setAttribute("ID", simple.getID());
session.setAttribute("password", simple.getPassword());
session.setAttribute("role", simple.getRole());
%>

<div class="main">
  <div class="main0">
  <div class="font24">登录成功，即将自动跳转到首页！</div>
     <div class="main_left">
        <img src="../images/zhuce-image-1.png" class="theimg"/>
     </div>
  </div>
</div>

<script type="text/javascript">
	setTimeout(go, 3000);
	function go(){
		location.href="../index.jsp"; 
	}
</script>

<footer>
    制作：陆玺文&emsp;计科6班&emsp;03170908&ensp;.
</footer>
</body>
</html>
