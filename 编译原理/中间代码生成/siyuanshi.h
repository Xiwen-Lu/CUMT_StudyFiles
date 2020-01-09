//siyuanshi.h

int nextstat=0;//当前生成的四元式编号
int registernum=0;
char code_buff[1024];
int delta=0;

int xvhao=0;
void print_xvhao(){printf("%d:\t",++xvhao);}

void init(){
	nextstat=0;
	 registernum=0;
	 xvhao=0;delta=0;
}
void newtemp(node* N){
	N->T=++registernum;
}

void emit_3addr(int T_dst,char *op,int T_1,int T_2){
	delta+=sprintf(code_buff+delta,"四元式%d：\t(%s\tT%d\tT%d\tT%d)\n",++nextstat,op,T_1,T_2,T_dst);
}

void emit_relop(char *op,int T_dst,int T_1,int T_2){
	delta+=sprintf(code_buff+delta,"四元式%d：\t if T%d %s T%d goto %d\n",++nextstat,T_1,op,T_2,nextstat+4);
	delta+=sprintf(code_buff+delta,"四元式%d: \t T%d = 0\n",++nextstat,T_dst);
	delta+=sprintf(code_buff+delta,"四元式%d: \t goto %d\n",++nextstat,nextstat+3);
	delta+=sprintf(code_buff+delta,"四元式%d: \t T%d = 1\n",++nextstat,T_dst);
}

void emit_ADD(int T_dst,int T_1,int T_2){
	delta+=sprintf(code_buff+delta,"四元式%d：\t(+\tT%d\tT%d\tT%d)\n",++nextstat,T_1,T_2,T_dst);
}

void emit_num(int T_dst,int num){
	delta+=sprintf(code_buff+delta,"四元式%d：\t(=\t%d\t\tT%d)\n",++nextstat,num,T_dst);
}

void emit_ID(char *T_dst,int T_src){
	delta+=sprintf(code_buff+delta,"四元式%d：\t(=\tT%d\t\t%s)\n",++nextstat,T_src,T_dst);
}
