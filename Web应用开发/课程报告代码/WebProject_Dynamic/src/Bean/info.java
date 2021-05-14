package Bean;
import java.util.HashMap;
import java.util.Map;
public class info {
	private String ID;
	private String password;
	private Map<String, String> errors = new HashMap<String, String>();
	
	public String getID() {
		return ID;
	}
	public String getPassword() {
		return password;
	}
	public void setID(String iD) {
		ID = iD;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getErrorMsg(String key) {
		return this.errors.get(key);
	}
	public void setErrors(Map<String, String> errors) {
		this.errors = errors;
	}
	public Map<String, String> getErrors() {
		return errors;
	}
	public boolean isValidate() {
		boolean flag = true;
		System.out.println("进入Bean,开始验证");
		if(!this.ID.matches("\\w{6,15}")) {
			flag = false;
			this.ID="";
			this.errors.put("errID","用户名是6~15位字母或数字");
		}
		if(!this.password.matches("\\w{6,15}")) {
			flag = false;
			this.password = "";
			this.errors.put("errpass","密码是6~15位字母或数字");
		}
		System.out.println("进入Bean,结束   验证");
		return flag;
	}
}
