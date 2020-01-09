//控制台输出模拟LCD液晶屏的输出
#include<iostream>
using namespace std;

void UI_Setup(){
	cout<<"**模拟LCD液晶屏界面--设置**"<<endl;
	cout<<"    ----------------"<<endl;
	cout<<"  ||      设置      ||"<<endl;
	cout<<"  ||起步价：  07.0  ||"<<endl;
	cout<<"  ||白天单价：1.20  ||"<<endl;
	cout<<"  ||夜间单价：1.40  ||"<<endl;
	cout<<"    ----------------"<<endl;	
}

void UI_Setup_Money(){
	cout<<"**模拟LCD液晶屏界面--等待插卡**"<<endl;
	cout<<"    ----------------"<<endl;
	cout<<"  ||                ||"<<endl;
	cout<<"  ||    状态正常    ||"<<endl;
	cout<<"  ||    请插入ID卡  ||"<<endl;
	cout<<"  ||                ||"<<endl;
	cout<<"    ----------------"<<endl;	
}

void UI_Setup_Time(){
	cout<<"**模拟LCD液晶屏界面--时间设置**"<<endl;
	cout<<"    ----------------"<<endl;
	cout<<"  ||      欢迎      ||"<<endl;
	cout<<"  ||日期：12/ 13    ||"<<endl;
	cout<<"  ||时间：16: 33    ||"<<endl;
	cout<<"  ||                ||"<<endl;
	cout<<"    ----------------"<<endl;	
}

void UI_DaiJi(){
	cout<<"**模拟LCD液晶屏界面--运行**"<<endl;
	cout<<"    ----------------"<<endl;
	cout<<"  ||单价: 1.00    元||"<<endl;
	cout<<"  ||日期: 12/ 17    ||"<<endl;
	cout<<"  ||累计里程: 07.1  ||"<<endl;
	cout<<"  ||累计金额：12.0  ||"<<endl;
	cout<<"    ----------------"<<endl;
}

void UI_YunXing(){
	cout<<"**模拟LCD液晶屏界面--运行**"<<endl;
	cout<<"    ----------------"<<endl;
	cout<<"  ||                ||"<<endl;
	cout<<"  ||开机自检，请稍后||"<<endl;
	cout<<"  ||                ||"<<endl;
	cout<<"  ||                ||"<<endl;
	cout<<"    ----------------"<<endl;
}

void UI_Log(){
	cout<<"**模拟LCD液晶屏界面--日志**"<<endl;
	cout<<"    ----------------"<<endl;
	cout<<"  ||日期:      11/21||"<<endl;
	cout<<"  ||载客次数:     06||"<<endl;
	cout<<"  ||总里程:     03.8||"<<endl;
	cout<<"  ||总收入：   07.00||"<<endl;
	cout<<"    ----------------"<<endl;	
}

int main(){
	UI_YunXing();
	UI_Setup();
	UI_DaiJi();
	
	UI_Setup_Money();
	UI_Setup_Time();
	system("pause");
	return 0;
} 
