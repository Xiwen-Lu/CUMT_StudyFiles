/*接线提示：
*麦克风接0809的INT3，喇叭接0832的0~5v
*0809片选地址0x2A0，0832片选地址
*/
#define port_ADC0809 0x2A0
#define port_DAC0832 0x280
#include<fstream>
#include<iostream>
using namespace std;
struct M_ADC0809 {
	BYTE *Data_Point;//数据区指针
	int port_change;
	M_ADC0809():port_change(port_ADC0809+3) { //以IN3口转换为例
		Data_Point = (BYTE *)malloc(6000);		/*分配空间用于存放录音数据*/
		if(!Data_Point) {
			printf("No memory!\7");
			exit(0);
		}
	}
	void Record() {
		BYTE data;
		printf("Press any key to record!\n");	/*录音提示*/
		getch();
		printf("录音中……\n");	/*录音提示*/
		fstream file;
		file.open("SoundOut.txt",ios::out);
		for(int i=0; i<30000; i++) {
			/*启动A/D,采集6000个数据放在开辟的内存空间中*/
			PortWriteByte(port_change,0);//特色的软启动
			//delay();
			PortReadByte(port_change,&data);//省略检测EOC，等待1ms后便直接读取转换后的数值
			*(Data_Point+i) = data;
			file<<data<<endl;
		}
		file.close();
		printf("录音已结束。\n");	/*录音提示*/
	}
	void Play() {
		printf("Press any key to playing!\n");	/*放音提示*/
		getch();
		BYTE data;
		fstream file;
		file.open("SoundOut.txt",ios::in);
		for(int i=0; i<30000; i++) {
			/*将ii中的6000个从D/A输出*/
			data = *(Data_Point+i);
			PortWriteByte(port_DAC0832,data);
		}
		file.close();
		printf("Playing end!\n");
	}
	void delay(){
		byte d;
			do{
				PortReadByte(0x28a,&d);
			}while(d&1!=0);
			do{
				PortReadByte(0x28a,&d);
			}while(d&1!=1);
	}
};

#define port_8259 0x2A0
struct M_8259 {
	int port_odd;
	int port_even;
	M_8259():port_odd(port_8259+1),port_even(port_8259) {
		Init();
		InterruptMask_Open();
		Wait_Interrupt();
	}
	void InterruptMask_Open() {
		//即写入OCW1开中断
		PortWriteByte(port_odd,0x00);
	}
	void Interrupt_End() {
		//即写入OCW2为00100000来结束刚才服务过的中断
		PortWriteByte(port_even,0x20);
		Wait_Interrupt();
	}
	void IR0(){
		cout<<"中断0"<<endl;
		
		Interrupt_End();
	}
	void IR1(){
		cout<<"中断1"<<endl;
		
		Interrupt_End();
	}

	void Init() {
		PortWriteByte(port_even,0x13);//ICW1
		PortWriteByte(port_odd,0xB0);//ICW2
		PortWriteByte(port_odd,0x03);//ICW4,自动结束终端方式 
	}
	int Read_ISR() {
		byte data;
		PortWriteByte(port_even,0x0B);
		PortReadByte(port_even,&data);
		return data;
	}
	void Wait_Interrupt(){
		cout<<"Wait  Interrupt...."<<endl;
		while(Read_ICheck()==-1){
			Sleep(20);
		}

	}
	int Read_IRR() {
		byte data;
		PortWriteByte(port_even,0x0A);
		PortReadByte(port_even,&data);
		return data;
	}
	int Read_ICheck() {
		//读取中断查询字，最高位表示有无中断，低三位显示是哪一级中断
		byte data;
		PortWriteByte(port_even,0x0C);
		PortReadByte(port_even,&data);
		//cout<<(int)data<<endl;
		if((int)data/128==1){
			switch((int)data%8){
			case 0:IR0();break;
			case 1:IR1();
			default:;
			}
			return (int)data%8;
		}
		else return -1;
	}
	int Read_IMR() {
		byte data;
		PortReadByte(port_odd,&data);
		return data;
	}
};

struct M_rgy {
	int port_h;
	int port_r;
	int Sleep_time;
	
