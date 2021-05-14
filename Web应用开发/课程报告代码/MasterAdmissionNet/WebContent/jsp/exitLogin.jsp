<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<jsp:useBean id="simple" class="vo.Info" scope="session"/>
<%session.removeAttribute("simple"); %>
<%response.sendRedirect("../index.jsp"); %>
</body>
</html>