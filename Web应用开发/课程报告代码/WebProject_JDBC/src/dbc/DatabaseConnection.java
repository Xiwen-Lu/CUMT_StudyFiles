package dbc;

import java.sql.Connection ;
import java.sql.DriverManager ;
import java.sql.SQLException ;

public class DatabaseConnection {
	//定义MySql的数据库驱动程序
	private static final String DBDRIVER="com.mysql.cj.jdbc.Driver";
	//定义MySQL数据库的连接地址
	private static final String DBURL="jdbc:mysql://localhost:3306/masterschool?serverTimezone=GMT";
//	MySQL数据库的连接用户名
	private static final String DBUSER="EricLu";
//	MySQL数据库的连接密码
	private static final String DBPASS="lu168681816";
	private Connection conn;

	public DatabaseConnection() throws Exception{     //无参构造函数
		Class.forName(DBDRIVER);
		this.conn=DriverManager.getConnection(DBURL, DBUSER, DBPASS);
	}	
	public Connection getConn() {//get 方法
		return conn;
	}
	public void setConn(Connection conn) {//set 方法
		this.conn = conn;
	}
	public void close() throws Exception {//close方法
		if(this.conn != null){
			try{
				this.conn.close() ;
			}catch(Exception e){
				throw e ;
			}
		}
	}
}