	M_rgy():port_h(0x2B8),port_r(0x2B0),Sleep_time(10) {

	}
	void Print_Kong() {
		byte Lie[8]= {0x04,0xef,0x55,0x22,0x1c,0x08,0x08,0x3e};
		byte h=0x01;
		for(int i=0; i<8; ++i) {
			PortWriteByte(port_r,Lie[i]);
			PortWriteByte(port_h,h);
			h=h<<1;
			Sleep(Sleep_time);
		}
	}
	void Print_Null() {
		PortWriteByte(port_h,0x00);
	}
};

#define port_8255 0x288
#define port_74LS273 0x290
struct M_8255 {
	int port;
	M_8255():port(port_8255) {
		PortWriteByte(port+3,0x81);
	}
};
#include"time.h"
struct LCD:public M_8255 {
	int port_data;
	int port_ctr;
	int Addr_start;
	int Youbiao_isON;
	LCD():M_8255(),port_data(port_74LS273),port_ctr(port_8255+1),Addr_start(128) ,Youbiao_isON(0){};

	void cmd_setup() {
//PC1置0,pc0置0 （LCD I端=0，W端＝0）
		PortWriteByte(port_ctr,0x00);
//PC2置1 （LCD E端＝1）
		PortWriteByte(port_ctr,0x04);
//PC2置0,（LCD E端＝0）
		PortWriteByte(port_ctr,0x01);
	}

	void Clear_All() {
		PortWriteByte(port_data,0x01);
		cmd_setup();
	}

	void data_setup() {
//PC1置0,pc0置0 （LCD I端=0，W端＝0）
		PortWriteByte(port_ctr,0x01);
//PC2置1 （LCD E端＝1）
		PortWriteByte(port_ctr,0x05);
//PC2置0,（LCD E端＝0）
		PortWriteByte(port_ctr,0x01);
	}

	void Display_Line(int n,int data[8]) {
		switch(n) {
			case 1:
				Addr_start=128;
				break;
			case 2:
				Addr_start=144;
				break;
			case 3:
				Addr_start=136;
				break;
			default:
				Addr_start=152;
		}
		for(int i=0; i<8; i++) {
			PortWriteByte(port_data,Addr_start);
			cmd_setup();
			PortWriteByte(port_data,data[i]>>8);
			data_setup();
			PortWriteByte(port_data,data[i]%256);
			data_setup();
			Addr_start++;
		}
	}
	void Display_Update_Car_Empty() {
		struct tm *local;
		time_t t=time(NULL);
		local=localtime(&t);
		cout<<"Date: "<<local->tm_mon<<" / "<<local->tm_mday<<endl;
		cout<<"Time: "<<local->tm_hour<<" : "<<local->tm_min<<endl;

		int B_mon,B_mday,B_hour,B_min;
		B_mon=0x3030+((local->tm_mon+1)/10)*256+(local->tm_mon+1)%10;
		B_mday=0x3030+(local->tm_mday/10)*256+local->tm_mday%10;
		B_hour=0x3030+(local->tm_hour/10)*256+local->tm_hour%10;
		B_min=0x3030+(local->tm_min/10)*256+local->tm_min%10;
		Display_Update_ch(2,3,B_mon);
		Display_Update_ch(2,5,B_mday);
		Display_Update_ch(3,3,B_hour);
		Display_Update_ch(3,5,B_min);
	}
	void Display_Update_ch(int n,int r,int data) {
		switch(n) {
			case 1:
				Addr_start=128;
				break;
			case 2:
				Addr_start=144;
				break;
			case 3:
				Addr_start=136;
				break;
			default:
				Addr_start=152;
		}
		PortWriteByte(port_data,Addr_start+r);
		cmd_setup();
		PortWriteByte(port_data,data>>8);
		data_setup();
		PortWriteByte(port_data,data%256);
		data_setup();
	}

