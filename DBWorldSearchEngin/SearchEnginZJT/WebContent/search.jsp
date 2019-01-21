<%@page import="org.apache.catalina.connector.Request"%>
<%@page import="crawler.luceneSearchResult"%>
<%@page import="java.util.ArrayList"%>
<%@page import="crawler.luceneSearch"%>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<%
	String QueryText;
	String QueryField;
	String QueryPage,QueryNext;
	QueryText = request.getParameter("query");
	QueryField = request.getParameter("field");
	QueryPage = request.getParameter("page");
	if(QueryPage == null){
		QueryNext = "1";
	}
	else{
		QueryNext = Integer.toString(Integer.parseInt(QueryPage)+1);
	}
	//System.out.println(QueryField);
	//System.out.println(QueryText.equals(""));
%>
<html>
	<head>
		<meta charset="UTF-8">
		<title>DBWord SearchEngin-ZJT</title>
	</head>
	<body>
		 <form method = "POST" action = "search.jsp">
			<p align = "center"><font size = "12" face="楷体-简 黑体" color = "#FF0000">DBWorld搜索引擎</font></p>
			<p align = "center">
		 		<font size = "5" color = "#FF0000" face="楷体-简 黑体">
					<!-- <font size = "5" face="楷体-简 黑体" color = "#FF0000">主题</font> -->
					<select name = "field" style = "width:80px; height:40px; font-style:oblique; color: #FF0000">
						<option value = "subject">主题</option>
						<option selected value = "content">内容</option>
						<option value = "ddl">截止日期</option>
						<option value = "from">发布者</option>
						<option value = "content" >相关地点</option>
					</select>
					<input type = "text"   name = "query"  value="<%= QueryText %>" style = "width:400px;height:40px" id="t1">
					<input type = "submit" value = "搜索"   style = "width:80px; height:40px; font-style:oblique;color: #FF0000"  id="button">
					前往第   
    				<input type = "text" name = "page" style = "width:50px;height:40px" value="<%= QueryNext %>" >
    				页
    				<input type = "submit" value = "跳转" style = "width:70px;height:40px">
		        </font>
	    	</p>
		</form>
		 <%
			luceneSearch S = new luceneSearch();
			ArrayList<luceneSearchResult> results;
			if(QueryText.equals("")){
				out.println("<font color = \"#FF0000\" size = \"8\">");
	            out.print("抱歉,输入为空");
	            out.println("</font>" + "<br>");
			}
			else{
				int Page = 1, size = 0;
				if( QueryPage != null && QueryPage.length()!=0)
					Page = Integer.parseInt(QueryPage);
				if(QueryText != null){
					results = S.search(QueryField,QueryText);
					size = results.size();
				    out.println("<font color = \"#7FFF00\" size = \"5\" face=\"楷体-简 黑体\">" + "找到了 " + size + " 个结果");
				    out.println("<font size = \"5\" face=\"楷体-简 黑体\">" + "每页最多显示10条,当前是第 " + Page + " 页, 共计" + ((size-1)/ 10 + 1) + "页");
				    out.println("</font>" + "<br><br>");
				    ArrayList<luceneSearchResult> PageResults = new ArrayList<luceneSearchResult>();
				    if(size > (Page-1)*10 && Page > 0){
			            for (int i = 0; i < 10; i++) {
			                if((Page-1)*10+i < size)
			                	PageResults.add(results.get((Page-1)*10+i));
			            }
				    }
			        else if(size != 0){
			            out.println("<font color = \"red\" size = \"4\" face=\"楷体-简 黑体\"> ");
			            out.print("抱歉,超出了页数范围: 1 - " + ((size-1)/10+1));
			            out.println("</font>" + "<br>");
			        }
					if(PageResults.size() > 0){
						for(luceneSearchResult re:PageResults){
							out.println("<font color = \"#7CFC00\" size = \" 5 \">");
							out.println("<a href=\" " + re.subjecturl.replace("http://www", "https://research") + "\">" + re.subject + "</a>");
							out.println("<font><br>");
							out.println("<font color = \"#030303\" size = \" 5 \" face=\"楷体-简 黑体\">");
							out.println("<strong>截止时间： </strong>" + re.ddl + "<br>");
							out.println("<strong>发布者： </strong>" + re.from + "<br>");
							out.println("<strong>相关链接： </strong>" + "<a href=\" " + re.webpageurl + "\">" + re.subject + "</a>" + "<br>");
							out.println("<font><br>");
						}
					}
					else{
						out.println("<font color = \"#FF0000\" size = \"5\">");
			            out.print("抱歉,没有找到" + QueryText);
			            out.println("</font>" + "<br>");
					}
				}
			}
		 %>
	</body>
</html>