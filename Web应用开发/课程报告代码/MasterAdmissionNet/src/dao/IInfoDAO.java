package dao;

import java.util.List;

import vo.Info;;


public interface IInfoDAO {
	public boolean doCreate(Info info) throws Exception ;//执行数据的插入操作

	public List<Info> findAll() throws Exception ;//完成数据 的查询操作
}
