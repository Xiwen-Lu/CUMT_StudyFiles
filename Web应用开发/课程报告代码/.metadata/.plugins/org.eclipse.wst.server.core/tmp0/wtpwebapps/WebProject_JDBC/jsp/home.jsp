<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="factory.DAOFactory"%>
<%@ page import="vo.Info"%>
<%@ page import="java.text.*"%>
<%@ page import="java.util.*" %>
<html>
<head>
<meta charset="UTF-8">
<title>研招信息网——主页</title>
</head>
	<jsp:useBean id="user" class="vo.Users" scope="session"/>
	<%String str=user.getID(); %>
	<%String role=user.getRole(); %>
	<%if(str!=null){out.print("欢迎您,"+role+":"+ str+"。");}%>
<body style="background-color:rgb(192,192,192);">
<%
List<Info> all = DAOFactory.getIInfoDAOInstance().findAll();
Info info = null;
Iterator<Info> iter = all.iterator();


%>


<form method="post" style="position: absolute;left: 50%;top: 60px;transform: translate(-50%,0);">
<table border="1">
<tr>

<td>编号</td>
<td width="30">学校</td>
<td>夏令营宣讲地址</td>
<td width="60">报名截止时间</td>
<td>夏令营开始时间</td>
<td>夏令营结束时间</td>
<td>推荐信数量</td><td>其他备注</td>
</tr>

<%
while(iter.hasNext()){
Info info2 = iter.next() ;
%>
<tr>

<td><%=info2.getNO()%></td>
<td><a href=<%=info2.getSchoolHomePage()%>><%=info2.getSchool()%></a></td>
<td><a href=<%=info2.getPreachLink()%>><%=info2.getPreachLink()%></a></td>
<td><%=info2.getSummerApplyFinishTime()%></td>
<td><%=info2.getSummerActivityStart()%></td>
<td><%=info2.getSummerActivityFinish()%></td>
<td><%=info2.getRecommendationLetterNum()%></td>
<td><%=info2.getOthers()%></td>
</tr>
<%
}
%>
</table>
<button type="button" onclick="location.href='../html/insertInfo.html'" style="margin-top: 10%;margin-left:200px;width: 80px;height: 40px;">增加</button>


</form>
</body>
</html>