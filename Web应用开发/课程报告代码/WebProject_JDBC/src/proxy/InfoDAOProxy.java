package proxy;

import dbc.DatabaseConnection;
import impl.InfoDAOImpl;
import vo.Info;

import java.util.List;

import dao.IInfoDAO;

public class InfoDAOProxy implements IInfoDAO{
	private DatabaseConnection dbc=null;
	private IInfoDAO dao=null;
	
	public InfoDAOProxy()throws Exception{
		this.dbc = new DatabaseConnection();
		this.dao = new InfoDAOImpl(this.dbc.getConn());
	}
	
	public List<Info> findAll()throws Exception{
		List<Info> all=null;
		try {
			all=this.dao.findAll();
		}catch (Exception e) {
			throw e;
		}finally {
			this.dbc.close();
		}
		return all;
	}

	@Override
	public boolean doCreate(Info info) throws Exception {
		boolean flag = false;
		try {
			flag=this.dao.doCreate(info);
		}catch (Exception e) {
			System.out.println("在创建新的info表单时出现了问题");
			throw e;
		}finally {
			this.dbc.close();
		}
		return flag;
	}
}
