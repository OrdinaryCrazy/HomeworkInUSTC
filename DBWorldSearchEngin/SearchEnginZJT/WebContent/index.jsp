<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8"%>
<html>
	<head>
		<title>DBWord SearchEngin-ZJT</title>
		<style type="text/css">
		body{
			background:url(./psb.jpeg);
	        background-size:100% 100%;
	        background-repeat:no-repeat;
	        padding-top:80px;
		}
		H1{
			font-style:oblique;
			color: #FF0000;
		}
	</style>
	</head>
	<body>
		<H1>Today is:<%= new java.util.Date() %><br>
			<%out.println("Your address is:" + request.getRemoteAddr()); %>
		</H1>
		<form method = "POST" action = "search.jsp">
			<p align = "center"><font size = "12" face="楷体-简 黑体" color = "#FF0000">DBWorld搜索引擎</font></p>
			<p align = "center">
		 		<font size = "15">
					<!-- <font size = "5" face="楷体-简 黑体" color = "#FF0000">主题</font> -->
					<select name = "field" style = "width:80px; height:40px; font-style:oblique; color: #FF0000">
						<option value = "subject">主题</option>
						<option selected value = "content">内容</option>
						<option value = "ddl">截止日期</option>
						<option value = "from">发布者</option>
						<option value = "content" >相关地点</option>
					</select>
					<input type = "text"   name = "query"  style = "width:400px;height:40px" id="t1">
					<input type = "submit" value = "搜索"   style = "width:80px; height:40px; font-style:oblique;color: #FF0000"  id="button">
		        </font>
	    	</p>
		</form>
	</body>
</html>