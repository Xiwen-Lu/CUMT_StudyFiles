package dao;
import vo.Users;

public interface IUsersDAO {
	public boolean doCreate(Users users) throws Exception;
	public Users findByID(String uid) throws Exception;
}
