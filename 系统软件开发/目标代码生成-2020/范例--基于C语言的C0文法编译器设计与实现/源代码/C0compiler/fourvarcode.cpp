#include <cstdlib>
#include <string.h>

#include <iostream>
#include <fstream>

#include "global.h"
#include <vector>

using namespace std;

int fvcnt=0;    //四元式计数器

int varcnt = 0; //临时变量计数器
vector <char*> hisvar; //临时变量名字符串链表

int labelcnt = 0;
int tindex = 0;


fourvarcodee midcode[ MAXMIDCODE ];

void fourvarcode (char* op, char* t1, char* t2, char* t3){
    strcpy(midcode[ fvcnt ].op, op);
    strcpy(midcode[ fvcnt ].var1, t1);
    strcpy(midcode[ fvcnt ].var2, t2);
    strcpy(midcode[ fvcnt ].var3, t3);
    fvcnt++;
}



//生成新的临时变量
char* nextreg()
{
    char *var = (char*)malloc(sizeof(char) * 20);
    sprintf(var, "$_%d", varcnt++);
    //insmidcode("int", "  ", "  ", var);
    hisvar.push_back(var);
    return var;
}

void freetempvar(){
    for ( int i = 0; i < hisvar.size(); i++ ) {
        free(hisvar[ i ]);
    }
}

//生成新的标记
char* nextlab(){
    char *label = (char*)malloc(sizeof(char) * 20);
    strcpy(label, "_LABEL_");
    sprintf(label, "_LABEL_%d", labelcnt++);
    return label;
}



//优化部分
//扫描这个四元式数组，处理所有的基本块
void better()
{
    //找到函数开始
    while ( strcmp(midcode[ tindex ].op, "func") != 0 ) tindex++;

    while ( tindex < fvcnt )
	{
        delcommon();
        tindex++;
    }

    return;
}

int ifasscom(int i){

    int tempi=i+1;
    int flg=0;
    do{
        if( strcmp(midcode[ tempi ].op, "=")==0 ){
            if( strcmp(midcode[tempi].var3,midcode[i].var1)==0 || strcmp(midcode[tempi].var3,midcode[i].var2)==0 )
                {
                    flg=1;
                    break;
                }
        }
        tempi++;
    }while(strcmp(midcode[ tempi ].op, "end") != 0);
    if(flg==1)return 1;
    return 0;

}

//删除公共子表达式
void delcommon()
{
    int i, j, h, k;
    //划分基本块
    //基本块中的子表达式i A
    for ( i = tindex; strcmp(midcode[ i ].op, "+") == 0 || strcmp(midcode[ i ].op, "-") == 0 || strcmp(midcode[ i ].op, "*") == 0 || strcmp(midcode[ i ].op, "/") == 0
            || strcmp(midcode[ i ].op, "=") == 0; i++ ) {

        if( midcode[ i ].var3[ 0 ] == '$'){
            if(ifasscom(i)==1)
                continue;
        }
        if ( i >= fvcnt ){
            return;
        }
        //i的结果操作数为中间变量
        if ( midcode[ i ].var3[ 0 ] == '$' ) {
            //寻找四元式基本块中序号i以后与i相同的子表达式B
            for ( j = i + 1; strcmp(midcode[ j ].op, "+") == 0 || strcmp(midcode[ j ].op, "-") == 0 || strcmp(midcode[ j ].op, "*") == 0 || strcmp(midcode[ j ].op, "/") == 0 || strcmp(midcode[ j ].op, "=") == 0; j++ ) {
                if ( j >= fvcnt ){
                    return;
                }
                //寻找公共子表达式(A,B)，B的结果数也为临时变量
                if ( strcmp(midcode[ j ].op, midcode[ i ].op) == 0 && strcmp(midcode[ j ].var1, midcode[ i ].var1) == 0 && strcmp(midcode[ j ].var2, midcode[ i ].var2) == 0 && midcode[ j ].var3[ 0 ] == '$' ) {
                    //找到之后寻找B之后的子表达式与B的var3相同的中间变量，修改Ci中变量的名字为A的结果数
                    for ( h = j + 1; strcmp(midcode[ h ].op, "+") == 0 || strcmp(midcode[ h ].op, "-") == 0 || strcmp(midcode[ h ].op, "*") == 0 || strcmp(midcode[ h ].op, "/") == 0 || strcmp(midcode[ h ].op, "=") == 0; h++ ) {
                        if ( h >= fvcnt ){
                            return;
                        }
                        if ( strcmp(midcode[ h ].var1, midcode[ j ].var3) == 0 )
                            strcpy(midcode[ h ].var1, midcode[ i ].var3);
                        if ( strcmp(midcode[ h ].var2, midcode[ j ].var3) == 0 )
                            strcpy(midcode[ h ].var2, midcode[ i ].var3);
                    }
					//删除B
                    for ( k = j; k< fvcnt; k++ ) {
                        strcpy(midcode[ k ].op, midcode[ k + 1 ].op);
                        strcpy(midcode[ k ].var1, midcode[ k + 1 ].var1);
                        strcpy(midcode[ k ].var2, midcode[ k + 1 ].var2);
                        strcpy(midcode[ k ].var3, midcode[ k + 1 ].var3);
                    }
                    fvcnt--;
                    j--;
                }
            }
        }
    }
}


