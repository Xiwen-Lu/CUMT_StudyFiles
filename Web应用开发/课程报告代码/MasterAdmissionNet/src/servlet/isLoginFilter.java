package servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import vo.Users;

/**
 * Servlet Filter implementation class isLoginFilter
 */
@WebFilter(description = "isLogin", urlPatterns = { "/jsp/home.jsp" ,"/jsp/messBoard.jsp"})
public class isLoginFilter implements Filter {

    /**
     * Default constructor. 
     */
    public isLoginFilter() {
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
		// TODO Auto-generated method stub
		// place your code here
		System.out.println("过滤器开始执行过滤");
        HttpServletRequest request = (HttpServletRequest) servletRequest;
        HttpServletResponse response = (HttpServletResponse) servletResponse;

        HttpSession session = request.getSession();
        String currPath = request.getRequestURI();    //当前请求的URL
        System.out.println("当前URL为："+currPath);
        Users user = (Users)session.getAttribute("user"); 
        if(user!=null)System.out.println("当前session对象中user对象的ID值为："+user.getID());
        if (user!=null&&user.getID() != null) {
        	String role = user.getRole();
        	System.out.println("用户已登录，权限为"+role);
        	if(role.equals("guest"))response.sendRedirect("homeGuest.jsp");
//        	response.sendRedirect("./home.html");不能加这句！！会无限跳转报senderror
        } else {
        	System.out.println("还没有登录");
            response.sendRedirect("../html/jumplogin.html");
        }

		// pass the request along the filter chain
		filterChain.doFilter(request, response);
	}

	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException {
		// TODO Auto-generated method stub
	}

}