	void Display_Youbiao_ON(){
		//显示游标
		PortWriteByte(port_data,0x0F);
			cmd_setup();
	}
	void Display_Youbiao_OFF(){
		PortWriteByte(port_data,0x0C);
			cmd_setup();
	}
	void Display_Self_Check() {
//
//开机自检，请稍候
//
//
		Clear_All();
		int Data_Self_Check[8]= {0xBFAA,0xBBFA,0xD7D4,0xBCEC,0xA3AC,0xC7EB,0xC9D4,0xBAF2};
		Display_Line(2,Data_Self_Check);
	}
	void Display_Wait_ICcard() {
//
//__ __ 状态正常 __ __
//__ __ 请插入IC 卡 __
//
		Clear_All();
		int Data_Condition_OK[8]= {0xA1A0,0xA1A0,0xD7B4,0xCCAC,0xD5FD,0xB3A3,0xA1A0,0xA1A0};
		int Data_Wait_ICcard[8]= {0xA1A0,0xA1A0,0xC7EB,0xB2E5,0xC8EB,0x4944,0xBFA8,0xA1A0};
		Display_Line(2,Data_Condition_OK);
		Display_Line(3,Data_Wait_ICcard);
	}
	void Display_Setup() {
//__ __ __ 设 置 __ __ __
//起 步 价 :_ __ 07 .0 __
//白 天 单 价 :_ 1. 20 __
//夜 间 单 价 :_ 1. 40 __
		int Data_Setup[8]= {0xA1A0,0xA1A0,0xA1A0,0xC9E8,0xD6C3,0xA1A0,0xA1A0,0xA1A0};
		int Data_Starting_Fare[8]= {0xC6F0,0xB2BD,0xBCDB,0x3A00,0xA1A0,0x3037,0x2E30,0xA1A0};
		int Data_PerPrice_Day[8]= {0xB0D7,0xCCEC,0xB5A5,0xBCDB,0x3A00,0x312E,0x3230,0xA1A0};
		int Data_PerPrice_Night[8]= {0xD2B9,0xBCE4,0xB5A5,0xBCDB,0x3A00,0x312E,0x3430,0xA1A0};
		Display_Line(1,Data_Setup);
		Display_Line(2,Data_Starting_Fare);
		Display_Line(3,Data_PerPrice_Day);
		Display_Line(4,Data_PerPrice_Night);
	}
	void Display_Car_Empty() {
//__ __ __ 欢 迎 __ __ __
//日 期 :_ 12 /_ 09 __ __
//时 间 :_ 15 :_ 30 __ __
//
		int Data_Welcome[8]= {0xA1A0,0xA1A0,0xA1A0,0xBBB6,0xD3AD,0xA1A0,0xA1A0,0xA1A0};
		int Data_Date[8]= {0xC8D5,0xC6DA,0x3A00,0x3132,0x2F00,0x3039,0xA1A0,0xA1A0};
		int Data_Time[8]= {0xCAB1,0xBCE4,0x3A00,0x3135,0x3A00,0x3330,0xA1A0,0xA1A0};
		int Blank[8]= {0xA1A0,0xA1A0,0xA1A0,0xA1A0,0xA1A0,0xA1A0,0xA1A0,0xA1A0};
		Display_Line(1,Data_Welcome);
		Display_Line(2,Data_Date);
		Display_Line(3,Data_Time);
		Display_Line(4,Blank);

		Display_Update_Car_Empty();
	}
	void Display_Update_Car_Full(double Mileage_Thistime,double Price_Thistime) {
		int Meter_0,Meter_1;
		Meter_0=0x2E30+(int)(Mileage_Thistime*10)%10;
		Meter_1=0x3030+(int)Mileage_Thistime/10*256+((int)Mileage_Thistime*10%100/10);
		Display_Update_ch(3,6,Meter_0);
		Display_Update_ch(3,5,Meter_1);
		
		int Money_0,Money_1;
		Money_0=0x2E30+(int)(Price_Thistime*10)%10;
		Money_1=0x3030+(int)Price_Thistime/10*256+((int)Price_Thistime*10%100/10);
		Display_Update_ch(4,6,Money_0);
		Display_Update_ch(4,5,Money_1);
	}
	void Display_Car_Full(double Per_Price) {
//单价 :_ 1. 20 __ __ 元   如：7.0
//时间 :_ 00 :_ 23 __ __  如：1:23   //行驶时间暂时去掉，优先实现完备系统，刚需为里程与计价
//累计 里 程 :_ __ ._ __
//累计 金 额 :_ __ ._ __
		int Data_Per_Price[8]= {0xB5A5,0xBCDB,0x3A00,0x312E,0x3230,0xA1A0,0xA1A0,0xD4AA};
		//int Data_Total_Time[8]= {0xCAB1,0xBCE4,0x3A00,0x3030,0x3A00,0x3031,0xA1A0,0xA1A0};
		int Data_Total_Meter[8]= {0xC0DB,0xBCC6,0xC0EF,0xB3CC,0x3A00,0x3030,0x2E30,0xA1A0};
		int Data_Total_Money[8]= {0xC0DB,0xBCC6,0xBDF0,0xB6EE,0x3A00,0x3037,0x2E30,0xA1A0};
		Display_Line(1,Data_Per_Price);
		//Display_Line(2,Data_Total_Time);
		Display_Line(3,Data_Total_Meter);
		Display_Line(4,Data_Total_Money);
		int Per_p_1=0x302E+(int)Per_Price*256;
		int Per_p_0=0x302E+(int)10*(Per_Price-(int)Per_Price);
		Display_Update_ch(1,3,Per_p_1);
		Display_Update_ch(1,4,Per_p_0);
	}
};


