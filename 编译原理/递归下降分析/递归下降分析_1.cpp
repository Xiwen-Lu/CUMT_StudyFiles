//递归下降语法分析_1 结合自己写的词法分析
//简略版，只存储终结符表及其标号 
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<cstring>
#include<ctype.h>
using namespace std;

char finaltable[100][20];//存放终结符 
int finaltableint[100]; 
int flagerror=0,finalnum=0;

void program();
void block();
void stmts();
void stmt();
void boo1();
void expr();
void expr1();
void term();
void term1();
void factor();
void error(){
	flagerror=1;cout<<"此处出现错误！"<<endl;
}
void match(char *t){
	if(strcmp(finaltable[finalnum],t)==0);
	else{
		//error();
		flagerror=1;return;
	}
	finalnum++;
}


char prog[5000],ch,token[8];
int p=0,sym=0,n;
int line=1,pstart_line=0;

char *keyword[21]={"if","else","while","do","main","int","float","double"
,"return","const","void","continue","break","char","unsigned","enum"
,"long","switch","case","auto","static"};
void GetToken();
void Read_File(){
	char filename[30];
	FILE *fpin;
	cout<<"请输入文件名："<<endl;
	for(;;)
	{
		cin>>filename;
		if((fpin=fopen(filename,"r"))!=NULL)
			break;
		else cout<<"文件路径错误，请输入源文件名：";
	}
	char c;
    int state = 0;

    while ((c = fgetc(fpin)) != EOF) {
        if (state == 0 && c == '/')
            state = 1;
        else if (state == 1 && c == '*')
            state = 2;
        else if (state == 1 && c == '/')
            state = 4;
        else if (state == 1) {
            putchar('/');
            state = 0;
        }

        else if (state == 2 && c == '*')state = 3;
        else if (state == 2)state = 2;

        else if (state == 3 && c == '/')state = 0;
        else if (state == 3)state = 2;

        else if (state == 4 && c == '\\')state = 9;
        else if (state == 9 && c == '\\')state = 9;
        else if (state == 9)state = 4;
        else if (state == 4 && c == '\n')state = 0;

        else if (state == 0 && c == '\'')state = 5;
        else if (state == 5 && c == '\\')state = 6;
        else if (state == 6)state = 5;
        else if (state == 5 && c == '\'')state = 0;

        else if (state == 0 && c == '\"')state = 7;
        else if (state == 7 && c == '\\')state = 8;
        else if (state == 8)state = 7;
        else if (state == 7 && c == '\"')state = 0;
            
        if ((state == 0 && c != '/') || state == 5 || state == 6 || state == 7 || state == 8)
			prog[p++]=c;
            
    }
    prog[p]=EOF;
}
void Print(){
	int n_line=1;
	int p=0;
	do
	{
		cout<<n_line<<"\t";
		do
		{
			ch=prog[p++];
			cout<<ch;
		}
		while(ch!='\n'&&ch!=EOF);
		++n_line;
	}while(ch!=EOF);

}
int main(){
	p=0;
	Read_File();
	cout<<"删除注释后，源程序打印如下："<<endl;
	Print();
	p=0;

	cout<<endl<<endl<<"开始词法分析……"<<endl<<"--------------------------"<<endl;
	do
	{
		GetToken();
		switch(sym)
		{
			case -1:
			case -2:break;
			//case 2:strcpy(finaltable[finalnum],"id");finaltableint[finalnum++]=sym;break;
			default:{
				cout<<"("<<sym<<","<<token<<")"<<"\t\t\tline:"<<line<<
			",row:"<<p-pstart_line<<endl;
				strcpy(finaltable[finalnum],token);finaltableint[finalnum++]=sym;break;
			}
		}
	}while(ch!=EOF);
	for(int i=0;i<=finalnum;++i)cout<<finaltable[i]<<'\t'<<finaltableint[i]<<endl;
	finalnum=0;
	program();
	cout<<"语法分析完成！"<<endl;
	return 0;
}

