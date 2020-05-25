#include <cstdlib>
#include <string.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "global.h"

#define rsT mipsWrite

#define INITSTACK 0x7fffeffc
#define INITDATA 0x10010000

int OPT=0;


int funcnum = 0;
int mi = 0;    //四元式处理的行数
int sp = INITSTACK;    //栈指针,此地址为即将分配的！！相对fp！！地址
int fp = 0;//帧指针
int ap;//地址表计数器
int ismain = 0;
int globedge = 0;
int tlabelnum = 0;

int isglob;
int paran = 0;
int tmi;

int funcedge=0;

int savespflg=0;
int vrnum;


int varreg[ 200 ];

typedef struct {
    char name[ 100 ];
    int address;
    int kind;
    int cnt;
}tempvaraddress;//变量表
tempvaraddress addrtable[ 1000 ];//临时变量在栈中的地址表





typedef struct {
    char name[ 100 ];
    int kind;
    int startap;
    int endap;
}funcclass;
vector<funcclass> fc;//函数表




//优化计数
void cntplus(char *varname){
    int t = ap - 1;
    isglob = 0;
    if ( varname[ 0 ] == '+' || varname[ 0 ] == '-' || ( varname[ 0 ] >= '0'&& varname[ 0 ] <= '9' ) || varname[ 0 ] == ' ' || varname[ 0 ] == '\t' || varname[ 0 ] == '\0' )
        return ;
    while ( t >= globedge) {
        if ( strcmp(addrtable[ t ].name, varname) == 0 ) {
            addrtable[ t ].cnt++;
            break;
        }
        t--;
    }
}


int findifin(vector<int> vec,int num){

    vector<int>::iterator ret;
    ret = find(vec.begin(), vec.end(), num);
    if(ret == vec.end())
        return 1;//未找到
    else
        return 0;//找到

}

//引用计数分配全局寄存器
void regopt() {
    //引用计数
    int tmi;
    tmi = mi;
    while ( strcmp(midcode[ tmi ].op, "end") != 0 ) {
        if ( strcmp(midcode[ tmi ].op, "=")==0 || strcmp(midcode[ tmi ].op, "+")==0 ||
                strcmp(midcode[ tmi ].op, "-")==0 || strcmp(midcode[ tmi ].op, "*")==0 || strcmp(midcode[ tmi ].op, "/")==0 )
        {
            cntplus(midcode[ tmi ].var1);
            cntplus(midcode[ tmi ].var2);
            cntplus(midcode[ tmi ].var3);
        }
        tmi++;
    }

/*
    for(int i=globedge;i<ap;i++){
     cout<< addrtable[i].name<< " " << addrtable[i].cnt <<endl;
    }
*/
    //排序
    vector<int> sortindex;
    int maxcnt = 0;
    int maxindex = 0;


    for(int rn=0 ; rn<7 ; rn++ ){
        int flg=0;
        maxcnt = 0;
        maxindex=0;
        for(int i=globedge;i<ap;i++){
            if( addrtable[i].cnt >= maxcnt  && findifin(sortindex,i) )
            {
                maxindex = i;
                maxcnt = addrtable[i].cnt;
                flg=1;
            }

        }

        if(flg==1)
            sortindex.push_back(maxindex);
        else
            sortindex.push_back(-1);
    }
    //排序结束

  //  for(int i=0;i<7;i++)cout<<  " : " << sortindex[i] <<endl;

    //分配全局寄存器
    for ( int i = 0; i < 7; i++ ) {

        if(sortindex[i]!=-1){
                //从$17--$s1开始分配到
            varreg[ sortindex[i] ] = i+1;
            int addr = addrtable[ sortindex[i] ].address;
            rsT << "\t\tlw\t$s" << i+1 << "\t" << addr << "($fp)" << endl;

           // cout<< addrtable[ sortindex[i] ].name << " $"<< i+1 <<endl;
        }

    }

}



//查找汇编变量地址
int varaddr(char *name) {
    int t = ap - 1;
    isglob = 0;
    if ( name[ 0 ] == '+' || name[ 0 ] == '-' || name[ 0 ] >= '0'&&name[ 0 ] <= '9' )
        return -1;
    while ( t >= 0 ) {



        if ( strcmp(addrtable[ t ].name, name) == 0 ) {
            if ( t < globedge ) {
                isglob = 1;
            }
            return addrtable[ t ].address;
        }
        t--;
    }

    return -1;
}

//查找汇编变量地址
int varaddr000(char *name) {
    int t = ap - 1;
    isglob = 0;
    if ( name[ 0 ] == '+' || name[ 0 ] == '-' || name[ 0 ] >= '0'&&name[ 0 ] <= '9' )
        return -1;
    while ( t >= 0 ) {



        if ( strcmp(addrtable[ t ].name, name) == 0 ) {
            if ( t < globedge ) {
                isglob = 1;
            }
            return t;
        }
        t--;
    }

    return -1;
}


void pushstack(char* item,int len) {
    if ( len == 1 ) {
        rsT << "li\t$t0\t" << item << "\t#" << midcode[mi].var3  <<endl; //li    $t0 item
        rsT << "sw\t$t0\t($sp)" << endl;      //sw    $t0 $sp
    }
    rsT << "subi\t$sp\t$sp\t" << 4 * len << endl; //subi  $sp $sp 4
  //  cout<< 4*len <<endl;

    return;
}


//给地址表插入相对地址，sp不变
void insertaddress(int kind, int itr,int len) {

    strcpy(addrtable[ ap ].name, midcode[ itr ].var3);
    addrtable[ ap ].address = sp;
    addrtable[ ap ].kind = kind;

    sp -= ( 4 * len );

    ap++;
}

//给地址表插入相对地址，sp不变
void parainsertaddress(int kind,int addr) {

    strcpy(addrtable[ ap ].name, midcode[ mi ].var3);
    addrtable[ ap ].address = addr;
    addrtable[ ap ].kind = kind;

    ap++;
}


int funckind(char *fname) {
    for ( int i = 0; i < fc.size(); i++ ) {
        if ( strcmp(fc[i].name, fname) == 0 ) {
            return fc[ i ].kind;
        }
    }
}



int findvartable(char *name) {
    int t = ap - 1;
    if ( name[ 0 ] == '+' || name[ 0 ] == '-' || name[ 0 ] >= '0'&&name[ 0 ] <= '9' )
        return -1;
    while ( t >= 0 ) {
        if ( strcmp(addrtable[ t ].name, name) == 0 )
            return t;
        t--;
    }
    return -1;
}




int varkind(char *name000) {
    int t = ap - 1;
    if ( name000[ 0 ] == '+' || name000[ 0 ] == '-' || name000[ 0 ] >= '0'&&name000[ 0 ] <= '9' )
        return -1;
    while ( t >= 0 ) {
        if ( strcmp(addrtable[ t ].name, name000) == 0 )
            return addrtable[ t ].kind;
        t--;
    }
  //  cout<<name000 <<"  NOTFOUND!"<<endl;
    return -1;
}



