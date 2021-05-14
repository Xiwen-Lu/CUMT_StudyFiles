package servlet;

import java.io.IOException;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import factory.DAOFactory;
import vo.Messboard;
import vo.Users;

/**
 * Servlet implementation class messCreate
 */
@WebServlet(description = "create a new message", urlPatterns = { "/messCreate" })
public class messCreate extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public messCreate() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.getWriter().append("Served at: ").append(request.getContextPath());
		
		Messboard mess= new Messboard();
		mess.setNickname(new String(request.getParameter("nickname").getBytes("iso-8859-1"),"utf-8"));
		mess.setMessage(new String(request.getParameter("message").getBytes("iso-8859-1"),"utf-8"));
		mess.setReleaseTime(new java.sql.Date(new java.util.Date().getTime()));
		HttpSession session = request.getSession();
		Users user = (Users)session.getAttribute("user"); 
        System.out.println("当前session对象中user对象的ID值为："+user.getID());
        if (user.getID()==null) {
			mess.setID("guest");
		}else {
			mess.setID(user.getID());
		}
        
        try {
        	if(DAOFactory.getIMessboardDAOInstance().doCreate(mess))
        		System.out.println("添加新的留言成功");
        	
        	response.sendRedirect("jsp/messBoard.jsp");
        }catch (Exception e) {
        	e.printStackTrace();
        	response.sendRedirect("html/insertMess.html");
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
