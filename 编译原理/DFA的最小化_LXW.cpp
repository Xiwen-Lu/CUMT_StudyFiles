#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int main(){
	cout<<"请输入转移字符数量、转移状态数量："<<endl;
	int Num_char;cin>>Num_char;
	int Num_con;cin>>Num_con;
	cout<<"请输入转移字符（不包含epsilon，无需输入）："<<endl;
	char* change_char=new char[Num_char+1];
	for(int i=1;i<Num_char+1;++i)cin>>change_char[i];
	
	int change[Num_con][Num_char+2]={};
	cout<<"请输入DFA状态转换矩阵，格式为（开始状态  转移状态1  转移状态2 子集号）如 1 6 3 1。"<<endl;
	int s,e,c;
	for(int i=0;i<Num_con;++i)
		for(int j=0;j<Num_char+2;++j)
			cin>>change[i][j];
	
	int v[Num_con];//v用于记录每一轮次内，改行对应的子集号是否需要修改
	for(int i=0;i<Num_con;++i)v[i]=0;//第一行始终不用修改
	//第一次更新
	for(int i=0;i<Num_con-1;++i){
		bool isSame=true;
		for(int j=1;j<=Num_char;++j){
			//cout<<i<<" "<<j<<" "<<endl;
			if(change[change[i][j]-1][Num_char+1]!=change[change[i+1][j]-1][Num_char+1]&&change[i][Num_char+1]==change[i+1][Num_char+1]){
				isSame=false;v[i+1]=1;break;
			}
		}
		if(isSame==false)break;
	}
	
	cout<<endl<<"初始DFA状态转化矩阵为(末列表示初始子集号)："<<endl<<"---------------------"<<endl;
	for(int i=0;i<Num_con;++i){
		for(int j=0;j<Num_char+2;++j){
			cout<<change[i][j]<<'\t';
		}
		cout<<endl;
	}
	int time=1;
	while(find(v,v+Num_con,1)!=v+Num_con){
		int curr_con=find(v,v+Num_con,1)-v;//记录当前需要改变状态行的下标
		for(int i=curr_con;i<Num_con;++i)++change[i][Num_char+1];//更新所有修改行以下的子集号，均加一；
		
		cout<<endl<<"第"<<time<<"次更新状态转化矩阵为："<<endl<<"---------------------"<<endl;
		for(int i=0;i<Num_con;++i){
			for(int j=0;j<Num_char+2;++j){
				cout<<change[i][j]<<'\t';
			}
			cout<<endl;
		}
		system("pause");
		v[curr_con]=0;//恢复
		
		for(int i=0;i<Num_con-1;++i){
			bool isSame=true;
			for(int j=1;j<=Num_char;++j){
				//cout<<i<<" "<<j<<" "<<endl;//这一步保留的调试可以看出是在判断到哪一行出现了与上一行不在同一子集中，断点即为需要开始调整的行
				if(change[change[i][j]-1][Num_char+1]!=change[change[i+1][j]-1][Num_char+1]&&change[i][Num_char+1]==change[i+1][Num_char+1]){
					isSame=false;v[i+1]=1;break;
				}
			}
			if(isSame==false)break;
		}
		++time;
	}
	cout<<endl<<"最小化后的DFA状态转化矩阵为："<<endl<<"---------------------"<<endl;
	for(int i=0;i<Num_con;++i){
		for(int j=0;j<Num_char+2;++j){
			cout<<change[i][j]<<'\t';
		}
		cout<<endl;
	}
	
	return 0;
}