void GetToken(){
	for(n=0;n<8;++n)token[n]='\0';//token赋初值
	
	n=0;
	ch=prog[p++];
	while(ch==' '||ch=='\n'||ch=='\t'){
		if(ch=='\n'){
			++line;pstart_line=p;
		}
		ch=prog[p++];//删除空白符
	}
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch=='_')
	{
		sym=1;
		do{
			token[n++]=ch;
			ch=prog[p++];
		}while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch=='_');
		sym=2;
		for(n=0;n<21;++n){//判断是不是保留字
			if(strcmp(token,keyword[n])==0)sym=n+3;
		}
		--p;//不是字母了，回退一格 
	 }
 
	else if(ch>='0'&&ch<='9')
	{
		sym=11;
		do{
			token[n++]=ch;
			ch=prog[p++];
		}while(ch>='0'&&ch<='9');
		sym=12;
		--p;
		return;
	}
	else
	{
		switch(ch){
			case '+':sym=26;token[0]=ch;break;
			case '-':sym=27;token[0]=ch;break;
			case '*':sym=28;token[0]=ch;break;
			case '/':sym=29;token[0]=ch;break;
			case '=':{
				sym=30;token[0]=ch;
				if(prog[p]=='='){
					token[1]='=';sym=40;++p;
				}
				break;
			}
			case '<':{
				sym=31;token[0]=ch;
				if(prog[p]=='='){
					token[1]='=';sym=45;++p;
				}
				break;
			}
			case '>':{
				sym=32;token[0]=ch;
				if(prog[p]=='='){
					token[1]='=';sym=44;++p;
				}
				break;
			}
			case '{':sym=33;token[0]=ch;break;
			case '}':sym=34;token[0]=ch;break;
			case ';':sym=35;token[0]=ch;break;
			case '(':sym=36;token[0]=ch;break;
			case ')':sym=37;token[0]=ch;break;
			case '\'':sym=38;token[0]=ch;break;
			case '"':sym=39;token[0]=ch;break;
			case '!':{
				if(prog[p]=='='){
					token[0]=ch;token[1]='=';
					sym=41;++p;break;
				}
				else;//单个!直接执行default报错处理
			}
			case '&':{
				if(prog[p]=='&'){
					token[0]='&';token[1]='&';
					sym=42;++p;break;
				}
				else;
			}
			case '|':{
				if(prog[p]=='|'){
					token[0]='|';token[1]='|';
					sym=43;++p;break;
				}
			}
			default:{
				sym=-2;
				if(ch==EOF)cout<<"词法分析结束。"<<endl;
				else cout<<"词法分析出错，检查输入"<<"\t\t\tline:"<<line<<
			",row:"<<p-pstart_line<<endl;
				break;
			}
		}
	}
}


void factor(){
	if(flagerror==1)return;
	//cout<<finaltableint[finalnum];
	switch(finaltableint[finalnum]){
		case 6:
			printf("factor-->(expr)\n");
			match("(");
			expr();
			match(")");
			break;
		case 2:
			printf("factor-->id\n");
			//match("id");
			++finalnum;
			break;
		case 12:
			printf("factor-->num\n");
			//match("num");
			++finalnum;
			break;
		default:
			flagerror=1;
			return;
	}
}

void term1(){
	if(flagerror==1)return;
	switch(finaltableint[finalnum]){
		case 28:
			printf("term1-->*factor term1\n");
			match("*");
			factor();
			term1();
			break;
		case 29:
			printf("term1-->/factor term1\n");
			match("/");
			factor();
			term1();
			break;
		default:
			printf("term1-->null\n");
			return;
	}
}

void term(){
	if(flagerror==1)return;
	printf("term-->factor term1\n");
	factor();
	term1();
}

void expr1(){
	if(flagerror==1)return;
	switch(finaltableint[finalnum]){
		case 26:
			printf("expr1-->+ term expr1\n");
			match("+");
			term();
			expr1();
			break;
		case 27:
			printf("expr1-->- term expr1\n");
			match("-");
			term();
			expr1();
			break;
		default:
			printf("expr1-->null\n");
			return; 
	}
}

void expr(){
	if(flagerror==1)return;
	printf("expr-->term expr1\n");
	term();expr1();
}
void boo1(){
	if(flagerror==1)return;
	expr();
	switch(finaltableint[finalnum]){
		case 31:
			printf("boo1-->expr<expr\n");
			match("<");expr();break;
		case 45:
			printf("boo1-->expr<=expr\n");
			match("<=");expr();break;
		case 32:
			printf("boo1-->expr>expr\n");
			match(">");expr();break;
		case 44:
			printf("boo1-->expr>=expr\n");
			match(">=");expr();break;
		default:
			printf("boo1-->expr\n");
			expr();break;
	}
}

void program(){
	printf("program-->block\n");
	block();
	if(flagerror==1){
		error();return;
	}
}

void block(){
	if(flagerror==1)return;
	printf("block-->{stmts}\n");
	match("{");stmts();match("}");
}

void stmts(){
	if(flagerror==1)return;
	if(finaltableint[finalnum]==34){
		printf("stms-->null\n");
		return;
	}
	printf("stms-->stmt stmts\n");
	stmt();stmts();
}
void stmt(){
	if(flagerror==1)return;
	switch(finaltableint[finalnum]){
		case 2:
			printf("stmt-->id=expr;\n");
			//match("id");
			++finalnum;
			match("=");expr();
			match(";");break;
		case 3:
			match("if");match("(");boo1();
			match(")");stmt();
			if(strcmp(finaltable[finalnum],"else")==0){
				printf("stmt-->if(boo1) stmt else stmt\n");
				match("else");
				stmt();break;
			}
			else{
				printf("stmt-->{if(boo1) stmt\n");
				break;
			}
		case 5:
			printf("stmt-->while(boo1) stmt\n");
			match("while");match("(");
			boo1();match(")");
			stmt();break;
		case 6:
			printf("stmt-->do stmt while(boo1)\n");
			match("do");stmt();
			match("while");match("(");
			boo1();match(")");break;
		case 15:
			printf("stmt-->break\n");
			match("break");break;
		default:
			printf("stmt-->block\n");
			block();break;
	}
}