/**测试硬件连接说明
*8255 地址口为288
*8255工作在方式0，A口输入B口输出，C口高4位接行线输出，低4位接列线输入
*
*键盘行线接c口高位输出，列线接c口低位输入
*/
#define port_8255_C 0x28A
struct KeyBoard {
	/**键盘工作流程
	*1. 当行线都拉低时，正常列线应该全为1
	*2. 若出现非1，说明改行按键被按下了，改为逐行拉低去检测是哪一行出现非1
	*3. 继续拉低该行，继续去检测是哪一列非1，在c中，哪一列可以直接计算得到
	**/
	int port_c;
	int result;
	int row;
	int col;
	int ret;//返回按键数值
	byte condition;

	KeyBoard():port_c(port_8255+2) {

		init();
		cout<<"keyboard started."<<endl;
	}
	void init() {
		PortWriteByte(port_c+1,0x81);//控制字：1 00 0 0 00 1  C口高4位输出，低4位输入
	}

	bool IsPRES() {
//拉低所有行，检测列线是否都为1，否，则说明有按键按下，转去read,（*防颤后面扩充）
		PortWriteByte(port_c,0x00);//拉低所有行
		PortReadByte(port_c,&condition);
		if((int)condition%16==15)return false;
		else {
//先引入一步“消颤”，根据实验，
//没有这一步会在一次按下中，多次识别
			Sleep(50);
			PortReadByte(port_c,&condition);
			if((int)condition%16==15) {
				return false;
//isPRES();
			}
			//change();
			//cout<<"PRES!"<<endl;
			//read();
			return true;
		}
	}
	void read() {
		int a=15-condition%15;
		col=0;
		while(a!=0) {
			a/=2;
			col++;
		}
//逐行拉低，读取非1时的该行，同时去计算是哪一列被按下了
		byte line=0xEF;
		row=0;
		do {
			PortWriteByte(port_c,line);
			PortReadByte(port_c,&condition);
			++row;
			line=line<<1;
		} while((int)condition%16==15);

		if(col==1) {
			if(row==1)ret=1;
			else if(row==2)ret=2;
			else if(row==3)ret=3;
		} else if(col==2) {
			if(row==1)ret=4;
			else if(row==2)ret=5;
			else if(row==3)ret=6;
		}
		cout<<"the board is "<<row<<" "<<col<<", ret is "<<ret<<endl;
	}

	int Pressed_Button() {
		//这个函数作为查询式的一个接口函数，始终等待按键按下，一旦按下返回内置的键值
		while(!IsPRES());
		read();
		cout<<"Button "<<ret<<" is Pressed."<<endl;
		return ret;
	}
};

#define port_8254 0x298
struct M_8254 {
	int port_ctr;
	int result;
	M_8254():port_ctr(port_8254+3) {
		Init_Gate0();
		Init_Gate2();
		result=0;
	}
	void Init_Gate0() { //通道0，此段计数初值可供之后中断调用,（之后可以扩充级联操作）
		PortWriteByte(port_ctr,0x30);//控制字：00 11 000 0通道0，二进制计数
		PortWriteByte(port_ctr-3,0x00);
		PortWriteByte(port_ctr-3,0x00);
		cout<<"8254 init, Gate 0 chosed"<<endl;
	}
	void Init_Gate1() { //通道1，此段硬延时产生一个刷新屏幕的频率
		PortWriteByte(port_ctr,0x77);//控制字：01 11 011 1通道1，10进制计数
		PortWriteByte(port_ctr-2,0x00);
		PortWriteByte(port_ctr-2,0x00);
		cout<<"8254 init, Gate 1 chosed"<<endl;
	}
	void Init_Gate2() { //通道2，用于给蜂鸣器输出打印声（未完全）
		PortWriteByte(port_ctr,0xB7);//控制字：10 11 011 1通道2，方式3，BCD计数
		PortWriteByte(port_ctr-1,0xe9);
		PortWriteByte(port_ctr-1,0xf1);
		cout<<"8254 init, Gate 2 chosed"<<endl;
		PortWriteByte(0x289,0x00);//默认为不发声；
	}