void Tomips(){

    memset(varreg, -1, sizeof(int) * 200);

    //for(int i = 0; i<20; i++) cout<< i << " @@ "<< varreg[i]<<endl;

    rsT << ".data" << endl;
    rsT << "\tEnter: .asciiz  \"\\n\"" <<endl;

    rsT << ".text" << endl;
    rsT << "ori\t$fp\t$sp\t0" << endl;//ori fp,sp,0//fp=sp
    rsT << "li\t$t9\t0x7fffeffc\t#global stack bottom" << endl; //li $t9,0x7fffeffc
    rsT << "li\t$t8\t0x10010000\t#save word" << endl;           //li $t8,0x10010000 .data

    mi = ap = 0;
    sp=0;

    while ( mi < fvcnt ){
        //全局常量定义
        while ( strcmp(midcode[ mi ].op, "const") == 0 ) {
            //sp在pushstack中已经减去
            pushstack(midcode[ mi ].var2,1);
            if ( strcmp(midcode[ mi ].var1, "int") == 0 ) {
                insertaddress(INTTK,mi,1);
            } else {
                insertaddress(CHARTK,mi,1);
            }

            mi++;
        }
        //全局变量定义
        while ( strcmp(midcode[ mi ].op, "int") == 0 || strcmp(midcode[ mi ].op, "char") == 0
               || strcmp(midcode[ mi ].op, "inta") == 0 || strcmp(midcode[ mi ].op, "chara") == 0 ) {

            if(strcmp(midcode[ mi ].op, "int") == 0 || strcmp(midcode[ mi ].op, "char")==0){
                pushstack("0",1);
                if ( strcmp(midcode[ mi ].op, "int") == 0 ) {
                    insertaddress(INTTK,mi,1);
                } else {
                    insertaddress(CHARTK,mi,1);
                }
                mi++;

            }
             //全局数组定义
            else if(strcmp(midcode[ mi ].op, "inta") == 0 || strcmp(midcode[ mi ].op, "chara") == 0 ){
                pushstack("0", atoi(midcode[mi].var2));
                if ( strcmp(midcode[ mi ].op, "inta") == 0 ) {
                    insertaddress(INTTK,mi,atoi(midcode[mi].var2));
                } else {
                    insertaddress(CHARTK,mi,atoi(midcode[mi].var2));
                }
                mi++;

            }
        }

        rsT << "\t\tj\t__main" << endl;
        globedge = ap;


        //函数定义
        funcclass tfc;
        while ( strcmp(midcode[mi].op, "func") == 0 ) {
            funcnum++;
            if ( strcmp(midcode[ mi ].var1, "char") == 0 ) {
                tfc.kind = CHARTK;
                strcpy(tfc.name, midcode[ mi ].var3);
                tfc.startap=ap;
                fc.push_back(tfc);
            } else if ( strcmp(midcode[ mi ].var1, "int") == 0 ) {
                tfc.kind = INTTK;
                strcpy(tfc.name, midcode[ mi ].var3);
                tfc.startap=ap;
                fc.push_back(tfc);
            } else {
                tfc.kind = VOIDTK;
                strcpy(tfc.name, midcode[ mi ].var3);
                tfc.startap=ap;
                fc.push_back(tfc);
            }

            if ( strcmp(midcode[ mi ].var3, "main") == 0 ) {
                ismain = 1;
                rsT << "__main:" << endl;
            } else {
                ismain = 0;
                rsT << midcode[ mi ].var3 << ":" << endl;
            }
            mi++;
            funcasm();
        }
    }
}

