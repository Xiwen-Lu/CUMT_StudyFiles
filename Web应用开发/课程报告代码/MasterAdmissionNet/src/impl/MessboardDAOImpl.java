package impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import dao.IMessboardDAO;
import vo.Messboard;

public class MessboardDAOImpl implements IMessboardDAO {
	private Connection conn=null;
	private PreparedStatement pstmt=null;
	
	public MessboardDAOImpl(Connection conn) {
		this.conn = conn;
	}
	@Override
	public boolean doCreate(Messboard messboard) throws Exception {
		boolean flag = false;
		String sql = "INSERT INTO Messboard VALUES(DEFAULT,?,?,?,?);";
		this.pstmt = this.conn.prepareStatement(sql);
		this.pstmt.setString(1, messboard.getID());
		this.pstmt.setString(2, messboard.getNickname());
		this.pstmt.setString(3, messboard.getMessage());
		this.pstmt.setDate(4, messboard.getReleaseTime());
		
		if(this.pstmt.executeUpdate()>0) {
			flag = true;
		}
		this.pstmt.close();
		return flag;
	}
	@Override
	public List<Messboard> findAll() throws Exception {
		List<Messboard> all = new ArrayList<Messboard>();
		String sql = "SELECT * FROM Messboard";
		this.pstmt = this.conn.prepareStatement(sql);
		
		ResultSet rs = this.pstmt.executeQuery();
		
		Messboard messboard = null;
		while (rs.next()) {
			messboard = new Messboard();
			messboard.setNO(rs.getInt(1));
			messboard.setID(rs.getString(2));
			messboard.setNickname(rs.getString(3));
			messboard.setMessage(rs.getString(4));
			messboard.setReleaseTime(rs.getDate(5));
			all.add(messboard);
		}
		return all;
	}
}
