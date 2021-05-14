package proxy;

import dao.IUsersDAO;
import dbc.DatabaseConnection;
import impl.UsersDAOImpl;
import vo.Users;

public class UsersDAOProxy implements IUsersDAO{
	private DatabaseConnection dbc = null;
	private IUsersDAO dao = null;
	
	public UsersDAOProxy() throws Exception {
		this.dbc = new DatabaseConnection();
		this.dao = new UsersDAOImpl(this.dbc.getConn());
	}
	
	public boolean doCreate(Users users) throws Exception {
		boolean flag = false;
		try {
			flag = this.dao.doCreate(users);
		} catch (Exception e) {
			System.out.println("在创建新的Users表单时出现了问题");
			e.printStackTrace();
		}finally {
			this.dbc.close();
		}
		return flag;
	}

	@Override
	public Users findByID(String uid) throws Exception {
		Users user = null;
		user = this.dao.findByID(uid);
		if (user==null) {
			System.out.println("查找用户失败，根据id : "+uid);
		}
		this.dbc.close();
		return user;
	}
}
