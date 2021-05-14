package dao;

import java.util.List;

import vo.Messboard;

public interface IMessboardDAO {
	public boolean doCreate(Messboard messboard) throws Exception ;//执行数据的插入操作
	public List<Messboard> findAll() throws Exception ;//完成数据 的查询操作
}
