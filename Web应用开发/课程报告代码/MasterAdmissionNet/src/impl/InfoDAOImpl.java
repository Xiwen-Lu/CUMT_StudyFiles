package impl;
import vo.Info;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import org.omg.CORBA.PRIVATE_MEMBER;

import dao.IInfoDAO;
import vo.Info;

public class InfoDAOImpl implements IInfoDAO {
	private Connection conn=null;
	private PreparedStatement pstmt=null;
	
	public InfoDAOImpl(Connection conn){
		this.conn = conn;
	}
	@Override
	public List<Info> findAll() throws Exception {
		// TODO Auto-generated method stub
		List<Info> all = new ArrayList<Info>();
		
		String sql = "SELECT * FROM Info";
		this.pstmt = this.conn.prepareStatement(sql);
		
		ResultSet rs = this.pstmt.executeQuery();
		
		Info info=null;
		while(rs.next()) {
			info=new Info();
			info.setNO(rs.getInt(1));
			info.setSchool(rs.getString(2));
			info.setSchoolHomePage(rs.getString(3));
			info.setSummerApplyFinishTime(rs.getDate(4));
			info.setSummerActivityStart(rs.getDate(5));
			info.setSummerActivityFinish(rs.getDate(6));
			info.setRecommendationLetterNum(rs.getInt(7));
			info.setPreachLink(rs.getString(8));
			info.setOthers(rs.getString(9));
			all.add(info);
		}
		return all;
	}
	@Override
	public boolean doCreate(Info info) throws Exception {
		boolean flag = false;
		String sql = "INSERT INTO Info VALUES(?,?,?,?,?,?,?,?,?);";
		//为了实现编号自动加一
		String sql_count = "SELECT count(*) num from info;";
		Statement stmt = this.conn.createStatement();
		ResultSet rs_count = stmt.executeQuery(sql_count);
		rs_count.next();
		int row_count = rs_count.getInt("num");
		stmt.close();
		
		this.pstmt = this.conn.prepareStatement(sql);
		this.pstmt.setInt(1, row_count+1);
		this.pstmt.setString(2, info.getSchool());
		this.pstmt.setString(3, info.getSchoolHomePage());
		this.pstmt.setDate(4, info.getSummerApplyFinishTime());
		this.pstmt.setDate(5, info.getSummerActivityStart());
		this.pstmt.setDate(6, info.getSummerActivityFinish());
		this.pstmt.setInt(7, info.getRecommendationLetterNum());
		this.pstmt.setString(8, info.getPreachLink());
		this.pstmt.setString(9, info.getOthers());
		
		if(this.pstmt.executeUpdate()>0) {
			flag = true;
		}
		this.pstmt.close();
		return flag;
	}

}