//处理函数内容，不处理最后的end和开始的func
void funcasm() {

    memset(varreg, -1, sizeof(int) * 200);
    sp = 0;//相对偏移为0
    //保存现场
    rsT << "#Save Register" << endl;//
    save();

    rsT << "sw  $s0 0($sp)" <<endl;     //保存上一个函数的sp
    rsT << "subi    $sp $sp 4" << endl;//$sp-=4
   // sp -= 4;

    rsT << "sw  $fp 0($sp)" << endl;//保存上一个函数的$fp
    rsT << "subi    $sp $sp 4" << endl;//$sp-=4
   // sp -= 4;

    rsT << "add\t$fp\t$sp\t$0" << endl;//设置本函数$fp：$fp=$sp
   // rsT << "subi\t$sp\t$sp\t4" << endl;//$sp-=4
  //  sp -= 4;

    rsT << "sw\t$ra\t($sp)" << endl;//保存$ra
    rsT << "subi\t$sp\t$sp\t4" << endl;//$sp-=4
    sp -= 4;

    rsT << "#Save Register Done!" << endl;//

    //临时变量定义
    tmi=mi;
    vrnum=0;

    while ( strcmp(midcode[ tmi ].op, "end") != 0 ) {
        char v1[100], v2[100], v3[100];
        strcpy(v1, midcode[ tmi ].var1);
        strcpy(v2, midcode[ tmi ].var2);
        strcpy(v3, midcode[ tmi ].var3);


        if ( v1[ 0 ] == '$' && varaddr(v1) == -1 ) {
            pushstack("0",1);
            insertaddress(INTTK, tmi, 1);
        }
        if ( v2[ 0 ] == '$' && varaddr(v2) == -1 ) {
            pushstack("0",1);
            insertaddress(INTTK, tmi, 1);
        }
        if ( v3[0] == '$' && varaddr(v3) == -1 ) {
            pushstack("0",1);
            if ( strcmp(midcode[tmi].op, "call") == 0 ) {
                insertaddress(funckind(midcode[tmi].var1), tmi, 1);
            }
            else if ( strcmp(midcode[ tmi ].op, "geta") == 0 ){
                //此处有问题！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
                insertaddress(varkind(v1),tmi, 1);
            }
            else{
                insertaddress(INTTK, tmi, 1);
            }
        }
        tmi++;
        vrnum++;
    }

    while ( strcmp(midcode[ mi ].op, "end") != 0 ) {
        paran = 0;
        for ( int i = 0; i < strlen(midcode[ mi ].op); i++ ) {
            if ( midcode[ mi ].op[ i ] == ' ' ) {
                midcode[ mi ].op[ i ] = '\0';
                break;
            }
        }

        if(OPT!=1){
            if ( strcmp(midcode[ mi ].op, "+") == 0 ) addasm();
            if ( strcmp(midcode[ mi ].op, "-") == 0 ) subasm();
            if ( strcmp(midcode[ mi ].op, "*") == 0 ) mulasm();
            if ( strcmp(midcode[ mi ].op, "/") == 0 ) divasm();
            if ( strcmp(midcode[ mi ].op, ">") == 0 ) greasm();
            if ( strcmp(midcode[ mi ].op, ">=") == 0 ) geqasm();
            if ( strcmp(midcode[ mi ].op, "<") == 0 ) lssasm();
            if ( strcmp(midcode[ mi ].op, "<=") == 0 ) leqasm();
            if ( strcmp(midcode[ mi ].op, "!=") == 0 ) neqasm();
            if ( strcmp(midcode[ mi ].op, "==") == 0 ) eqlasm();
            if ( strcmp(midcode[ mi ].op, "=") == 0 ) assasm();
            if ( strcmp(midcode[ mi ].op, "[]=") == 0 ) aassasm();
            if ( strcmp(midcode[ mi ].op, "geta") == 0 ) assaasm();
            if ( strcmp(midcode[ mi ].op, "lab:") == 0 ) setlabasm();
            if ( strcmp(midcode[ mi ].op, "scf") == 0 ) {
                scfasm();
            }
            if ( strcmp(midcode[ mi ].op, "prt") == 0 ) {
                prtasm();
            }
            if ( strcmp(midcode[ mi ].op, "jne") == 0 ) jneasm();
            if ( strcmp(midcode[ mi ].op, "jmp") == 0 ) jmpasm();
            if ( strcmp(midcode[ mi ].op, "fupa") == 0 ) fupaasm();
            if ( strcmp(midcode[ mi ].op, "call") == 0 ) callasm();
            if ( strcmp(midcode[ mi ].op, "ret") == 0 ) retasm();
            if ( strcmp(midcode[ mi ].op, "para") == 0 ) {paraasm();vrnum++;}
            if ( strcmp(midcode[ mi ].op, "int") == 0|| strcmp(midcode[ mi ].op, "char") == 0 ) {

                if(OPT!=1){intcharasm();vrnum++;}

                else{

                    int flag = 0;
                    while ( strcmp(midcode[ mi ].op, "int") == 0|| strcmp(midcode[ mi ].op, "char") == 0 ) {
                        flag = 1;
                        intcharasm();
                        mi++;
                    }
                    if (flag)    mi--;
                    //引用计数优化
                    regopt();

                }

            }

            if ( strcmp(midcode[ mi ].op, "const") == 0 ) {constdefasm();vrnum++;}
            if ( strcmp(midcode[ mi ].op, "inta") == 0 || strcmp(midcode[ mi ].op, "chara") == 0 ) {intcharaasm();vrnum++;}
            mi++;
        }
        //优化
        else{
            if ( strcmp(midcode[ mi ].op, "+") == 0 ) addbetter();
            if ( strcmp(midcode[ mi ].op, "-") == 0 ) subbetter();
            if ( strcmp(midcode[ mi ].op, "*") == 0 ) mulbetter();
            if ( strcmp(midcode[ mi ].op, "/") == 0 ) divbetter();
            if ( strcmp(midcode[ mi ].op, ">") == 0 ) grebetter();
            if ( strcmp(midcode[ mi ].op, ">=") == 0 ) geqbetter();
            if ( strcmp(midcode[ mi ].op, "<") == 0 ) lssbetter();
            if ( strcmp(midcode[ mi ].op, "<=") == 0 ) leqbetter();
            if ( strcmp(midcode[ mi ].op, "!=") == 0 ) neqbetter();
            if ( strcmp(midcode[ mi ].op, "==") == 0 ) eqlbetter();
            if ( strcmp(midcode[ mi ].op, "=") == 0 ) assbetter();
            if ( strcmp(midcode[ mi ].op, "[]=") == 0 ) aassbetter();
            if ( strcmp(midcode[ mi ].op, "geta") == 0 ) assabetter();
            if ( strcmp(midcode[ mi ].op, "lab:") == 0 ) setlabasm();
            if ( strcmp(midcode[ mi ].op, "scf") == 0 ) {
                scfbetter();
            }
            if ( strcmp(midcode[ mi ].op, "prt") == 0 ) {
                prtbetter();
            }
            if ( strcmp(midcode[ mi ].op, "jne") == 0 ) jneasm();
            if ( strcmp(midcode[ mi ].op, "jmp") == 0 ) jmpasm();
            if ( strcmp(midcode[ mi ].op, "fupa") == 0 ) fupabetter();
            if ( strcmp(midcode[ mi ].op, "call") == 0 ) callbetter();
            if ( strcmp(midcode[ mi ].op, "ret") == 0 ) retbetter();
            if ( strcmp(midcode[ mi ].op, "para") == 0 ) {paraasm();vrnum++;}

            if ( strcmp(midcode[ mi ].op, "int") == 0|| strcmp(midcode[ mi ].op, "char") == 0 ) {
                int flag = 0;
                while ( strcmp(midcode[ mi ].op, "int") == 0|| strcmp(midcode[ mi ].op, "char") == 0 ) {
                    flag = 1;
                    intcharasm();
                    mi++;
                }
                if (flag)    mi--;
                //引用计数优化
                regopt();
            }

            if ( strcmp(midcode[ mi ].op, "const") == 0 ) {constdefasm();vrnum++;}
            if ( strcmp(midcode[ mi ].op, "inta") == 0 || strcmp(midcode[ mi ].op, "chara") == 0 ) {intcharaasm();vrnum++;}
            mi++;
        }

    }
    ap = globedge;



    fc.back().endap = ap;
    //恢复现场
    rsT << "__FEND_LAB_" << funcnum << ":" << endl;//结束开始
    rsT << "lw  $ra 0($fp)" << endl;//恢复$ra
    rsT << "lw  $sp 8($fp)" << endl;//退栈,恢复$sp
    rsT << "lw  $fp 4($fp)" << endl;//恢复上一个函数的fp

    load();
    if ( ismain ) {
        rsT << "li\t$v0\t10" << endl;
        rsT << "syscall" << endl;//终止程序
    } else {
        rsT << "jr\t$ra\t" << endl;//返回
    }
    mi = mi + 1;
    return;
}


//para, int, , a == > f(int a, ...)
void paraasm() {
    paran = 0;
    for ( int i = mi; i < fvcnt; i++ ) {
        if ( strcmp(midcode[ i ].op, "para") == 0 )
            paran++;
        else
            break;
    }
    for ( int i = 0; i < paran; i++ ) {
        int kind = (strcmp(midcode[ mi ].var1, "int") == 0) ? INTTK : CHARTK;
        parainsertaddress(kind, 8+4 * ( paran - i ));

        mi++;
    }
    mi--;
}

//fupa,   ,   , a     ==> a is a function parameter
void fupaasm() {

    if(savespflg==0){
        rsT << "move $s0 $sp" << endl;
      //  funcedge=ap;

        savespflg=1;
    }


    if ( isdigit(midcode[mi].var3[0]) ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var3 << endl;
    } else {
        rsT << "lw\t$t0\t" << varaddr(midcode[ mi ].var3); //li    $t0 item
        if(isglob){
            rsT << "($t9)" << endl;
        }else{
            rsT << "($fp)" << endl;
        }
    }
    rsT << "sw\t$t0\t($sp)" << endl;      //sw    $t0 $sp
    rsT << "subi\t$sp\t$sp\t4" << endl; //subi  $sp $sp 4
    sp -= 4;
}

void fupabetter(){
    if(savespflg==0){
        rsT << "move $s0 $sp" << endl;
      //  funcedge=ap;

        savespflg=1;
    }
    if ( isdigit(midcode[mi].var3[0]) ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var3 << endl;
    } else {

        if( varreg[varaddr000(midcode[ mi ].var3)]==-1 ){

            rsT << "lw\t$t0\t" << varaddr(midcode[ mi ].var3); //li    $t0 item
            if(isglob){
                rsT << "($t9)" << endl;
            }else{
                rsT << "($fp)" << endl;
            }

        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var3)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }
    }
    rsT << "sw\t$t0\t($sp)" << endl;      //sw    $t0 $sp
    rsT << "subi\t$sp\t$sp\t4" << endl; //subi  $sp $sp 4
    sp -= 4;

}


