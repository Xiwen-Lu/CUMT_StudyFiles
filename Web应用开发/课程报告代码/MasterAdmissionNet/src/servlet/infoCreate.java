package servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import factory.DAOFactory;
import vo.Info;

/**
 * Servlet implementation class infoCreate
 */
@WebServlet(description = "createANewInfo", urlPatterns = { "/infoCreate" })
public class infoCreate extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public infoCreate() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
		
		Info info = new Info();
		System.out.print("request参数中获得的School值：");
		System.out.println(request.getParameter("School"));
		info.setSchool(new String(request.getParameter("School").getBytes("iso-8859-1"), "utf-8"));
		System.out.print("request参数中获得的School值（修改编码后）：");
		System.out.println(request.getParameter("School"));
		
		info.setSchoolHomePage(request.getParameter("SchoolHomePage"));
		
		info.setSummerApplyFinishTime(java.sql.Date.valueOf(request.getParameter("SummerApplyFinishTime")));
		info.setSummerActivityStart(java.sql.Date.valueOf(request.getParameter("SummerActivityStart")));
		info.setSummerActivityFinish(java.sql.Date.valueOf(request.getParameter("SummerActivityFinish")));
		
		info.setRecommendationLetterNum(Integer.parseInt(request.getParameter("RecommendationLetterNum")));
		
		info.setPreachLink(request.getParameter("PreachLink"));
		info.setOthers(new String(request.getParameter("Others").getBytes("iso-8859-1"), "utf-8"));
		System.out.println("读取新info表单信息成功");
		try {
			if (DAOFactory.getIInfoDAOInstance().doCreate(info)) {
				System.out.println("添加入数据库成功");
			}
			
			response.sendRedirect("jsp/home.jsp");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			response.sendRedirect("html/insertInfo.html");
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
