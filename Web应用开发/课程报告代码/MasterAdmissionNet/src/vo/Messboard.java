package vo;

import java.sql.Date;

public class Messboard {
	private int NO;
	private String ID;
	private String nickname;
	private String message;
	private Date releaseTime;
	public int getNO() {
		return NO;
	}
	public String getID() {
		return ID;
	}
	public String getNickname() {
		return nickname;
	}
	public String getMessage() {
		return message;
	}
	public Date getReleaseTime() {
		return releaseTime;
	}
	public void setNO(int nO) {
		NO = nO;
	}
	public void setID(String iD) {
		ID = iD;
	}
	public void setNickname(String nickname) {
		this.nickname = nickname;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public void setReleaseTime(Date releaseTime) {
		this.releaseTime = releaseTime;
	}
}