//    jmp ,  ,  ,
void jmpasm() {
    rsT << "j\t" << midcode[ mi ].var3 << endl;
}

//    jne
void jneasm() {
    rsT << "bne\t$t0\t1\t" << midcode[ mi ].var3 << endl;   //bne,$t0,1,label
}


//    call, f ,   , a
void callasm() {

    if(savespflg == 0){
        rsT << "move $s0 $sp" << endl;
        savespflg=1;
    }

    rsT << "jal\t" << midcode[ mi ].var1 << endl;
    rsT << "nop\n";
    if ( midcode[ mi ].var3[ 0 ] != ' ' && midcode[ mi ].var3[ 0 ] != '\0' ) {
        int addr2;
        addr2 = varaddr(midcode[ mi ].var3);
        if ( isglob )
            rsT << "sw\t$v0\t" << addr2 << "($t9)" << endl; // sw v0,0(t9)
        else
            rsT << "sw\t$v0\t" << addr2 << "($fp)" << endl; // sw v0,0(fp)
    }

    savespflg=0;
}

//    call, f ,   , a
void callbetter() {

    if(savespflg == 0){
        rsT << "move $s0 $sp" << endl;
        savespflg=1;
    }

    rsT << "jal\t" << midcode[ mi ].var1 << endl;
    rsT << "nop\n";
    if ( midcode[ mi ].var3[ 0 ] != ' ' && midcode[ mi ].var3[ 0 ] != '\0' ) {

        if(varreg[varaddr000(midcode[mi].var3)]==-1){
            int addr2;
            addr2 = varaddr(midcode[ mi ].var3);
            if ( isglob )
                rsT << "sw\t$v0\t" << addr2 << "($t9)" << endl; // sw v0,0(t9)
            else
                rsT << "sw\t$v0\t" << addr2 << "($fp)" << endl; // sw v0,0(fp)
        }
        else{

             int regnum = varreg[varaddr000(midcode[ mi ].var3)];
             rsT << "\t\tadd\t$s" <<regnum<<"\t$v0\t$0" <<endl;//add $si $v0 $0
        }

    }

    savespflg=0;
}

//ret ,   ,   , (a)   ==> return a / return
void retasm() {
    if ( midcode[ mi ].var3[ 0 ] != ' ' && midcode[ mi ].var3[ 0 ] != '\0' ) {
        if ( isdigit(midcode[ mi ].var3[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
            rsT << "li\t$v0\t" << midcode[ mi ].var3 << endl;
        } else {
            int addr2 = varaddr(midcode[ mi ].var3);
            if ( isglob )
                rsT << "lw\t$v0\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$v0\t" << addr2 << "($fp)" << endl;
        }
    }
    rsT << "j\t__FEND_LAB_" << funcnum << endl;//跳至结束
}

//ret ,   ,   , (a)   ==> return a / return
void retbetter() {
    if ( midcode[ mi ].var3[ 0 ] != ' ' && midcode[ mi ].var3[ 0 ] != '\0' ) {
        if ( isdigit(midcode[ mi ].var3[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
            rsT << "li\t$v0\t" << midcode[ mi ].var3 << endl;
        } else {
            if(varreg[varaddr000(midcode[mi].var3)]==-1){
                int addr2 = varaddr(midcode[ mi ].var3);
                if ( isglob )
                    rsT << "lw\t$v0\t" << addr2 << "($t9)" << endl;
                else
                    rsT << "lw\t$v0\t" << addr2 << "($fp)" << endl;
            }
            else{
                 int regnum = varreg[varaddr000(midcode[ mi ].var3)];
                 rsT << "\t\tadd\t$v0\t$s" <<regnum<<"\t$0" <<endl;//add $v0 $si $0
            }

        }
    }
    rsT << "j\t__FEND_LAB_" << funcnum << endl;//跳至结束
}



//    lab,  ,  ,
void setlabasm() {
    rsT << midcode[ mi ].var3 << ":\n";
}

//    add, a, b, c
void addasm() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        //li t0,var1
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;

    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    addr3 = varaddr(midcode[ mi ].var3);
    rsT << "add\t$t0\t$t0\t$t1" << endl;
    if ( isglob )
        rsT << "\t\tsw\t$t0\t" << addr1 << "($t9)" << endl;
    else
        rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
}


//    add, a, b, c
void addbetter() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        //li t0,var1
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;

    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }

    if(varreg[varaddr000(midcode[mi].var3)]==-1){
        addr3 = varaddr(midcode[ mi ].var3);
        rsT << "add\t$t0\t$t0\t$t1" << endl;
        if ( isglob )
            rsT << "\t\tsw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
    }
    else{
        rsT << "add\t$t0\t$t0\t$t1" << endl;
        int regnum = varreg[varaddr000(midcode[ mi ].var3)];
        rsT << "\t\tadd\t$s" <<regnum<<"\t$t0\t$0" <<endl;//add $si $t0 $0
    }

}


//    sub, a, b, c
void subasm() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    addr3 = varaddr(midcode[ mi ].var3);
    rsT << "sub\t$t0\t$t0\t$t1" << endl;
    if ( isglob )
        rsT << "sw\t$t0\t" << addr3 << "($t9)" << endl; //sw t0,addr3(t9)
    else
        rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
}


//    sub, a, b, c
void subbetter() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {

        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }

    if(varreg[varaddr000(midcode[mi].var3)]==-1){
        addr3 = varaddr(midcode[ mi ].var3);
        rsT << "sub\t$t0\t$t0\t$t1" << endl;
        if ( isglob )
            rsT << "sw\t$t0\t" << addr3 << "($t9)" << endl; //sw t0,addr3(t9)
        else
            rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
    }
    else{
        rsT << "sub\t$t0\t$t0\t$t1" << endl;
        int regnum = varreg[varaddr000(midcode[ mi ].var3)];
        rsT << "\t\tadd\t$s" <<regnum<<"\t$t0\t$0" <<endl;//add $si $t0 $0

    }

}

//    mul, a, b, c
void mulasm() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    addr3 = varaddr(midcode[ mi ].var3);
    rsT << "mul\t$t0\t$t0\t$t1" << endl;
    if ( isglob )
        rsT << "sw\t$t0\t" << addr3 << "($t9)" << endl;
    else
        rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
}

//    mul, a, b, c
void mulbetter() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;

        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }

    if(varreg[varaddr000(midcode[mi].var3)]==-1){
        addr3 = varaddr(midcode[ mi ].var3);
        rsT << "mul\t$t0\t$t0\t$t1" << endl;
        if ( isglob )
            rsT << "sw\t$t0\t" << addr3 << "($t9)" << endl;
        else
            rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
    }
    else{
        rsT << "mul\t$t0\t$t0\t$t1" << endl;
        int regnum = varreg[varaddr000(midcode[ mi ].var3)];
        rsT << "\t\tadd\t$s" <<regnum<<"\t$t0\t$0" <<endl;//add $si $t0 $0
    }

}



//    div, a, b, c
void divasm() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    addr3 = varaddr(midcode[ mi ].var3);
    rsT << "div\t$t0\t$t0\t$t1" << endl;
    if ( isglob )
        rsT << "sw\t$t0\t" << addr3 << "($t9)" << endl;
    else
        rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
}