	void Buzzer_Call() {
//8255 B7连接Gate2，out连接非门再输出，（因为8254工作在方式3时，Gate为0默认为不计数输出恒高）
		cout<<"Buzzer_Call init"<<endl;
		for(int i=0; i<8; ++i) {
			PortWriteByte(0x289,0x80);
			Sleep(150);//对应发声时间
			cout<<"end:"<<endl;
			PortWriteByte(0x289,0x00);
			Sleep(30);//对应的是沉默时间
		}
		cout<<"Buzzer_Call ended"<<endl;
	}

	int read() {
		PortWriteByte(port_ctr,0x00);//控制字：00 00 000 0通道0锁存
		byte L;
		byte H;
		PortReadByte(port_ctr-3,&L);
		PortReadByte(port_ctr-3,&H);
		result=65536-(256*H+L);
		cout<<"8254计数补值为："<<result<<endl;
		if(result>60000)Init_Gate0();
		return result;
	}
};

#define port_DAC0832 0x280

struct M_DAC0832 {
	int port_ctr;
	int speed;

	M_DAC0832():port_ctr(port_DAC0832),speed(0) {
		PortWriteByte(port_ctr,speed);
		cout<<"M_0832 init, Speed_0 = 0"<<endl;
	}
	void Speed_Update(int sp) {
		PortWriteByte(port_ctr,sp);
		cout<<"Speed update, Speed_now = "<<speed<<endl;
	}

};

struct TAXI:public M_DAC0832,M_8254 {
//TAXI 类继承M_DAC0832芯片,M_8254芯片,在此类中完成里程数计算
//继承speed与加减速，同时自身带有数据成员state状态
//state:0-未启动，1-运行，10-静止等待（运行中，车速0）
	int state;
	double Meter_Total;
	double Meter_Thistime;
	double temp;
	double factor;
	TAXI():M_DAC0832(),state(0),Meter_Thistime(0),Meter_Total(0),temp(0),factor(1440) {};
	double Read_Meter_Thistime() {
		int Now=this->read();
		//8254计数是倒计数，这里在装入下一个计数值时会出现较大误差
		//在出租车速度不快时没有问题，当速度达到五档时有很大误差。
		if(Now>=temp) {
			Meter_Thistime+=(double)(Now-temp)/factor;
			temp=Now;
		} else {
			Meter_Thistime+=(double)(Now)/factor;
			temp=Now;
		}
		return Meter_Thistime;
	}
	double Read_Meter_Total() {
		return Meter_Total+Meter_Thistime;
	}
	void Thistime_Start() {
		Meter_Thistime=0;
		temp=0;
	}
	int Thistime_End() {
		Meter_Total+=Read_Meter_Thistime();
		cout<<"本次运行结束，总里程为："<<Meter_Thistime<<endl;
		return Meter_Thistime;
	}
	void Start_or_SpeedUp() {
		if(state==0) {
			state=1;//汽车启动
			speed=90;
			this->Speed_Update(speed);
			return;
		}
		if(speed<245)speed+=10;
		else speed=254;
		this->Speed_Update(speed);

		if(state==10) {
			state=1;
			cout<<"Taxi continue runing"<<endl;
		}
	}
	void Stop_or_SpeedDown() {
		if(state==10) {
			state=0;
			cout<<"Taxi stop"<<endl;
			return;
		}
		if(speed>70)speed-=10;
		else speed=61;
		Speed_Update(speed);
		if(speed==61) {
			state=10;
			cout<<"Taxi wait"<<endl;
		}
	}
};

struct TAXIMETER {
	int state;
	/**state 代表计价器的状态
	*0 IC卡未插
	*10 重车状态
	*11 空车状态
	*12 自检状态
	*13 设置状态
	*14 计价暂停状态
	**/
	double Per_Price_Day;
	double Per_Price_Night;
	double Per_Price_Now;
	
	double Starting_Price;
	int Total_Times;//累积载客次数
	int Total_Price;
//单次营运中的一些参数
	int Money_Thistime;
	int Time_Start;
	int Time_End;

