package factory;

import dao.*;
import proxy.*;

public class DAOFactory {
	public static IInfoDAO getIInfoDAOInstance() throws Exception{
		return new InfoDAOProxy();
	}
	
	public static IUsersDAO getIUsersDAOInstance() throws Exception {
		return new UsersDAOProxy();
	}
}