//    div, a, b, c
void divbetter() {
    int addr1, addr2, addr3;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }

    if(varreg[varaddr000(midcode[mi].var3)]==-1){
        addr3 = varaddr(midcode[ mi ].var3);
        rsT << "div\t$t0\t$t0\t$t1" << endl;
        if ( isglob )
            rsT << "sw\t$t0\t" << addr3 << "($t9)" << endl;
        else
            rsT << "sw\t$t0\t" << addr3 << "($fp)" << endl;
    }
    else{
        rsT << "div\t$t0\t$t0\t$t1" << endl;
        int regnum = varreg[varaddr000(midcode[ mi ].var3)];
        rsT << "\t\tadd\t$s" <<regnum<<"\t$t0\t$0" <<endl;//add $si $t0 $0
    }

}

//    > , a, b, c
void greasm() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    // slt t0,t1,t0
    rsT << "slt\t$t0\t$t1\t$t0" << endl;
}


//    > , a, b, c
void grebetter() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {

        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }
    // slt t0,t1,t0
    rsT << "slt\t$t0\t$t1\t$t0" << endl;
}

//    >=
void geqasm() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    rsT << "slt\t$t0\t$t0\t$t1" << endl;    //slt t0,t0,t1
    rsT << "li\t$t1\t1" << endl;            //li t1,1
    rsT << "sub\t$t0\t$t1\t$t0" << endl;   //sub t0,t1,t0
}


//    >=
void geqbetter() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;

        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    rsT << "slt\t$t0\t$t0\t$t1" << endl;    //slt t0,t0,t1
    rsT << "li\t$t1\t1" << endl;            //li t1,1
    rsT << "sub\t$t0\t$t1\t$t0" << endl;   //sub t0,t1,t0
}


//    <
void lssasm() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    rsT << "slt\t$t0\t$t0\t$t1" << endl;
}
//    <
void lssbetter() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    rsT << "slt\t$t0\t$t0\t$t1" << endl;
}


//    <=
void leqasm() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    rsT << "slt\t$t0\t$t1\t$t0" << endl;
    rsT << "li\t$t1\t1" << endl;
    rsT << "sub\t$t0\t$t1\t$t0" << endl;
}


//    <=
void leqbetter() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;

        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    rsT << "slt\t$t0\t$t1\t$t0" << endl;
    rsT << "li\t$t1\t1" << endl;
    rsT << "sub\t$t0\t$t1\t$t0" << endl;
}

//    ==
void eqlasm() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }


    int t1 = tlabelnum++;
    int t2 = tlabelnum++;
    rsT << "bne\t$t0\t$t1\t__tLABEL" << t1 << endl; //bne t0 t1 __tLABEL0
    rsT << "li\t$t0\t1" << endl;                    //li t0,1
    rsT << "j\t__tLABEL" << t2 << endl;             //j __tLABEL1
    rsT << "__tLABEL" << t1 << ":" << endl;             //__tLABEL0:
    //cout << "__tLABEL" << t1 << ":" << endl;
    rsT << "li\t$t0\t0" << endl;                    //li $t0,0
    rsT << "__tLABEL" << t2 << ":" << endl;             //__tLABEL1:

}

//    ==
void eqlbetter() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {

        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;

        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0

        }

    }


    int t1 = tlabelnum++;
    int t2 = tlabelnum++;
    rsT << "bne\t$t0\t$t1\t__tLABEL" << t1 << endl; //bne t0 t1 __tLABEL0
    rsT << "li\t$t0\t1" << endl;                    //li t0,1
    rsT << "j\t__tLABEL" << t2 << endl;             //j __tLABEL1
    rsT << "__tLABEL" << t1 << ":" << endl;             //__tLABEL0:
    //cout << "__tLABEL" << t1 << ":" << endl;
    rsT << "li\t$t0\t0" << endl;                    //li $t0,0
    rsT << "__tLABEL" << t2 << ":" << endl;             //__tLABEL1:

}


//    !=
void neqasm() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        addr2 = varaddr(midcode[ mi ].var2);
        if ( isglob )
            rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
        else
            rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;
    }
    int t1 = tlabelnum++;
    int t2 = tlabelnum++;
    rsT << "beq\t$t0\t$t1\t__tLABEL" << t1 << endl;
    rsT << "li\t$t0\t1" << endl;
    rsT << "j\t__tLABEL" << t2 << endl;
    rsT << "__tLABEL" << t1 << ":" << endl;
    //cout << "__tLABEL" << t1 << ":" << endl;
    rsT << "li\t$t0\t0" << endl;
    rsT << "__tLABEL" << t2 << ":" << endl;
}


//    !=
void neqbetter() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }
    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        rsT << "li\t$t1\t" << midcode[ mi ].var2 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addr2 = varaddr(midcode[ mi ].var2);
            if ( isglob )
                rsT << "lw\t$t1\t" << addr2 << "($t9)" << endl;
            else
                rsT << "lw\t$t1\t" << addr2 << "($fp)" << endl;

        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }
    int t1 = tlabelnum++;
    int t2 = tlabelnum++;
    rsT << "beq\t$t0\t$t1\t__tLABEL" << t1 << endl;
    rsT << "li\t$t0\t1" << endl;
    rsT << "j\t__tLABEL" << t2 << endl;
    rsT << "__tLABEL" << t1 << ":" << endl;
    //cout << "__tLABEL" << t1 << ":" << endl;
    rsT << "li\t$t0\t0" << endl;
    rsT << "__tLABEL" << t2 << ":" << endl;
}


//    =
void assasm() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        addr1 = varaddr(midcode[ mi ].var1);
        if ( isglob )
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
    }
    addr2 = varaddr(midcode[ mi ].var3);
    if (isglob )
        rsT << "sw\t$t0\t" << addr2 << "($t9)" <<"  #   "<< midcode[mi].var3<< endl;
    else
        rsT << "sw\t$t0\t" << addr2 << "($fp)" <<"  #   "<< midcode[mi].var3<< endl;
}

//    =
void assbetter() {
    int addr1, addr2;
    if ( isdigit(midcode[ mi ].var1[ 0 ]) || midcode[ mi ].var1[ 0 ] == '-' || midcode[ mi ].var1[ 0 ] == '+' ) {
        rsT << "li\t$t0\t" << midcode[ mi ].var1 << endl;
    } else {
        if(varreg[varaddr000(midcode[mi].var1)]==-1){
            addr1 = varaddr(midcode[ mi ].var1);
            if ( isglob )
                rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var1)];
            rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

    }


    if(varreg[varaddr000(midcode[mi].var3)]==-1){

        addr2 = varaddr(midcode[ mi ].var3);
        if (isglob )
            rsT << "sw\t$t0\t" << addr2 << "($t9)" <<"  #   "<< midcode[mi].var3<< endl;
        else
            rsT << "sw\t$t0\t" << addr2 << "($fp)" <<"  #   "<< midcode[mi].var3<< endl;
    }
    else{
        int regnum = varreg[varaddr000(midcode[ mi ].var3)];
        rsT << "\t\tadd\t$s" <<regnum<<"\t$t0\t$0" <<endl;//add $si $t0 $0
    }

}


