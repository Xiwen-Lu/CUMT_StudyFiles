//
//  global.h
//  Compiler
//
//  Created by Yang Hu on 2017/11/28.
//  Copyright © 2017年 Yang Hu. All rights reserved.
//

#ifndef global_h
#define global_h

#include <iostream>
#include <fstream>


#define MAXIDENLEN 50  //最长标识符长度
#define MAXSYMTABLENUM 200 //符号表元素最多个数
#define MAXMIDCODE 1000
#define MAXPARANUM 20


#define MAINTK       1
#define INTTK        2
#define CHARTK       3
#define CONSTTK      4
#define VOIDTK       5
#define IFTK         6
#define ELSETK       7
#define SWITCHTK     8
#define CASETK       9
#define DEFAULTTK   10
#define FORTK       11
#define PRINTFTK    12
#define SCANFTK     13
#define RETURNTK    14

#define ASSIGNSY    15
#define PLUSSY      16
#define SUBSY       17
#define MULTSY      18
#define DIVSY       19
#define LESSY       20
#define LESEQSY     21
#define GRTSY       22
#define GRTEQSY     23
#define NEQUALSY    24
#define EQUALSY     25
#define LSBRASY     26
#define RSBRASY     27
#define LMBRASY     28
#define RMBRASY     29
#define LBBRASY     30
#define RBBRASY     31
#define COMMASY     32
#define COLONSY     33
#define SEMICOLONSY 34

#define NUMET       35
#define CHARET      36
#define STRINGET    37
#define IDEN        38

#define CINTET      39
#define CCHARET     40




//err

#define NONRETFUNCINEXPRE   30
#define COLONLACK           31
#define TYPECHANGE          32
#define DEFINEERROR         33
#define FUNCDEFINEERROR     34
#define UNEXPECTEDCHAR      35
#define PARATYPENOTMATCH    36
#define ARRAYOUTBOUND       37


#define DOUBLEQUOTESLACK    1
#define UNACCEPTATLECHAR    2
#define SINGLEQUOTESLACK    3
#define OUTOFTABLE          4
#define SYMBOLCONFLICT      5
#define CSTDEFINEFAIL       6   //常亮声明失败
#define VARNOTINIT          7   //变量未初始化
#define UNKNOWRIGHTSYM      8   //等号右边字符非法
#define SEMICOLONLACK       9   //丢失“；”
#define KEYWORDERROR        10  //关键字错误
#define IDENTIFIERLACK      11  //丢失标志符
#define RIGHTBRACKLACK      12  //丢失“]”
#define FUNCTIONNOTFOUND    13  //调用函数未定义
#define FORMALPARANUMUNMATCH 14 //形参个数不匹配
#define VARNOTDEFINE        15  //未定义变量
#define LEFTPARENTLACK      16  //丢失“（”
#define RIGHTPARENTLACK     17  //丢失“）”
#define IMMLACK             18  //丢失立即数
#define RIGHTBRACELACK      19  //丢失“}”
#define FUNCTIONRETURNNULL  20  //函数无返回值却被用于参数
#define EXPRESSIONERROR     21  //表达式缺失或错误
#define UNACCEPTABLESENTENCE 22 //句子不合法
#define ASSIGNCONST         23  //给常数赋值
#define LEFTBRACELACK       24  //缺少“{”
#define NONERETURN          25  //缺少返回值
#define PLUSMINULACK        26  //缺少‘+’或‘-’
#define MAINLACK            27  //缺少main函数
#define MOREWORD            28  //main函数后面有多余字符
#define CONSTNOTINIT        29    //常量没有初始化



using namespace std;

typedef struct{
    char op[ 10 ];
    char var1[ 200 ];
    char var2[ 30 ];
    char var3[ 30 ];
}fourvarcodee;

extern string text;
extern int pin;
extern char ch;
extern int linenum;

extern string sym;
extern int symid;
//extern char markstr[MAXIDENLEN];
extern string markstr;
extern int num;
extern string stret;


extern int varcnt;
extern int fvcnt;
extern fourvarcodee midcode [ MAXMIDCODE ];

extern int OPT;


extern ofstream mipsWrite,errWrite;


extern void error(int errsig, int opt = 0);
extern int errnum;




void getsym();
void FiletoString();
void conststate();
void constdef(int ctpe);
void defhead();
void vardef();
void varstate();
void scanfsentence();
void printfsentence();
void expression();
void item();
void factor();
void valueofpara();
void returnsentence();
void ifsentence();
void condition();
void loopsentence();
void casesentence();
void sentence();
void sentencelist();
void complexsentence();
void program();
void parametertable();

void fourvarcode(char* op, char* t1, char* t2, char* t3);
char * nextreg();
char * nextlab();

void Tomips();
void funcasm();
void jmpasm();
void callasm();
void setlabasm();
void addasm();
void subasm();
void mulasm();
void divasm();
void greasm();
void geqasm();
void lssasm();
void leqasm();
void eqlasm();
void neqasm();
void assasm();
void aassasm();
void assaasm();
void scfasm();
void prtasm();
void fupaasm();
void retasm();
void paraasm();
void jneasm();
void intcharasm();
void constdefasm();
void intcharaasm();

void callbetter();
void addbetter();
void subbetter();
void mulbetter();
void divbetter();
void grebetter();
void geqbetter();
void lssbetter();
void leqbetter();
void eqlbetter();
void neqbetter();
void assbetter();
void aassbetter();
void assabetter();
void scfbetter();
void prtbetter();
void fupabetter();
void retbetter();

void load();
void save();

void better();
void delcommon();



#endif /* global_h */
