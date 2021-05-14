package impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.List;

import dao.IUsersDAO;
import vo.Users;

public class UsersDAOImpl implements IUsersDAO {
	private Connection conn=null;
	private PreparedStatement pstmt=null;
	
	public UsersDAOImpl(Connection conn){
		this.conn = conn;
	}
	
	@Override
	public Users findByID(String uid) throws Exception {
		Users user = null;
		String sql = "SELECT * FROM Users WHERE ID=?" ;
		this.pstmt = this.conn.prepareStatement(sql);
		this.pstmt.setString(1, uid);
		ResultSet rs = this.pstmt.executeQuery();
		while(rs.next()) {
			user = new Users();
			user.setID(rs.getString(1));
			user.setPassword(rs.getString(2));
			user.setRole(rs.getString(3));
			user.setIntegral(rs.getInt(4));
		}
		this.pstmt.close();
		return user;
	}
	
	public boolean doCreate(Users users) throws Exception{
		boolean flag = false;
		String sql = "INSERT INTO Users VALUES(?,?,?,?);";
		this.pstmt = this.conn.prepareStatement(sql);
		this.pstmt.setString(1, users.getID());
		this.pstmt.setString(2, users.getPassword());
		this.pstmt.setString(3, "guest");
		this.pstmt.setInt(4, 0);
		
		if(this.pstmt.executeUpdate()>0) {
			flag = true;
		}
		this.pstmt.close();
		return flag;
	}

}
