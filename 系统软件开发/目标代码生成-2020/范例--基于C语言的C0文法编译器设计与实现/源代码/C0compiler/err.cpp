
#include "global.h"
#include <stdlib.h>
#include <stdio.h>

#define rsT errWrite

#define QUIT 1
#define DONOTHING 2
#define ICV    3
#define ICVFIRST 4
#define CS    5
#define CLR 6
#define SENTENFIRST 7
#define SFIRST 8
#define BFIRST 9

#define SWITCHJUMP 10

int errnum = 0;


void error(int errsig, int opt)
{

    int errclass = -1;
    errnum++;
    rsT<< "Error" << errnum  << " : At Line" << linenum << ", Near symbol \"" << sym <<"\" :\t";
    switch ( errsig ) {
        //case  NOSUCHFILE:            errclass = QUIT;    printf("NO SUCH FILE\n");    break;
        //case  FILEINCOMPLETE:        errclass = DONOTHING;    printf("FILEINCOMPLETE\n");    break;
        case  DOUBLEQUOTESLACK:        errclass = DONOTHING;    rsT<<"DOUBLE QUOTES LACK"<<endl;    break;        //1 少双引号
        case  UNACCEPTATLECHAR:        errclass = DONOTHING;    rsT<<"UNACCEPTATLE CHAR"<<endl;    break;        //2 不可接受字符
        case  SINGLEQUOTESLACK:        errclass = DONOTHING;    rsT<<"SINGLE QUOTES LACK"<<endl;    break;        //3 少单引号
        case  OUTOFTABLE:            errclass = QUIT;           rsT<<"OUT OF TABLE"<<endl;        break;        //4 符号表满
        case  SYMBOLCONFLICT:        errclass = DONOTHING;      rsT<<"SYMBOL CONFLICT"<<endl;     break;        //5 变量名冲突
        case  CSTDEFINEFAIL:        errclass = CS;              rsT<<"CST DEFINE FAIL"<<endl;     break;        //6 const定义失败
       // case  VARNOTINIT:            errclass = DONOTHING;      rsT<<"VARNOTINIT"<<endl;          break;        //7 变量未初始化
        case  UNKNOWRIGHTSYM:        errclass =                                                                 //8 等号右边字符非法
            opt == 0 ? CS :
            opt == 1 ? SFIRST :
            -1;
            rsT<<"UNKNOWRIGHTSYM"<<endl;    break;
        case  SEMICOLONLACK:        errclass =                                                                  //9 少分号
            opt == 0 ? ICVFIRST :
            opt == 1 ? SENTENFIRST :
            opt == 2 ? SFIRST :
            -1;
            rsT<<"SEMICOLONLACK"<<endl;
            break;
        case  KEYWORDERROR:                                                                                     //10 少关键字
            errclass = opt == 0 ? ICVFIRST :
                opt == 1 ? CLR :
                opt == 2 ? SENTENFIRST :
                opt == 3 ? SFIRST:
                -1;
                rsT<<"KEYWORDERROR"<<endl;
            break;
        case  IDENTIFIERLACK:        errclass =                                                                  //少标识符
            opt == 0 ? ICV :
            opt == 1 ? CLR :
            opt == 2 ? SENTENFIRST :
            opt == 3 ? SFIRST :
            opt == 4 ? BFIRST :
            -1;
            rsT<<"IDENTIFIER LACK"<<endl;
            break;
        case  RIGHTBRACKLACK:        errclass =                                                                 //少右中括号
            opt == 0 ? BFIRST :
            opt == 1 ? SENTENFIRST :
            -1;
            rsT<<"RIGHT BRACK LACK"<<endl;
            break;
        case  FUNCTIONNOTFOUND:        errclass =                                                                //函数未定义
            opt == 0 ? SFIRST :
            opt == 1 ? BFIRST :
            -1;
            rsT<<"FUNCTION NOT FOUND"<<endl;    break;
        case  FORMALPARANUMUNMATCH:    errclass =                                                                 //形参个数不匹配
            opt == 0 ? DONOTHING :
            opt == 1 ? SFIRST :
            -1;
            rsT<<"FORMAL PARA NUM UNMATCH"<<endl;    break;
        case  VARNOTDEFINE:            errclass =                                                                 //15 变量未定义
            opt == 0 ? DONOTHING :
            opt == 1 ? SFIRST :
            -1;
            rsT<<"VAR NOT DEFINE"<<endl;    break;
        case  LEFTPARENTLACK:        errclass =                                                                   //少左小括号
            opt == 0 ? ICV :
            opt == 1 ? SFIRST :
            opt == 2 ? BFIRST :
            -1;
            rsT<<"LEFT PARENT LACK"<<endl;    break;
        case  RIGHTPARENTLACK:        errclass =                                                                   //少右小括号
            opt == 0 ? ICV :
            opt == 1 ? SFIRST :
            opt == 2 ? BFIRST :
            -1;
            rsT<<"RIGHT PARENT LACK"<<endl;    break;
        case  IMMLACK:                errclass = opt == 0 ? SENTENFIRST : SWITCHJUMP;    rsT<<"IMM LACK"<<endl;    break;                    //少立即数
        case  RIGHTBRACELACK:        errclass =                                                                     //少右大括号
            opt == 0 ? ICV :
            opt == 1 ? SFIRST :
            -1;
            rsT<<"RIGHT BRACE LACK"<<endl;    break;
        case  FUNCTIONRETURNNULL:    errclass = BFIRST;   rsT<<"FUNCTION RETURN NULL"<<endl;    break;           //函数定义为空
        case  EXPRESSIONERROR:        errclass = BFIRST;    rsT<<"EXPRESSION ERROR"<<endl;    break;             //21 表达式错误
        case  LEFTBRACELACK:        errclass = ICV;    rsT<<"LEFT BRACE LACK"<<endl;    break;                       //少左大括号
        case  NONERETURN:            errclass = ICV;    rsT<<"NON RETURN"<<endl;    break;                          //无返回值
        case  UNACCEPTABLESENTENCE:    errclass = SFIRST;    rsT<<"UNACCEPTABLE SENTENCE"<<endl;    break;       //不可接受句子
        case  ASSIGNCONST:            errclass =                                                                    //赋值常量
            opt == 0 ? SFIRST :
            opt == 1 ? SFIRST :
            -1;
            rsT<<"ASSIGN CONST"<<endl;    break;
        case  PLUSMINULACK:            errclass = SFIRST;    rsT<<"PLUS or MINU LACK"<<endl;    break;            //26 少加号或减号
        case  MAINLACK:                errclass = DONOTHING;    rsT<<"MAIN LACK"<<endl;    break;                     //无main函数
        case  MOREWORD:                errclass = DONOTHING;    rsT<<"MORE WORD"<<endl;    break;                     //main函数后面有多余字符
        case  DEFINEERROR:           errclass = ICV;    rsT<<"VAR DEFINE ERROR"<<endl;    break;
        case  FUNCDEFINEERROR:           errclass = ICV;    rsT<<"FUNC DEFINE ERROR"<<endl;    break;

        case  CONSTNOTINIT:        errclass = CS;    rsT<<"CONST NOT INIT"<<endl;    break;                           //常量未初始化
        case  NONRETFUNCINEXPRE:    errclass = DONOTHING;    rsT<<"NON RETURN FUNC IN EXPRESSION"<<endl;    break;
        case COLONLACK:             errclass = SWITCHJUMP;    rsT<<"COLON LACK"<<endl;    break;
        case  TYPECHANGE:           errclass = DONOTHING;    rsT<<"WARNING:INT CANNOT ASSIGH TO CHAR!!!"<<endl;    break;

        case  UNEXPECTEDCHAR:       errclass = DONOTHING;    rsT<<"UNEXPECTED CHAR"<<endl;    break;
        case PARATYPENOTMATCH:      errclass = DONOTHING;    rsT<<"PARA TYPE NOT MATCH"<<endl;    break;
        case ARRAYOUTBOUND:         errclass = DONOTHING;    rsT<<"Warning: index of array out of boundary"<<endl;    break;
        default:                    errclass = QUIT;    rsT<<"Unknow error occurs!"<<endl;                            //未知错误

    }



    switch ( errclass ){
        case QUIT:

            exit(0);
            break;
        case DONOTHING:
            break;
        case ICV:
            while ( symid != INTTK && symid != CHARTK && symid != VOIDTK ) {
                if ( symid == -1 )
                {
                        exit(0);
                }
                getsym();
            }
            break;
        case ICVFIRST:
            while ( symid != CONSTTK && symid != INTTK && symid != CHARTK && symid != VOIDTK && symid != IFTK
                && symid != FORTK/* && symid != IDEN */&& symid != RETURNTK && symid != SCANFTK && symid != PRINTFTK ){
                if ( symid == -1 ) {     exit(0); }
                getsym();
            }
            break;
        case CS:
            while ( symid != COMMASY && symid != SEMICOLONSY ) {
                if ( symid == -1 ) {     exit(0); }
                getsym();
            }
            break;
        case CLR:
            while ( symid != COMMASY && symid != LSBRASY && symid != RSBRASY ) {
                if ( symid == -1 ) {     exit(0); }
                getsym();
            }
            break;
        case SENTENFIRST://IWFRSPIFCV
            while ( symid != LBBRASY && symid != IFTK && symid != SWITCHTK &&  symid != FORTK && symid != RETURNTK && symid != SCANFTK
                && symid != PRINTFTK  && symid != INTTK  && symid != CHARTK && symid != VOIDTK ) {
                if ( symid == -1 ) {     exit(0); }
                getsym();
            }
            break;

        case SFIRST:
            while ( symid != IFTK && symid != FORTK && symid != SWITCHTK && symid != LMBRASY  && symid != IDEN
                && symid != RETURNTK && symid != SCANFTK && symid != PRINTFTK && symid != ELSETK && symid != RBBRASY) {
                if ( symid == -1 ) {     exit(0); }
                getsym();
            }
            break;

        case BFIRST:
            while ( symid != IFTK && symid != FORTK && symid != SWITCHTK && symid != LMBRASY && symid != IDEN && symid != RETURNTK
                && symid != SCANFTK && symid != PRINTFTK && symid != SEMICOLONSY && symid != ELSETK && symid != RSBRASY
                && symid != COMMASY && symid != PLUSSY && symid != SUBSY && symid != MULTSY && symid != DIVSY
                && symid != LESSY && symid != LESEQSY && symid != GRTSY && symid != GRTEQSY && symid != NEQUALSY && symid != EQUALSY ) {
                if ( symid == -1 ) {     exit(0); }
                getsym();
            }
            break;
        case SWITCHJUMP:
            while ( symid != DEFAULTTK && symid != RBBRASY ) {
                if ( symid == -1 ) {     exit(0); }
                getsym();
            }
        default:
            break;
    }


}
