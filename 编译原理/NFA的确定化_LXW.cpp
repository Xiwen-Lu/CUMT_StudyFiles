#include<vector>
#include<queue>
#include<set>
#include<iostream>
#include<memory.h> 
#include<algorithm>
using namespace std;

void print(const set<int> &a){
	if(a.size()==0)return;
	//cout<<a.size();
	cout<<'{';
	set<int>::iterator it;
	for(it=a.begin();it!=a.end();++it)
		cout<<*it<<',';
	cout<<'\b'<<'}';
}
bool equal(set<int> &a,set<int> &b){
	if(a.size()!=b.size())return false;
	else{
		set<int>::iterator ia=a.begin();
		set<int>::iterator ib=b.begin();
		for(;ia!=a.end();++ia,++ib){
			if(*ia!=*ib)return false;
		}
	}
	return true;
}

int main()
{
	vector<int> I;
	cout<<"请输入有多少个转移字符（不包含epsilon）："<<endl;
	int Num_char;cin>>Num_char;
	cout<<"请输入转移字符（小写，保留e，e默认为epsilon，无需输入）："<<endl;
	char* change_char=new char[Num_char+1];*change_char='e';//change_char[]存储了所有的转移字符 
	for(int i=1;i<Num_char+1;++i)cin>>change_char[i];
	cout<<"请输入节点总数（0默认为start节点，包含在总数中):"<<endl;
	int Num_node;cin>>Num_node;
	int* node=new int[Num_node];
	for(int i=0;i<Num_node;++i)node[i]=i;
	
	char change[Num_node][Num_node]={};
	cout<<"请输入转移箭弧，格式为（开始节点编号  终点节点编号 转移字符）如 0 1 e。输入0 0 e结束输入"<<endl;
	int s,e;char c;
	while(cin>>s>>e>>c){
		if(s==0&&e==0&&c=='e')break;
		change[s][e]=c;
	};
	cout<<endl<<"输入状态邻接矩阵为："<<endl<<"------------------------"<<endl;
	for(int i=-1;i<Num_node;++i){
		for(int j=-1;j<Num_node;++j){
			if(i==-1&&j==-1)cout<<" "<<" ";
			else if(i==-1)cout<<j<<" ";
			else if(j==-1)cout<<i<<" ";
			else
				cout<<change[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"每个节点的e-closure为:"<<endl<<"-----------------------"<<endl;
	set<int>* node_epsilon=new set<int>[Num_node];//建立每个节点的e闭包set，便于之后的扩充
	for(int i=0;i<Num_node;++i){
		node_epsilon[i].insert(i);
		queue<int> que;que.push(i);//使用一个队列维护来进行宽度优先搜索（先找一步可达的所有位置）
		while(!que.empty()){
			int ii=que.front();
			for(int j=0;j<Num_node;++j){
				if(change[ii][j]=='e'/*&&node_epsilon[i].find(j)==node_epsilon[i].end()*/){
					node_epsilon[i].insert(j);
					que.push(j);
				}
			}
			que.pop();
		}
		print(node_epsilon[i]);cout<<endl;
	} 
	
	cout<<endl<<"确定化过程中构造的状态表为："<<endl<<"----------------"<<endl;
	vector<set<int> > v;
	v.push_back(node_epsilon[0]);
	//vector<set<int> >::const_iterator it=v.begin();迭代器在每一次容器元素发生变化时都会失效！！坑！！
	int it=0;
	while(it<v.size()){
		cout<<"s"<<it<<":";print(v[it]);cout<<'\t'<<'\t';
		for(int i=1;i<Num_char+1;++i){//开始维护v[char]，即单步字符的转移vector 
			char c=change_char[i]; 
			set<int> temp;//temp用来维护转移过程之中的集合,开副本，不再使用clear，为了保留在vector中值
			for(set<int>::iterator m=v[it].begin();m!=v[it].end();++m){
				for(int j=0;j<Num_node;++j){
					if(change[*m][j]==c){
						temp.insert(node_epsilon[j].begin(),node_epsilon[j].end());
					}
				}
			}
			print(temp);cout<<'\t'<<'\t';
			//开始判断该状态集合之前是否已经存在
			bool exists=false;
			for(int q=0;q<v.size();q++){
				//cout<<q;
				if(equal(v[q],temp)){
					exists=true;break;
				}
			}
			if(!exists){
				v.push_back(temp);//cout<<v.size()<<temp.size();
			}
   			//if(v.end()==find(v.begin(),v.end(),temp))v.push_back(temp);
		}
		++it;
		//print();//这里开始输出总是显示为空，猛然想到是不是vector保留的是一个指向内部元素的指针？而每次temp被clear之后便无法再恢复！！
		cout<<endl;
	}

 } 
