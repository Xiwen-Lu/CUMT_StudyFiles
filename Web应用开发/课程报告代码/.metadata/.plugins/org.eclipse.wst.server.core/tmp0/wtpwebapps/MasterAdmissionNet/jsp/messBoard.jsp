<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="factory.DAOFactory"%>
<%@ page import="vo.Messboard"%>
<%@ page import="java.text.*"%>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>研招信息网——留言板</title>
</head>
	<jsp:useBean id="user" class="vo.Users" scope="session"/>
	<%String str=user.getID(); %>
	<%String role=user.getRole(); %>
	<%if(str!=null){out.print("欢迎您,"+role+":"+ str+"。");}%>
<body style="background-color:rgb(192,192,192);">
<%
List<Messboard> all = DAOFactory.getIMessboardDAOInstance().findAll();
Messboard mess = null;
Iterator<Messboard> iter = all.iterator();


%>


<form method="post" style="position: absolute;left: 50%;top: 60px;transform: translate(-50%,0);">
<h1 style="font-size: 50px;font-family: kaiti;margin-left: 22%">留言交流板</h1>

<table border="0"  autocapitalize="on" style="font-family:fangsong;font-size:22px;border-spacing: 3px">
<tr>

<td width="60">编号</td>
<td width="60">ID</td>
<td width="90">昵称</td>
<td width="600">留言内容</td>
<td width="200">留言时间</td>

</tr>

<%
while(iter.hasNext()){
Messboard mess2 = iter.next() ;
%>
<tr>

<td><%=mess2.getNO()%></td>
<td><%=mess2.getID()%></td>
<td><%=mess2.getNickname()%></td>
<td><%=mess2.getMessage()%></td>
<td><%=mess2.getReleaseTime()%></td>
</tr>
<%
}
%>
</table>
<button type="button" onclick="location.href='../html/insertMess.html'" style="margin-top: 10%;margin-left:200px;width: 80px;height: 40px;">留言</button>
<a target="_blank" href="http://mail.qq.com/cgi-bin/qm_share?t=qm_mailme&email=t9vCz97A0tmGjo6O98bGmdTY2g" style="text-decoration:none;margin-left: 200px;"><img src="http://rescdn.qqmail.com/zh_CN/htmledition/images/function/qm_open/ico_mailme_12.png"/></a>


</form>
</body>
</html>