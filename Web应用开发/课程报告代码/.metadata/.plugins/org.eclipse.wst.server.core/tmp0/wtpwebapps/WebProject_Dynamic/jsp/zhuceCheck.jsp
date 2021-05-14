<%@page import="Bean.info"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<jsp:useBean id="simple" scope="session" class="Bean.info"/>
<jsp:setProperty property="*" name="simple"/>

<body>
<%
if(simple.isValidate()){
%>
<script type="text/javascript">
alert("Succ");
</script>
<jsp:forward page="../html/zhuceSucc.html"/>
<%
}else{
%>
<jsp:forward page="../jsp/zhuce.jsp"/>
<%
}
%>
</body>
</html>