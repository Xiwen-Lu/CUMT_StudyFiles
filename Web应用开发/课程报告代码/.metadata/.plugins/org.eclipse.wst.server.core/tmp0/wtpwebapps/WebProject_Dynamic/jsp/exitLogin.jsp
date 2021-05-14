<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<jsp:useBean id="simple" class="Bean.info" scope="session"/>
<%session.removeAttribute("simple"); %>
<%response.sendRedirect("../index.jsp"); %>
</body>
</html>