	LCD lcd;
	M_8255 m_8255;
	M_8254 m_8254;
	KeyBoard kb;
	TAXI taxi;
	M_rgy rgy;

	TAXIMETER():state(0) {
		History_Read();
		//Wait_IC();
	};
	~TAXIMETER() {
//析构函数中可以加“写硬盘”
	}
	void History_Read() {
		//此步可以使用存储器进行断电存储
		Per_Price_Day=1.2;
		Per_Price_Night=1.4;
		taxi.Meter_Total=123;
		Total_Price=374;
		Total_Times=12;
		Starting_Price=7;
		cout<<"Read Log OK, "<<Per_Price_Day<<" "<<Per_Price_Night<<" "
		    <<taxi.Meter_Total<<" "<<Total_Price<<" "<<Total_Times<<" "<<endl;
	}

	void History_Write() {

	}
	double Caculate_Money_Thistime(double meter) {
		double M;
		if(meter<3)M=7;
		else{
		M=Per_Price_Now*(meter-3)+7;
		M*=10;
		M=(int)(M+0.5);
		M=(double)M/10;//精确到小数点后一位
		}
		cout<<"Meter:  "<<meter<<",Money:  "<<M<<endl;
		return M;
	}
	void Journey_Start() {
		state=10;
		struct tm *local;
		time_t t=time(NULL);
		local=localtime(&t);
		if(local->tm_hour>18||local->tm_hour<6)Per_Price_Now=Per_Price_Night;
		else Per_Price_Now=Per_Price_Day;
		rgy.Print_Null();
		taxi.Thistime_Start();
		lcd.Display_Car_Full(Per_Price_Now);
	}
	void Journey_End() {
		state=11;
		rgy.Print_Kong();
		taxi.Thistime_End();
		m_8254.Buzzer_Call();
		Sleep(1000);
		lcd.Display_Car_Empty();
	}
	void State_Change(int ret) {
		//这段函数根据键盘操作执行状态之间的跳转代码，类似于事务中心的转移
		switch(state) {
			case 11: {
				//空车
				if(ret==6)taxi.Start_or_SpeedUp();
				else if(ret==3)taxi.Stop_or_SpeedDown();
				else if(ret==1) {
					Journey_Start();
				} else if(ret==2) {
					state=13;
					lcd.Display_Setup();
				} else return;
				break;
			}
			case 10: {
				//重车状态，仅可以加减速
				if(ret==6)taxi.Start_or_SpeedUp();
				else if(ret==3)taxi.Stop_or_SpeedDown();
				else if(ret==1) {
					Journey_End();
				}
				return;
			}
			case 13: {
				//设置状态，仅可以设置或者加减速
				if(ret==6)taxi.Start_or_SpeedUp();
				else if(ret==3)taxi.Stop_or_SpeedDown();
				else if(ret==2){
					if(lcd.Youbiao_isON==0){
						lcd.Display_Youbiao_ON();
						lcd.Youbiao_isON=1;
					}
					else if(lcd.Youbiao_isON==1){
						lcd.Display_Youbiao_OFF();
						lcd.Youbiao_isON=2;
					}
					else if(lcd.Youbiao_isON==2){
						lcd.Display_Car_Empty();
						lcd.Youbiao_isON=0;
						state=11;
					}
					}
				//else if(ret==5);
				else return;
			}
			default:
				;
		}
	}
	void Wait_IC() {
		lcd.Display_Wait_ICcard();
//接下来查询等待键盘插入IC（按键模拟）
		while(kb.Pressed_Button()!=4);
		state=12;
		Self_Check();
	}
	void Self_Check() {
		lcd.Display_Self_Check();
		Sleep(1500);
		state=11;
		lcd.Display_Car_Empty();
		Update();
//等待空车牌被翻下，或是按键被按下
	}
	void Update() {
		while(1) {
			if(kb.IsPRES()) {
				kb.read();
				State_Change(kb.ret);
			} else {
				switch(state) {
					case 11:
						lcd.Display_Update_Car_Empty();
						rgy.Print_Kong();
						break;
					case 13://此处本为设置，可以加一些反白的操作
						rgy.Print_Kong();
						break;
					case 10:
						lcd.Display_Update_Car_Full(taxi.Read_Meter_Thistime(),Caculate_Money_Thistime(taxi.Meter_Thistime));
						break;
					default:;
				}
			}
		}
	}
};