//    []= , a , i , t
void aassasm() {
    int addr1, addr2, addri;
    addr1 = varaddr(midcode[ mi ].var1);
    int tisglob = isglob;
    //[i]不是表达式
    if ( isdigit(midcode[ mi ].var2[0]) ) {
        addr1 -= (atoi(midcode[ mi ].var2) * 4);
        if ( isdigit(midcode[ mi ].var3[ 0 ]) || midcode[ mi ].var3[ 0 ] == '-' || midcode[ mi ].var3[ 0 ] == '+' ) {
            rsT << "li\t$t0\t" << midcode[ mi ].var3 << endl;       //t0=var3
        } else {
            addr2 = varaddr(midcode[ mi ].var3);
            if ( isglob ) {
                rsT << "lw\t$t0\t" << addr2 << "($t9)" << endl;
            }else
                rsT << "lw\t$t0\t" << addr2 << "($fp)" << endl;

        }
        if (tisglob)
            rsT << "sw\t$t0\t" << addr1 << "($t9)" << endl;
        else
            rsT << "sw\t$t0\t" << addr1 << "($fp)" << endl;
    } else {
        //求数组元素a[i]地址
        addri = varaddr(midcode[ mi ].var2);//addrt = &i
        if (isglob)
            rsT << "lw\t$t1\t" << addri << "($t9)" << endl;    //t1 = i
        else
            rsT << "lw\t$t1\t" << addri << "($fp)" << endl;    //t1 = i
        rsT << "mul\t$t1\t$t1\t-4\n";    //t1 = t1 * 4 (t1 = offset)
        rsT << "addi\t$t1\t$t1\t" << addr1 << endl;    //t1 = addr1+t1
       // rsT << "\t\tadd\t$t1\t$t1\t$fp" << endl;//t1 = &a[i]


        if ( isdigit(midcode[ mi ].var3[ 0 ]) || midcode[ mi ].var3[ 0 ] == '-' || midcode[ mi ].var3[ 0 ] == '+' ) {
            rsT << "li\t$t0\t" << midcode[ mi ].var3 << endl;
        } else {
            //t0=var3
            addr2 = varaddr(midcode[ mi ].var3);
            if ( isglob ) {
                rsT << "lw\t$t0\t" << addr2 << "($t9)" << endl;
            } else {
                rsT << "lw\t$t0\t" << addr2 << "($fp)" << endl;
            }

        }



        if (tisglob){

            rsT << "add\t$t1\t$t1\t$t9" << endl;
            rsT << "sw\t$t0\t0($t1)" << endl;

        }

        else{
            rsT << "add\t$t1\t$t1\t$fp" << endl;
            rsT << "sw\t$t0\t0($t1)" << endl;

        }
           // rsT << "sw\t$t0\t$t1" << "($fp)" << endl;
        //rsT << "sw\t$t0\t0($t1)" << endl;
    }
}



//    []= , a , i , t
void aassbetter() {
    int addr1, addr2, addri;
    addr1 = varaddr(midcode[ mi ].var1);
    int tisglob = isglob;
    //[i]不是表达式
    if ( isdigit(midcode[ mi ].var2[0]) ) {
        addr1 -= (atoi(midcode[ mi ].var2) * 4);
        if ( isdigit(midcode[ mi ].var3[ 0 ]) || midcode[ mi ].var3[ 0 ] == '-' || midcode[ mi ].var3[ 0 ] == '+' ) {
            rsT << "li\t$t0\t" << midcode[ mi ].var3 << endl;       //t0=var3
        } else {
            if(varreg[varaddr000(midcode[mi].var3)]==-1){
                addr2 = varaddr(midcode[ mi ].var3);
                if ( isglob ) {
                    rsT << "lw\t$t0\t" << addr2 << "($t9)" << endl;
                }else
                    rsT << "lw\t$t0\t" << addr2 << "($fp)" << endl;
            }
            else{
                int regnum = varreg[varaddr000(midcode[ mi ].var3)];
                rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
            }


        }

            if (tisglob)
                rsT << "sw\t$t0\t" << addr1 << "($t9)" << endl;
            else
                rsT << "sw\t$t0\t" << addr1 << "($fp)" << endl;



    } else {
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            addri = varaddr(midcode[ mi ].var2);//addrt = &i
            if (isglob)
                rsT << "lw\t$t1\t" << addri << "($t9)" << endl;    //t1 = i
            else
                rsT << "lw\t$t1\t" << addri << "($fp)" << endl;    //t1 = i
        }
        //求数组元素a[i]地址
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }

        rsT << "mul\t$t1\t$t1\t-4\n";    //t1 = t1 * 4 (t1 = offset)
        rsT << "addi\t$t1\t$t1\t" << addr1 << endl;    //t1 = addr1+t1
       // rsT << "\t\tadd\t$t1\t$t1\t$fp" << endl;//t1 = &a[i]


        if ( isdigit(midcode[ mi ].var3[ 0 ]) || midcode[ mi ].var3[ 0 ] == '-' || midcode[ mi ].var3[ 0 ] == '+' ) {
            rsT << "li\t$t0\t" << midcode[ mi ].var3 << endl;
        } else {
            //t0=var3
            if(varreg[varaddr000(midcode[mi].var3)]==-1){
                addr2 = varaddr(midcode[ mi ].var3);
                if ( isglob ) {
                    rsT << "lw\t$t0\t" << addr2 << "($t9)" << endl;
                } else {
                    rsT << "lw\t$t0\t" << addr2 << "($fp)" << endl;
                }
            }
            else{
                int regnum = varreg[varaddr000(midcode[ mi ].var3)];
                rsT << "\t\tadd\t$t0\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
            }


        }



        if (tisglob){

            rsT << "add\t$t1\t$t1\t$t9" << endl;
            rsT << "sw\t$t0\t0($t1)" << endl;

        }

        else{
            rsT << "add\t$t1\t$t1\t$fp" << endl;
            rsT << "sw\t$t0\t0($t1)" << endl;

        }
           // rsT << "sw\t$t0\t$t1" << "($fp)" << endl;
        //rsT << "sw\t$t0\t0($t1)" << endl;
    }
}


