package vo;

import java.sql.Date;

public class Info {
	private int NO;
	private String School;
	private String SchoolHomePage;
	private Date SummerApplyFinishTime;
	private Date SummerActivityStart;
	private Date SummerActivityFinish;
	private int RecommendationLetterNum;
	private String PreachLink;
	private String Others;
	public int getNO() {
		return NO;
	}
	public String getSchool() {
		return School;
	}
	public Date getSummerApplyFinishTime() {
		return SummerApplyFinishTime;
	}
	public Date getSummerActivityStart() {
		return SummerActivityStart;
	}
	public Date getSummerActivityFinish() {
		return SummerActivityFinish;
	}
	public int getRecommendationLetterNum() {
		return RecommendationLetterNum;
	}
	public String getPreachLink() {
		return PreachLink;
	}
	public String getOthers() {
		return Others;
	}
	public String getSchoolHomePage() {
		return SchoolHomePage;
	}
	public void setSchoolHomePage(String schoolHomePage) {
		SchoolHomePage = schoolHomePage;
	}
	public void setNO(int nO) {
		NO = nO;
	}
	public void setSchool(String school) {
		School = school;
	}
	public void setSummerApplyFinishTime(Date summerApplyFinishTime) {
		SummerApplyFinishTime = summerApplyFinishTime;
	}
	public void setSummerActivityStart(Date summerActivityStart) {
		SummerActivityStart = summerActivityStart;
	}
	public void setSummerActivityFinish(Date summerActivityFinish) {
		SummerActivityFinish = summerActivityFinish;
	}
	public void setRecommendationLetterNum(int recommendationLetterNum) {
		RecommendationLetterNum = recommendationLetterNum;
	}
	public void setPreachLink(String preachLink) {
		PreachLink = preachLink;
	}
	public void setOthers(String others) {
		Others = others;
	}
	
}
