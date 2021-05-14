package proxy;

import java.util.List;

import dao.IInfoDAO;
import dao.IMessboardDAO;
import dbc.DatabaseConnection;
import impl.MessboardDAOImpl;
import vo.Info;
import vo.Messboard;

public class MessboardDAOProxy implements IMessboardDAO {
	private DatabaseConnection dbc=null;
	private IMessboardDAO dao=null;
	
	public MessboardDAOProxy() throws Exception {
		this.dbc = new DatabaseConnection();
		this.dao = new MessboardDAOImpl(this.dbc.getConn());
		System.out.println("获取DAO成功");
	}
	
	@Override
	public boolean doCreate(Messboard messboard) throws Exception {
		boolean flag = false;
		try {
			flag=this.dao.doCreate(messboard);
		}catch (Exception e) {
			System.out.println("在创建新的messboard表单时出现了问题");
			throw e;
		}finally {
			this.dbc.close();
		}
		return flag;
	}

	@Override
	public List<Messboard> findAll() throws Exception {
		List<Messboard> all=null;
		try {
			all=this.dao.findAll();
			System.out.println("获取所有数据完成");
		}catch (Exception e) {
			System.out.println("留言板查找全部出现了异常");
			throw e;
		}finally {
			this.dbc.close();
		}
		return all;
	}

}
