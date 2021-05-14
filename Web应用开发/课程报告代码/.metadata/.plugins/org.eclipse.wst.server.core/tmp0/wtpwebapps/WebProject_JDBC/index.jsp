<%@page import="vo.Users"%>
<%@page import="sun.java2d.pipe.SpanShapeRenderer.Simple"%>
<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>研招信息主页</title>
</head>

	<jsp:useBean id="user" class="vo.Users" scope="session"/>
	<%String str=user.getID(); %>
	<%String role=user.getRole(); %>
	<%if(str!=null){out.print("欢迎您,"+role+":"+ str+"。");session.setAttribute("user", user); %>
	<%} %>


<body>

<div style="background-color:#9B59B6;height: 200px;"></div>
<div style="text-align: center;font-family: unset !important;font-size: 40px;border-bottom: 30px;border-top: 240px;height: 50px;">
<a href="./jsp/login.jsp">登录</a>
&ensp;&emsp;
<a href="./jsp/zhuce.jsp">注册</a>
&ensp;&emsp;
<a href="./jsp/home.jsp">主页</a>

</div>
<div style="background-color:#9B59B6;height: 280px;"></div>
</body>
</html>