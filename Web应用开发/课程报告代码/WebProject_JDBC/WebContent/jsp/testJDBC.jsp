<%@page import="org.apache.jasper.tagplugins.jstl.core.Catch"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="factory.*"%>
<%@ page import="vo.Info"%>
<%@ page import="java.text.*"%>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>测试jsp</title>
</head>
<body>
hello
<%

	
List<Info> all = DAOFactory.getIInfoDAOInstance().findAll();

Iterator<Info> iter = all.iterator();
while(iter.hasNext()) {
	Info info2 = iter.next();
	System.out.println(info2.getSchool());
	System.out.println(info2.getSummerApplyFinishTime());
	System.out.println(info2.getSummerActivityStart());
	System.out.println(info2.getSummerActivityFinish());
	System.out.println(info2.getRecommendationLetterNum());
	System.out.println(info2.getPreachLink());
	System.out.println(info2.getOthers());
}
%>

</body>
</html>