import java.sql.Connection;
import java.util.Iterator;
import java.util.List;

import dbc.DatabaseConnection;
import factory.*;
import vo.Info;
public class testJDBC {

	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		testJDBCconnect();
	}
	
	static void testFindAll() {
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