//geta, a, n, b         b=a[n]
void assaasm() {
    int addr1 = varaddr(midcode[ mi ].var1);
    int tisglob = isglob;
    int addr2;


    int t1 = findvartable(midcode[ mi ].var3);

    if(midcode[mi].var3[0]=='$' && addrtable[t1].kind <0 ){
            int t0 = findvartable(midcode[ mi ].var1);
            int kind0 = addrtable[ t0 ].kind;


            addrtable[t1].kind=kind0;

           // cout<< kind0<<"  aaaaaaaaaaaaaaaaaa"<<endl;
    }


    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
        addr1 -= ( atoi(midcode[ mi ].var2) * 4 );    //addr1 = &a[n]
        addr2 = varaddr(midcode[ mi ].var3);        //addr2 = &b
        if ( tisglob ) {
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        }else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;
        if ( isglob ) {
            rsT << "sw\t$t0\t" << addr2 << "($t9)" << endl;
        }else
            rsT << "sw\t$t0\t" << addr2 << "($fp)" << endl;
    } else {
        //求数组元素a[i]地址
        int addri = varaddr(midcode[ mi ].var2);//addrt = &i
        if ( isglob ) {
            rsT << "lw\t$t1\t" << addri << "($t9)" << endl;    //t1 = i
        }else
            rsT << "lw\t$t1\t" << addri << "($fp)" << endl;    //t1 = i
        rsT << "mul\t$t1\t$t1\t-4\n";    //t1 = t1 * 4 (t1 = offset)
        rsT << "addi\t$t1\t$t1\t" << addr1 << endl;    //t1=$a[i]偏移量

        addr2 = varaddr(midcode[ mi ].var3);        //addr2 = &b
        if ( tisglob ) {
            rsT << "add\t$t1\t$t1\t$t9" << endl;
            rsT << "lw\t$t0\t0"  << "($t1)" << endl;
        }else{
            rsT << "add\t$t1\t$t1\t$fp" << endl;
            rsT << "lw\t$t0\t0"  << "($t1)" << endl;

        }

        if ( isglob ) {
            rsT << "sw\t$t0\t" << addr2 << "($t9)" << endl;
        }else{
            rsT << "sw\t$t0\t" << addr2 << "($fp)" << endl;
        }

    }
}

//geta, a, n, b         b=a[n]
void assabetter() {
    int addr1 = varaddr(midcode[ mi ].var1);
    int tisglob = isglob;
    int addr2;


    int t1 = findvartable(midcode[ mi ].var3);

    if(midcode[mi].var3[0]=='$' && addrtable[t1].kind <0 ){
            int t0 = findvartable(midcode[ mi ].var1);
            int kind0 = addrtable[ t0 ].kind;


            addrtable[t1].kind=kind0;

           // cout<< kind0<<"  aaaaaaaaaaaaaaaaaa"<<endl;
    }


    if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {


        addr1 -= ( atoi(midcode[ mi ].var2) * 4 );    //addr1 = &a[n]
        addr2 = varaddr(midcode[ mi ].var3);        //addr2 = &b
        if ( tisglob ) {
            rsT << "lw\t$t0\t" << addr1 << "($t9)" << endl;
        }else
            rsT << "lw\t$t0\t" << addr1 << "($fp)" << endl;

        if(varreg[varaddr000(midcode[mi].var3)]==-1){
            if ( isglob ) {
                rsT << "sw\t$t0\t" << addr2 << "($t9)" << endl;
            }else
                rsT << "sw\t$t0\t" << addr2 << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var3)];
            rsT << "\t\tadd\t$s" <<regnum<<"\t$t0\t$0" <<endl;//add $si $t0 $0
        }

    } else {
        //求数组元素a[i]地址
        if(varreg[varaddr000(midcode[mi].var2)]==-1){
            int addri = varaddr(midcode[ mi ].var2);//addrt = &i
            if ( isglob ) {
                rsT << "lw\t$t1\t" << addri << "($t9)" << endl;    //t1 = i
            }else
                rsT << "lw\t$t1\t" << addri << "($fp)" << endl;    //t1 = i
        }
        else{

            int regnum = varreg[varaddr000(midcode[ mi ].var2)];
            rsT << "\t\tadd\t$t1\t$s" <<regnum<<"\t$0" <<endl;//add $t0 $si $0
        }
        rsT << "mul\t$t1\t$t1\t-4\n";    //t1 = t1 * 4 (t1 = offset)
        rsT << "addi\t$t1\t$t1\t" << addr1 << endl;    //t1=$a[i]偏移量




        addr2 = varaddr(midcode[ mi ].var3);        //addr2 = &b
        if ( tisglob ) {
            rsT << "add\t$t1\t$t1\t$t9" << endl;
            rsT << "lw\t$t0\t0"  << "($t1)" << endl;
        }else{
            rsT << "add\t$t1\t$t1\t$fp" << endl;
            rsT << "lw\t$t0\t0"  << "($t1)" << endl;

        }


        if(varreg[varaddr000(midcode[mi].var3)]==-1){
            if ( isglob ) {
                rsT << "sw\t$t0\t" << addr2 << "($t9)" << endl;
            }else{
                rsT << "sw\t$t0\t" << addr2 << "($fp)" << endl;
            }

        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var3)];
            rsT << "\t\tadd\t$s" <<regnum<<"\t$t0\t$0" <<endl;//add $si $t0 $0
        }
    }
}


//scf ,   ,   , a
void scfasm() {
    int addr = varaddr(midcode[ mi ].var3);
    int ti = findvartable(midcode[ mi ].var3);
    int kind = addrtable[ ti ].kind;
    if ( kind == INTTK ) {
        rsT << "li\t$v0\t5" << endl;
        rsT << "syscall" << endl;
        //rsT << "\t\tsubi\t$v0\t$v0\t" << ( int )'0' << endl;
        if (isglob)
            rsT << "sw\t$v0\t" << addr << "($t9)" << endl;
        else
            rsT << "sw\t$v0\t" << addr << "($fp)" << endl;
    } else {
        rsT << "li\t$v0\t12" << endl;
        rsT << "syscall" << endl;
        if ( isglob )
            rsT << "sw\t$v0\t" << addr << "($t9)" << endl;
        else
            rsT << "sw\t$v0\t" << addr << "($fp)" << endl;
    }
}


//scf ,   ,   , a
void scfbetter() {
    int addr = varaddr(midcode[ mi ].var3);
    int ti = findvartable(midcode[ mi ].var3);
    int kind = addrtable[ ti ].kind;
    if ( kind == INTTK ) {
        rsT << "li\t$v0\t5" << endl;
        rsT << "syscall" << endl;
        //rsT << "\t\tsubi\t$v0\t$v0\t" << ( int )'0' << endl;
        if(varreg[varaddr000(midcode[mi].var3)]==-1){
            if (isglob)
                rsT << "sw\t$v0\t" << addr << "($t9)" << endl;
            else
                rsT << "sw\t$v0\t" << addr << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var3)];
            rsT << "\t\tadd\t$s" <<regnum<<"\t$v0\t$0" <<endl;//add $si $t0 $0
        }

    } else {
        rsT << "li\t$v0\t12" << endl;
        rsT << "syscall" << endl;

        if(varreg[varaddr000(midcode[mi].var3)]==-1){
            if ( isglob )
                rsT << "sw\t$v0\t" << addr << "($t9)" << endl;
            else
                rsT << "sw\t$v0\t" << addr << "($fp)" << endl;
        }
        else{
            int regnum = varreg[varaddr000(midcode[ mi ].var3)];
            rsT << "\t\tadd\t$s" <<regnum<<"\t$v0\t$0" <<endl;//add $si $t0 $0
        }

    }
}


