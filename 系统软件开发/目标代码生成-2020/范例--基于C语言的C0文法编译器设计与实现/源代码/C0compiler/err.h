#ifndef ERR_H_INCLUDED
#define ERR_H_INCLUDED


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

extern void error(int errsig, int opt = 0);
extern int errnum;

#endif // ERR_H_INCLUDED
