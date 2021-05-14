import java.sql.Connection;
import java.util.Iterator;
import java.util.List;

import dbc.DatabaseConnection;
import factory.*;
import vo.Info;
import vo.Messboard;
public class testJDBC {

	public static void main(String[] args) throws Exception{
//		testJDBCconnect();
//		testMessboarddoCreate();
		System.out.println(new java.sql.Date(new java.util.Date().getTime()));
	}
	static void testMessboardFindAll() {
		try {
			List<Messboard> all = DAOFactory.getIMessboardDAOInstance().findAll();
			Messboard mess = null;
			Iterator<Messboard> iter = all.iterator();
			while(iter.hasNext()) {
				Messboard mess2 = iter.next() ;
				System.out.println(mess2.getNO());
				System.out.println(mess2.getID());
				System.out.println(mess2.getNickname());
				System.out.println(mess2.getMessage());
				System.out.println(mess2.getReleaseTime());
			}
		}catch (Exception e) {
			System.out.println("出现了异常");
		}
	}
	static void testMessboarddoCreate() throws Exception {
		Messboard mess=new Messboard();
		mess.setID("1234");
		mess.setNickname("test");
		mess.setMessage("数据库加入测试");
		mess.setReleaseTime(java.sql.Date.valueOf("2020-5-4"));
		boolean flag = DAOFactory.getIMessboardDAOInstance().doCreate(mess);
		System.out.println(flag);
	}
	static void testInfoFindAll() {
		try {
			List<Info> all = DAOFactory.getIInfoDAOInstance().findAll();
			Info info = null;
			Iterator<Info> iter = all.iterator();
			while(iter.hasNext()) {
				Info info2 = iter.next();
				System.out.println(info2.getSchool());
				System.out.println(info2.getSummerApplyFinishTime());
				System.out.println(info2.getSummerActivityStart());
				System.out.println(info2.getSummerActivityFinish());
				System.out.println(info2.getRecommendationLetterNum());
				System.out.println(info2.getPreachLink());
				System.out.println(info2.getOthers());
			}
		} catch (Exception e) {
			System.out.println("出现了异常");
		}
	}
	static void testJDBCconnect() throws Exception {
		Connection conn = new DatabaseConnection().getConn();
		System.out.println(conn);
	}
}