//prt,string,expression,int/char
void prtasm() {
    int addr;
    if ( midcode[ mi ].var1[ 0 ] != '\0' ) {
        int len = strlen(midcode[ mi ].var1);
        for ( int i = 1; i < len-1; i++ ) {
            rsT << "li\t$v0\t11" << endl;
            rsT << "li\t$a0\t" << int(midcode[ mi ].var1[i]) << endl;
            rsT << "syscall" << endl;
        }

    }
    if ( midcode[ mi ].var2[ 0 ] != ' ' && midcode[ mi ].var2[ 0 ] != '\0' ) {
        if ( isdigit(midcode[mi].var2[0]) && strcmp(midcode[mi].var3, "char") == 0 ) {
            rsT << "li\t$v0\t11" << endl;
            rsT << "li\t$a0\t" << midcode[ mi ].var2 << endl;
            rsT << "syscall" << endl;

            rsT << "li\t$v0\t4" << endl;
            rsT << "la\t$a0\t" << "Enter" << endl;
            rsT << "syscall" << endl;

            return;

        } else if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
            rsT << "li\t$v0\t1" << endl;
            rsT << "li\t$a0\t" << midcode[ mi ].var2 << endl;
            rsT << "syscall" << endl;

            rsT << "li\t$v0\t4" << endl;
            rsT << "la\t$a0\t" << "Enter" << endl;
            rsT << "syscall" << endl;

            return;
        }
        addr = varaddr(midcode[ mi ].var2);
        int ti = findvartable(midcode[ mi ].var2);
        int kind = addrtable[ ti ].kind;

      //  cout<< midcode[ mi ].var2 << " : " << kind << "@@@@@@@@@@@@@@" << endl;

        if ( kind == INTTK ) {
            rsT << "li\t$v0\t1" << endl;    //li $v0,1
            if ( isglob ) {
                rsT << "lw\t$a0\t" << addr << "($t9)" << endl;
            }else
                rsT << "lw\t$a0\t" << addr << "($fp)" << endl;
            rsT << "syscall" << endl;
        } else {
            rsT << "li\t$v0\t11" << endl;
            if ( isglob )    rsT << "lw\t$a0\t" << addr << "($t9)" << endl;
            else    rsT << "lw\t$a0\t" << addr << "($fp)" << endl;
            rsT << "syscall" << endl;
        }

        rsT << "li\t$v0\t4" << endl;
        rsT << "la\t$a0\t" << "Enter" << endl;
        rsT << "syscall" << endl;

    }
}


//prt,string,expression,int/char
void prtbetter() {
    int addr;
    if ( midcode[ mi ].var1[ 0 ] != '\0' ) {
        int len = strlen(midcode[ mi ].var1);
        for ( int i = 1; i < len-1; i++ ) {
            rsT << "li\t$v0\t11" << endl;
            rsT << "li\t$a0\t" << int(midcode[ mi ].var1[i]) << endl;
            rsT << "syscall" << endl;
        }

    }
    if ( midcode[ mi ].var2[ 0 ] != ' ' && midcode[ mi ].var2[ 0 ] != '\0' ) {
        if ( isdigit(midcode[mi].var2[0]) && strcmp(midcode[mi].var3, "char") == 0 ) {
            rsT << "li\t$v0\t11" << endl;
            rsT << "li\t$a0\t" << midcode[ mi ].var2 << endl;
            rsT << "syscall" << endl;

            rsT << "li\t$v0\t4" << endl;
            rsT << "la\t$a0\t" << "Enter" << endl;
            rsT << "syscall" << endl;

            return;

        } else if ( isdigit(midcode[ mi ].var2[ 0 ]) || midcode[ mi ].var2[ 0 ] == '-' || midcode[ mi ].var2[ 0 ] == '+' ) {
            rsT << "li\t$v0\t1" << endl;
            rsT << "li\t$a0\t" << midcode[ mi ].var2 << endl;
            rsT << "syscall" << endl;

            rsT << "li\t$v0\t4" << endl;
            rsT << "la\t$a0\t" << "Enter" << endl;
            rsT << "syscall" << endl;

            return;
        }

        addr = varaddr(midcode[ mi ].var2);
        int ti = findvartable(midcode[ mi ].var2);
        int kind = addrtable[ ti ].kind;

      //  cout<< midcode[ mi ].var2 << " : " << kind << "@@@@@@@@@@@@@@" << endl;

        if ( kind == INTTK ) {
            rsT << "li\t$v0\t1" << endl;    //li $v0,1

            if(varreg[varaddr000(midcode[mi].var2)]==-1){
                if ( isglob ) {
                    rsT << "lw\t$a0\t" << addr << "($t9)" << endl;
                }else
                    rsT << "lw\t$a0\t" << addr << "($fp)" << endl;

            }
            else{
                int regnum = varreg[varaddr000(midcode[ mi ].var2)];
                rsT << "\t\tadd\t$a0\t$s" <<regnum<<"\t$0" <<endl;//add $a0 $si $0
            }

            rsT << "syscall" << endl;
        } else {
            rsT << "li\t$v0\t11" << endl;

            if(varreg[varaddr000(midcode[mi].var2)]==-1){
                if ( isglob )    rsT << "lw\t$a0\t" << addr << "($t9)" << endl;
                else    rsT << "lw\t$a0\t" << addr << "($fp)" << endl;

            }
            else{
                int regnum = varreg[varaddr000(midcode[ mi ].var2)];
                rsT << "\t\tadd\t$a0\t$s" <<regnum<<"\t$0" <<endl;//add $a0 $si $0
            }
            rsT << "syscall" << endl;
        }

        rsT << "li\t$v0\t4" << endl;
        rsT << "la\t$a0\t" << "Enter" << endl;
        rsT << "syscall" << endl;

    }
}



void intcharasm() {
    if ( isdigit(midcode[ mi ].var2[0]) ) {
        pushstack(midcode[ mi ].var2,1);
    } else {
        pushstack("0",1);
    }
    if ( strcmp(midcode[ mi ].op, "int") == 0 ) {
        insertaddress(INTTK,mi,1);
    } else {
        insertaddress(CHARTK,mi,1);
    }
}

void constdefasm() {
    //常量定义
    while ( strcmp(midcode[ mi ].op, "const") == 0 ) {
        pushstack(midcode[ mi ].var2,1);
        if ( strcmp(midcode[ mi ].var1, "int") == 0 ) {
            insertaddress(INTTK,mi,1);
        } else {
            insertaddress(CHARTK,mi,1);
        }
        mi++;
    }
    mi--;
}

void intcharaasm() {
    //数组定义
    while ( strcmp(midcode[ mi ].op, "inta") == 0 || strcmp(midcode[ mi ].op, "chara") == 0 ) {
           //cout<< atoi(midcode[ mi ].var2)<< "1111111111111111111111111111111111111111111111111" <<endl;
        pushstack("0", atoi(midcode[ mi ].var2));
        if ( strcmp(midcode[ mi ].op, "inta") == 0 ) {
            insertaddress(INTTK,mi,atoi(midcode[mi].var2));
        } else {
            insertaddress(CHARTK,mi,atoi(midcode[mi].var2));
        }
        mi++;
    }
    mi--;

}


void save() {
    if ( OPT ) {
        for ( int i = 1; i < 8; i++ ) {
            rsT << "\t\tsw\t$s" << i << "\t" << 4 * i << "($t8)" << endl;
        }
    }
}

void load() {
    if ( OPT ) {
        for ( int i = 1; i < 8; i++ ) {
            rsT << "\t\tlw\t$s" << i << "\t" << 4 * i << "($t8)" << endl;
        }
    }
}


