<%@page import="vo.Users"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="factory.DAOFactory"%>
<%@ page import="java.text.*"%>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>

<jsp:useBean id="user" scope="session" class="vo.Users"/>
<jsp:setProperty property="*" name="user"/>

<body>
<%if(user.isValidate()){ %>
<%
//开始向数据库写入该组有效注册
try{
	if(DAOFactory.getIUsersDAOInstance().doCreate(user)){
		System.out.println("注册用户加入数据库成功");
	}
}catch(Exception e){
		System.out.println("注册用户加入数据库失败");
}
%>
<script type="text/javascript">
alert("注册成功");
</script>

<jsp:setProperty property="role" name="user" value="guest" />
<jsp:forward page="../html/zhuceSucc.html"/>
<%}else{ %>

<jsp:forward page="../jsp/zhuce.jsp"/>
<%} %>

</body>
</html>