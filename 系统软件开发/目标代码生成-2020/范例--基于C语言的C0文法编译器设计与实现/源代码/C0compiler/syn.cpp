#include <cstdlib>
#include <string.h>

#include <iostream>
#include <fstream>

#include "global.h"

#include <vector>


#define CONST       41   //常亮
#define VARIABLE    42   //变量
#define FUNCTION    43   //函数
#define PARAINT     44   //参数
#define PARACHAR    45



using namespace std;

int  value;     //保存常量的值；对于子程序，0表示void，1表示int
int  address;   //变量的地址；函数返回值的地址
int  paranum;   //全局变量，用来处理函数定义，因为函数的参数个数只能在参数表子程序执行结束之后才知道，所以只能在后面才插入符号表信息
int  kind;      //正在处理的标志符的类型
int tpkind[MAXPARANUM];

int returnnum = 0;
int termtk=0;
char exprevalue[ 200 ];
char funcname[100];

int globdefine = 1;


char name [MAXIDENLEN]; //标志符的名字，包括常量变量和函数



typedef struct{
    char name[ MAXIDENLEN ];  //identifier name
    int kind;               //标识符类型：INTTK,CHARTK,CINTET, CCHARET,FUNCTION,PARA
    int value;              //对于函数来说，2表示返回值为char，1表示返回值为Int 0返回值为void
    int address;            //address，元素在符号表element数组中的下标
    int paranum;            //对函数来说的参数个数

    int parakind[MAXPARANUM];
}symin;

typedef struct {
    symin element[ MAXSYMTABLENUM ];
    int index;
    int ftotal;                 //分程序总数
    int findextable[ MAXSYMTABLENUM ];//分程序索引数组
}symtable;


symtable maintable;

//进符号表函数
void pushtable(char* name, int kind, int value, int address, int paranum, int isVec = 0){

    //whether table is full
    if ( maintable.index >= MAXSYMTABLENUM ){
        error(OUTOFTABLE);
       // cout<<"FULLSYMBOLTABLE"<<endl;
        exit(1);
    }

    //whether conflict
    //function
    if ( kind == FUNCTION ) {
        int iter = 1;
        for ( iter = 1; iter <= maintable.ftotal; iter++ ) {
            if ( strcmp(maintable.element[ maintable.findextable[ iter ] ].name, name)==0 ) {
                error(SYMBOLCONFLICT);
                //cout<<"IDENTIFIERCONFLICT"<<endl;
                return;
            }
        }
        maintable.findextable[ ++maintable.ftotal ] = maintable.index;
    }
    else{
        //others非函数   在函数内部找是否重名局部变量
        int iter = maintable.findextable[ maintable.ftotal ];
        for ( ; iter < maintable.index; iter++ ) {
            if ( strcmp(maintable.element[ iter ].name, name)==0 ) {
                error(SYMBOLCONFLICT);
              //  cout<<"IDENTIFIERCONFLICT"<<endl;
                return;
            }
        }
        //全局变量范围内找与全局变量是否重名
        if ( globdefine ) {
            iter = 0;
            while ( iter < maintable.findextable[ 1 ] ) {
                if ( strcmp(maintable.element[ iter ].name, name) ==0 ) {
                    error(SYMBOLCONFLICT);
                    //cout<<"IDENTIFIERCONFLICT"<<endl;
                    return;
                }
                iter++;
            }
        }
    }

    strcpy(maintable.element[ maintable.index ].name, name);
    maintable.element[ maintable.index ].kind = kind;
    maintable.element[ maintable.index ].value = value;
    maintable.element[ maintable.index ].address = maintable.index;
    maintable.element[ maintable.index ].paranum = isVec ? isVec : paranum;
   /* if (maintable.index <= hiscnt) {
        symtablehis << "----------------------------------------------------------------" << endl;
    }
    hiscnt = maintable.index;*/
    //symtablehis << maintable.index << "\t" << name << "\t" << kind << "\t" << value << "\t" << address << "\t" << paranum << "\t" << isVec << endl;
    maintable.index++;
}


void updatepara(int paranum,int* tkind)
{
    int x = maintable.findextable[ maintable.ftotal ];   //array[i]，指向的是当前正在被分析的函数在符号表中的索引
    maintable.element[ x ].paranum = paranum;//插入函数参数个数信息

    for(int i=0;i<paranum;i++){
        maintable.element[x].parakind[i]=tkind[i];
    }

    return;
}


int arrnum(char *name){
    int n;
    int m = maintable.findextable[ 1 ];
    n = maintable.findextable[ maintable.ftotal ];
    //查找符号表中是否有
    while ( n < maintable.index ) {
        if ( strcmp(maintable.element[ n ].name, name) == 0 )
            return maintable.element[ n ].paranum;
        n++;
    }

    //如果分程序符号表中无定义，查找最外层符号表
    if ( n == maintable.index ) {
        n = 0;
        while ( n < m ) {
            if ( strcmp(maintable.element[ n ].name, name) == 0 )
                return maintable.element[ n ].paranum;
            n++;
        }
        //符号表中没有定义
        if ( n == m ) {
            printf("\"%s\" ", name);
            //error(VARNOTDEFINE);
            return -1;
        }
    }
}

//查符号表
//flag=1时，说明要在分程序索引里查找，flag=0时，在当前所在分程序符号表和最外层全局变量中查找

int searchst(char* name0, int flag){
    int n;
    int m = maintable.findextable[ 1 ];
    if ( flag == 1 ) {

        n = 1;
        while ( n <= maintable.ftotal ) {
            if ( strcmp(maintable.element[ maintable.findextable[ n ] ].name, name0) == 0 )
                break;
            n++;
        }

        //如果函数标志符没有定义
        if ( n > maintable.ftotal ) {
            //printf("\"%s\" ", name);
            error(FUNCTIONNOTFOUND);//IWFLIRSPE
            cout<<"FUNCTIONNOTFOUND"<<endl;
         //   return -1 * FUNCTIONNOTFOUND;
            return -1;
        }

        //如果函数的实参个数与形参个数不匹配
        if ( maintable.element[ maintable.findextable[ n ] ].paranum != paranum ) {
            //printf("\"%s\" ", name);
            error(FORMALPARANUMUNMATCH);//DONOTHING
            cout<<"FUNCPARANUMNMATCH"<<endl;
          //  return -1 * FORMALPARANUMUNMATCH;
          return -1;
        }

        for(int j=0;j<paranum;j++){
            if(maintable.element[maintable.findextable[ n ]].parakind[j]!=tpkind[j]){
                cout<<"WARNING:PARATYPENOTMATCH"<<endl;
                error(PARATYPENOTMATCH);
              //  return -1;
            }
        }


        return maintable.element[ maintable.findextable[ n ] ].address;
    }
    else{
        n = maintable.findextable[ maintable.ftotal ];


        //查找符号表中是否有
        while ( n < maintable.index ) {
            if ( strcmp(maintable.element[ n ].name, name0) == 0 )
                break;
            n++;
        }

        //如果分程序符号表中无定义，查找最外层符号表
        if ( n == maintable.index ) {
            n = 0;
            while ( n < m ) {
                if ( strcmp(maintable.element[ n ].name, name0) == 0 )
                    break;
                n++;
            }
            //符号表中没有定义
            if ( n == m ) {
                //printf("\"%s\" ", name);
                error(VARNOTDEFINE);//DONOTHING
                cout<<"VARNOTDEFINE"<<endl;
                return -1;
            }
        }

        if ( maintable.element[ n ].kind == INTTK || maintable.element[ n ].kind == CHARTK )
            return maintable.element[ n ].address;
        if ( maintable.element[ n ].kind == CINTET || maintable.element[ n ].kind == CCHARET )
            return maintable.element[ n ].address;    //const 返回负两倍地址
        if ( maintable.element[ n ].kind == PARAINT ||  maintable.element[ n ].kind == PARACHAR )
            return maintable.element[ n ].address;    //参数标志
        return -1;
    }
}


//查符号表返回kind
//flag=1时，说明要在分程序索引里查找，flag=0时，在当前所在分程序符号表和最外层全局变量中查找

int searchkind(char* name0, int flag){
    int n;
    int m = maintable.findextable[ 1 ];
    if ( flag == 1 ) {
        n = 1;
        while ( n <= maintable.ftotal ) {
            if ( strcmp(maintable.element[ maintable.findextable[ n ] ].name, name0) == 0 )
                break;
            n++;
        }

        //如果函数标志符没有定义
        if ( n > maintable.ftotal ) {
            //printf("\"%s\" ", name);
    //        error(FUNCTIONNOTFOUND);
            cout<<"FUNCTIONNOTFOUND"<<endl;
         //   return -1 * FUNCTIONNOTFOUND;
            return -1;
        }

        //如果函数的实参个数与形参个数不匹配
        if ( maintable.element[ maintable.findextable[ n ] ].paranum != paranum ) {
            //printf("\"%s\" ", name);
   //         error(FORMALPARANUMUNMATCH);
            cout<<"FUNCPARANUMNMATCH"<<endl;
          //  return -1 * FORMALPARANUMUNMATCH;
          return -1;
        }
/*
        //如果函数标识符无内容
        if ( maintable.element[ maintable.findextable[ n ] ].value == 0 )
            //return -1 * FUNCTIONRETURNNULL;
            return -1;
*/

        return maintable.element[ maintable.findextable[ n ] ].value;
    }
    else{
        n = maintable.findextable[ maintable.ftotal ];


        //查找符号表中是否有
        while ( n < maintable.index ) {
            if ( strcmp(maintable.element[ n ].name, name0) == 0 )
                break;
            n++;
        }

        //如果分程序符号表中无定义，查找最外层符号表
        if ( n == maintable.index ) {
            n = 0;
            while ( n < m ) {
                if ( strcmp(maintable.element[ n ].name, name0) == 0 )
                    break;
                n++;
            }
            //符号表中没有定义
            if ( n == m ) {
                //printf("\"%s\" ", name);
    //            error(VARNOTDEFINE);
                cout<<"VARNOTDEFINE"<<endl;
                return -1;
            }
        }



        if ( maintable.element[ n ].kind == INTTK || maintable.element[ n ].kind == CINTET || maintable.element[ n ].kind == PARAINT )
            return INTTK;
        if ( maintable.element[ n ].kind == CHARTK || maintable.element[ n ].kind == CCHARET || maintable.element[ n ].kind == PARACHAR ){
           // cout<<  CHARTK << "     33333333333333" << endl;
            return CHARTK;    //const 返回负两倍地址
        }


        return -1;
    }
}





void popst(){
    int x = maintable.index - 1;

    while ( ( maintable.element[ x ].kind == INTTK || maintable.element[ x ].kind == CHARTK || maintable.element[ x ].kind == CINTET
            || maintable.element[ x ].kind == CCHARET || maintable.element[ x ].kind == PARAINT || maintable.element[ x ].kind == PARACHAR)
            && strcmp(maintable.element[ x ].name, funcname) != 0 ) {
        maintable.element[ x ].kind = 0;
        maintable.element[ x ].address = 0;
        maintable.element[ x ].paranum = 0;
        maintable.element[ x ].value = 0;

        memset(maintable.element[ x ].name,'\0',sizeof(maintable.element[ x ].name));

        x--;
    }
    maintable.index = x + 1;
    return;
}



//＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}  const int a=1;
void conststate(){
     while ( symid == CONSTTK ) {
         getsym();
         int ctpe;
         if ( symid == INTTK || symid == CHARTK ) {

             kind = ( symid == INTTK ) ? CINTET : CCHARET;
             address = 0;
             paranum = 0;

             ctpe = symid;
             getsym();
             constdef(ctpe);
             while ( symid == COMMASY ) {
                 getsym();
                 constdef(ctpe);
             }
             //定义结束，下一个字符一定是分号
             if ( symid != SEMICOLONSY ) {
                 error(SEMICOLONLACK,0);//CICVIFIRSP
                 cout<<"SEMICOLONLACK"<<endl;
                 //return;
                 //getsym();
                 continue;
             }
             getsym();
         }
         else{
             error(KEYWORDERROR,0);//CICVIFIRSP
          //不是int或者char
             cout<<"KEYWORDERROR"<<endl;
             return;
         }
     }

    // cout<<"This is a const statement!"<<endl;
     return;
 }

 //＜常量定义＞   ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}

 //                           | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}


 void constdef( int ctpe ){
     //without int or char   a=123/char='a'
      char temp[ 200 ];
      //结构：IDEN = XXXX
      if ( symid == IDEN ) {
          //name记录标识符名称
          strcpy(name, markstr.c_str() );
        // name = markstr;
          getsym();
          //if is '='
          if ( symid == ASSIGNSY ) {
              getsym();
              // if is '+' or '-'
              if ( symid == PLUSSY || symid == SUBSY ) {
                  int symb = symid;
                  getsym();
                  // if is integer
                  if ( ctpe == INTTK && symid == NUMET ) {
                      if ( symb == PLUSSY ) {
                          value = num;
                      }
                      else{
                          value = 0 - num;
                      }
                      pushtable(name, kind, value, address, paranum);
                      sprintf(temp, "%d", value);
                      fourvarcode("const", "int", temp, name);

                  }
              }
              // if is char
              else if ( symid == CHARET && ctpe==CHARTK ){
                value = stret.c_str()[1];
                pushtable(name, kind, value, address, paranum);
                sprintf(temp, "%d", stret.c_str()[1]);
                fourvarcode("const", "char", temp, name);
              }
              //无符号整数
              else if ( symid == NUMET && ctpe == INTTK ){
                value = num;
                pushtable(name, kind, value, address, paranum);
                sprintf(temp, "%d", value);
                fourvarcode("const", "int", temp, name);
              }
              else{
                  error(UNKNOWRIGHTSYM,0);//CS
                cout<<"UNKNOWRIGHTSYM"<<endl;
                return;
              }
          }
          //没有赋值符号
          else{
              error(CONSTNOTINIT);//CS
              cout<<"CONSTNOTINIT"<<endl;
              return;
          }
          num=0;
      }
      else
      {
         error(CSTDEFINEFAIL);//CS
         //未识别到标识符
         cout<<"CSTDEFINEFAIL"<<endl;
         return;
      }
      getsym();
      return;
  }


  //＜声明头部＞   ::=  int＜标识符＞ | char＜标识符＞
//ATTENTION: 读到的是int/char和标识符以及其后面的一个单词！！
 void defhead()
 {

     if ( symid == INTTK || symid == CHARTK ) {
         kind = symid;
         getsym();

         if ( symid != IDEN ) {
            error(IDENTIFIERLACK, 1);//CLR  逗号,或者括号( )
            cout<<"IDENLACK"<<endl;
            return;
         }
         else {

            strcpy(name, markstr.c_str());//拷贝函数的名字;
         }
     }
     else{
         error(KEYWORDERROR, 1);//CLR
         cout<<"KEYWORDERROR"<<endl;
         return;
     }
     getsym();
  //   cout<<"This is a define head!"<<endl;
     return;
}


//＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
void varstate()
{
  //  while(symid==INTTK || symid==CHARTK){
         vardef();
        //缺少';'
        if ( symid != SEMICOLONSY ) {
            error(SEMICOLONLACK, 1);//SENTENFIRST
            cout<<"SEMICOLONLACK"<<endl;
            return;

        }
        getsym();
  //  }
   // cout<<"This is a variable statement!"<<endl;
    return;
}

//＜变量定义＞  ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’) }
// int a/int a[22]/int a,b[11]
void vardef()
{
    if ( symid == INTTK || symid == CHARTK ) {
        kind=symid;
        getsym();
        if ( symid != IDEN ) {
            error(IDENTIFIERLACK, 2);//SENTENFIRST
            cout<<"IDENTIFIERLACK"<<endl;
            return;
        }
        else {
            strcpy(name, markstr.c_str());
        }
    }
    else{
        error(KEYWORDERROR, 2);//SENTENFIRST
        cout<<"KEYWORDERROR"<<endl;
        return;
    }
    getsym();

    int isArr = ( symid == LMBRASY );
    value = 0;
    address = 0;
    paranum = 0;

    if ( isArr ) {    //如果是数组
        getsym();
        if ( symid != NUMET ) {
            error(IMMLACK);//SENTENFIRST
           //此处处理无符号整数？？？？？？？？？？？？？？？？？？！！！！！！！！！！！！！！！！！！！！！
            cout<<"IMMLACK"<<endl;
            return;
        }
        else{
           if(num==0) {
                //数组定义下标为0
                error(IMMLACK);//SENTENFIRST
                cout<<"ARRAYERROR"<<endl;
                return;
           }
            pushtable(name, kind, value, address, paranum, num);

            if ( kind == INTTK ){
                 char tempnum[20];
                 sprintf(tempnum,"%d",num);
                 fourvarcode("inta","  ",tempnum, name);

            }


            else if ( kind == CHARTK ){
                 char tempnum[20];
                sprintf(tempnum,"%d",num);
                fourvarcode("chara","  ",tempnum, name);
            }


            getsym();
            if ( symid != RMBRASY ){
                error(RIGHTBRACKLACK, 1);//SENTENFIRST
                cout<<"RMBRALACK"<<endl;
                return;
            }
             else{
                 getsym();
            }
        }
    }
    else{
            //不是数组
        pushtable(name, kind, value, address, paranum, isArr);
        if ( kind == INTTK )
            fourvarcode("int", "  ", "  ", name);

        else if ( kind == CHARTK )
            fourvarcode("char", "  ", "  ", name);

    }

    num=0;

    //如果后面是逗号，那么变量定义未结束
    while ( symid == COMMASY ) {
//cout<<symid<<endl;
        getsym();

        if(symid != IDEN ){
            error(IDENTIFIERLACK, 2);
            cout<<"IDENTIFIERLACK"<<endl;//SENTENFIRST
            return;
        }

        strcpy(name, markstr.c_str());
        getsym();
        int isArr = ( symid == LMBRASY );

        if ( isArr ) {    //如果是数组


            getsym();

            if ( symid != NUMET ) {
                error(IMMLACK);//SENTENFIRST
               //此处处理无符号整数？？？？？？？？？？？？？？？？？？！！！！！！！！！！！！！！！！！！！！！
                cout<<"IMMLACK"<<endl;
                return;
            }
            else{
                pushtable(name, kind, value, address, paranum, num);

                if ( kind == INTTK ){
                    char tempnum [20];
                    sprintf(tempnum,"%d",num);

                    fourvarcode("inta", "  ", tempnum, name);
                }


                else if ( kind == CHARTK ){

                    char tempnum [20];
                    sprintf(tempnum,"%d",num);
                    fourvarcode("chara", "  ", tempnum, name);
                }


                getsym();
                if ( symid != RMBRASY ) {
                        error(RIGHTBRACKLACK);//SENTENFIRST
                    cout<<"RMBRALACK"<<endl;
                    return;
                }
                 else{
                     getsym();
                }
            }
        }
        else{
                //不是数组
            pushtable(name, kind, value, address, paranum, isArr);
            if ( kind == INTTK )
                fourvarcode("int", "  ", "  ", name);

            else if ( kind == CHARTK )
                fourvarcode("char", "  ", "  ", name);

        }
        num = 0;
    }
    return;
}

//＜读语句＞    ::=  scanf ‘(’＜标识符＞{,＜标识符＞}‘)’
void scanfsentence()
{
    char names[ 30 ];
    int s;
    getsym();
    if ( symid != LSBRASY ) {
            error(LEFTPARENTLACK, 1);//IWFLIRSPE
        cout<<"LSBRALACK"<<endl;
        return;
    }

    do{
        getsym();
        if ( symid != IDEN ) {
                error(IDENTIFIERLACK, 3);//IWFLIRSPE
            cout<<"IDENTIFIERLACK"<<endl;         //不合法的标志符
            return;
        }

        strcpy(names, markstr.c_str());
        s = searchst(names, 0);
        if ( s < 0 ) {
                /*
            if ( s == -1 )
                error(VARNOTDEFINE, 1);            //未定义标志符
            else
                error(ASSIGNCONST, 1);*/
            return;

        }
        fourvarcode("scf", "  ", "  ", names);
        getsym();
    } while ( symid == COMMASY );

    if ( symid != RSBRASY ) {
            error(RIGHTPARENTLACK, 1);//IWFLIRSPE
        cout<<"RSBRALACK"<<endl;
        return;
    }

    getsym();
    return;
}


//＜写语句＞    ::= printf ‘(’ ＜字符串＞,＜表达式＞ ‘)’| printf ‘(’＜字符串＞ ‘)’| printf ‘(’＜表达式＞‘)’
void printfsentence()
{

    char str1[ 200 ] = "", str2[ 30 ] = ""; //str1是字符串，str2是表达式
    getsym();
    if ( symid != LSBRASY ) {
            error(LEFTPARENTLACK, 1);//IWFLIRSPE
        cout<<"LSBRALACK"<<endl;
        return;
    }

    getsym();

    if ( symid == STRINGET ) {
        strcpy(str1, stret.c_str());
        getsym();
        if ( symid == COMMASY ) {
            getsym();
            expression();
            strcpy(str2, exprevalue);
        }
    }
    else {
        expression();
        strcpy(str2, exprevalue);
    }


    if ( symid != RSBRASY ) {
            error(RIGHTPARENTLACK, 1);//IWFLIRSPE
        cout<<"RSBRALACK"<<endl;
        return;
    }

    string tempstr = (termtk == CHARTK) ? "char" : "int";


   // cout<< termtk<< "   1111111111111111111111111111111" <<endl;
    fourvarcode("prt", str1, str2, (char*)tempstr.data());
    getsym();
    return;
}

//＜返回语句＞   ::=  return[‘(’＜表达式＞‘)’]
void returnsentence()
{
    char str3[ 30 ];
    getsym();
    if ( symid == LSBRASY ) {
        getsym();
        expression();//表达式子程序
        strcpy(str3, exprevalue);

        if ( symid != RSBRASY ) {
                error(RIGHTPARENTLACK, 1);//IWFLIRSPE
            cout<<"RSBRALACK"<<endl;
            return;
        }
        returnnum++;
        fourvarcode("ret", "  ", "  ", exprevalue);
        getsym();
        return;
    }

    fourvarcode("ret", "  ", "  ", "  ");

    return;
}

////＜表达式＞    ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
void expression()
{
    termtk = 0;
    char str1[ 30 ],str2[ 30 ], str3[ 30 ];

    //有＋｜－的情况
    if ( symid == PLUSSY || symid == SUBSY ) {
        termtk = INTTK;
        if ( symid == PLUSSY ) {
            getsym();
            item();//项，结束后，项的结果会放入全局变量expervalue
            strcpy(str3, exprevalue);//把项的结果放入临时变量的位置

        }
        else if ( symid == SUBSY ) {
            getsym();
            item();//项
            strcpy(str1, exprevalue);
            strcpy(str3, nextreg());
            fourvarcode("-", "0 ", str1, str3); //place3 = 0 - (place1)
        }
    }
    else {
        item();
        strcpy(str3, exprevalue);
     //   cout<<symid<<endl;
    }

    while ( symid == PLUSSY || symid == SUBSY ) {
        termtk = INTTK;
        strcpy(str1, str3);
        if ( symid == PLUSSY ) {
            getsym();
            item();
            strcpy(str2, exprevalue);
            strcpy(str3, nextreg());
            fourvarcode("+", str1, str2, str3);
            continue;
        }
        else {
            getsym();
            item();
            strcpy(str2, exprevalue);
            strcpy(str3, nextreg());
            fourvarcode("-", str1, str2, str3);
            continue;
        }
    }
    strcpy(exprevalue, str3);//把表达式的最终值存放在p之中
    return;
}

//＜项＞     ::= ＜因子＞{＜乘法运算符＞＜因子＞}
void item()
{
    char str1[ 200 ], str2[ 200 ], str3[ 200 ];
    factor();
    strcpy(str3, exprevalue);

    while ( symid == MULTSY || symid == DIVSY ) {
        termtk = INTTK;
        strcpy(str1, str3);
        if ( symid == MULTSY ) {
            getsym();
            factor();
            strcpy(str2, exprevalue);
            strcpy(str3, nextreg());//申请临时变量
            fourvarcode("*", str1, str2, str3);
            continue;

        }
        else if ( symid == DIVSY ) {
            getsym();
            factor();
            strcpy(str2, exprevalue);
            strcpy(str3, nextreg());
            fourvarcode("/", str1, str2, str3);
            continue;
        }
    }
    strcpy(exprevalue, str3);  //每一个项，计算后的值都在变量exprevalue里面
    return;
}


//＜因子＞    ::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’
void factor()
{
    int t = -1;
    char names[ 30 ], str3[ 30 ];

    //＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜有返回值函数调用语句＞
    if ( symid == IDEN ) {
        strcpy(names, markstr.c_str());
        getsym();
        //如果有左括号，则是＜有返回值函数调用语句＞
        if ( symid == LSBRASY ) {
            getsym();
            valueofpara();
            if ( symid != RSBRASY ) {
                    error(LEFTPARENTLACK, 2);//IWFXXXANE
                cout<<"RSBRALACK"<<endl;
                return;
            }

            t = searchst(names, 1);
            if ( t < 0 ) {
                /*if ( t == -1 * FUNCTIONRETURNNULL )
                    error(FUNCTIONRETURNNULL);   //函数无返回值，不能出现在表达式中
                else if ( t == -1 * FUNCTIONNOTFOUND )
                    error(FUNCTIONNOTFOUND, 1);
                    */
                return;
            }

            if(t==0){
            //        error(NONRETFUNCINEXPRE);//IWFXXXANE
           //     cout<<"NON RETURN FUNC IN EXPRESSION"<<endl;
            }


            if( termtk != INTTK )
                termtk == ( maintable.element[t].value == 1 )? INTTK:CHARTK;


            strcpy(str3, nextreg());//生成临时变量
            fourvarcode("call", names, "  ", str3);//将调用的返回值存放在临时变量里面
            strcpy(exprevalue, str3);


            getsym();
            cout<<"This is a returnfunction diaoyong sentence!"<<endl;
            return;
        }

        //＜标识符＞‘[’＜表达式＞‘]’
        else if ( symid == LMBRASY ){      //如果是数组元素
            //?????????????????????????数组元素中括号表达式里termtk只能是INTTK
            getsym();
            //int tk = termtk;
            t = searchst(names, 0);
            int tk = searchkind(names,0);

            expression();
            if(termtk != INTTK)
            {
                cout<<"INVALID ARRAR INDEX"<<endl;
                error(IMMLACK);
                return;
               // exit(1);
            }
            if(termtk != INTTK){
                termtk = tk;
            }

            char temp[ 30 ];
            strcpy(temp, exprevalue);

            //数组边界溢出判断

            if (isdigit(exprevalue[0])){
                int arrnums = 0;
                arrnums = arrnum(names);
                if (atoi(temp) >= arrnums){

                    printf("Warning: Line:%d index of array out of boundary, which should be less than %d.\n",linenum, atoi(temp));
                    error(ARRAYOUTBOUND);
                }
            }


            if ( symid != RMBRASY ) {
                    error(RIGHTBRACKLACK);//IWFXXXANE
                cout<<"RMBRALACK"<<endl;
                return;
            }
            else{
                strcpy(exprevalue, nextreg());
                fourvarcode("geta", names, temp, exprevalue);
                getsym();
            }
        }

        //如果是＜标识符＞
        else{



          //  cout<< termtk << "   22222222222222222222222222" <<endl;

            t = searchst(names, 0);      //查表，查找到标识符对应的地址
            if (t <0 ) {
                error(IDENTIFIERLACK, 4);//IWFXXXANE
                cout<<"IDENTIFIERLACK"<<endl;
                return;
            }
            if ( termtk!=INTTK) {
                termtk = searchkind(names,0);
            }

            /*
            if ( t < -1 ) {
                t = -t / 2;
            }
            */
            strcpy(exprevalue, names);
        }


        return;
    }

    //'('＜表达式＞')'
    else if ( symid == LSBRASY ) {
        getsym();
        expression();
        if ( symid != RSBRASY ) {
                error(RIGHTPARENTLACK, 2);//IWFXXXANE
            cout<<"RSBRALACK"<<endl;
            return;
        }
        getsym();
        return;
    }

    // ＜整数＞｜＜字符＞
    //此处要处理正负号与字符的关系！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！factclass,正负号与0的关系
    else if ( symid == PLUSSY || symid == SUBSY || symid == NUMET || symid == CHARET ) {

        if(symid == PLUSSY || symid == SUBSY){
            int t=(symid==PLUSSY)?1:-1;
            getsym();
            //处理数字
            termtk = INTTK;
            sprintf(exprevalue, "%d", t * num);
            num = 0;
            //再读一个
            getsym();
            return;
        }

        else if(symid == NUMET){
            termtk = INTTK;
            sprintf(exprevalue, "%d",  num);
            //itoa(num,exprevalue,10);
     //       cout<< exprevalue<< "11111111111111111111111111111111111111111111111111111111" <<endl;
            num=0;
            getsym();
            return;
        }
        else if(symid == CHARET){
            if ( termtk != INTTK ) {
                termtk = CHARTK;
            }
            sprintf(exprevalue, "%d", stret.c_str()[1]);
           // cout<<exprevalue<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
            getsym();
            return;
        }

    }


    cout<<"EXPRESSIONERROR"<<endl;//IWFXXXANE
    error(EXPRESSIONERROR);                  //表达式缺失或错误
    return;
}


//＜值参数表＞   ::= ＜表达式＞{,＜表达式＞}｜＜空＞
void valueofpara()
{
    int j = 0;
    vector<string> paraqueue;



    do {
        if ( symid == COMMASY )
            getsym();
        if ( symid == PLUSSY || symid == SUBSY || symid == IDEN || symid == LSBRASY || symid == CHARET || symid == NUMET ) {
            expression();
            paraqueue.push_back(exprevalue);
            tpkind[j]=termtk;
            j++;
        }
    } while ( symid == COMMASY );

    char tc[ 20 ];
    for ( int i = 0; i < paraqueue.size(); i++ ) {
        strcpy(tc, paraqueue[ i ].c_str());
        fourvarcode("fupa", "  ", "  ", tc);
    }
    paranum = j;
    paraqueue.~vector();

    return;
}


//＜语句列＞   ::= ｛＜语句＞｝
//＜语句＞    ::= ＜条件语句＞｜＜循环语句＞| ‘{’＜语句列＞‘}’｜＜有返回值函数调用语句＞;

//                      | ＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞;|＜情况语句＞｜＜返回语句＞;
void sentencelist()
 {
     //sentence();
     //语句，如果读到的是如下的东西，那么还是语句
     while ( symid == IFTK || symid == FORTK || symid == LBBRASY
         || symid == IDEN || symid == RETURNTK || symid == SCANFTK || symid == PRINTFTK|| symid == SWITCHTK || symid == SEMICOLONSY ) {
         sentence();
     }
 }

 //＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
 void ifsentence()
 {
    char label1[ 20 ], label2[ 20 ], conditionvalue[ 30 ];
    strcpy(label1, nextlab());  //如果不满足if，则跳过label1，label1是if的结束部分
    strcpy(label2, nextlab());  //如果还有else，则else的结束位置是label2

     getsym();
     //少“(”
     if ( symid != LSBRASY ) {
                error(LEFTPARENTLACK, 1);//IWFLIRSPE
         cout<<"LSBRALACK"<<endl;
         return;
     }
     getsym();
     //＜条件＞
     condition();

     strcpy(conditionvalue, exprevalue);  //条件计算的值在nowitem里面,此处应该是个临时变量$_x
     fourvarcode("jne", "  ", "  ", label1);  //比较，为假的时候跳转到label1

     if ( symid != RSBRASY ) {
            error(RIGHTPARENTLACK, 1);//IWFLIRSPE
         cout<<"RSBRALACK"<<endl;
         return;
     }
     getsym();
     sentence();

     fourvarcode("jmp", "  ", "  ", label2);//不执行else的部分,jump到lable2
     fourvarcode("lab:", "  ", "  ", label1);

     if ( symid == ELSETK ) {
         getsym();
         sentence();
     }
     fourvarcode("lab:", "  ", "  ", label2);
     return;
 }

//＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞
void condition()
 {

     char str1[ 30 ], str2[ 30 ];
     expression();
     strcpy(str1, exprevalue);  //条件至少有一个表达式

     //关系运算符
     if ( symid == LESSY || symid == LESEQSY || symid == GRTSY || symid == GRTEQSY || symid == EQUALSY || symid == NEQUALSY ) {
         if ( symid == LESSY ) {
             getsym();
             expression();
             strcpy(str2, exprevalue);
             fourvarcode("<", str1, str2, "  ");
         }
         else if ( symid == LESEQSY ) {
             getsym();
             expression();
             strcpy(str2, exprevalue);
             fourvarcode("<=", str1, str2, "  ");

         }
         else if ( symid == GRTSY ) {
             getsym();
             expression();
             strcpy(str2, exprevalue);
             fourvarcode(">", str1, str2, "  ");

         }
         else if ( symid == GRTEQSY ) {
             getsym();
             expression();
             strcpy(str2, exprevalue);
             fourvarcode(">=", str1, str2, "  ");

         }
         else if ( symid == EQUALSY ) {
             getsym();
             expression();
             strcpy(str2, exprevalue);
             fourvarcode("==", str1, str2, "  ");

         }
         else if ( symid == NEQUALSY ) {
             getsym();
             expression();
             strcpy(str2, exprevalue);
             fourvarcode("!=", str1, str2, "  ");

         }
        return;

     }
     strcpy(str2, "0");
     fourvarcode("!=", str1, str2,"  ");
     return;
 }


 //＜循环语句＞::=  for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞
  void loopsentence()
{
    int s = 0;
    char names[ 30 ], names1[ 30 ], names2[ 30 ], place2[ 30 ], place3[ 30 ];
    char label1[ 20 ], label2[ 20 ], label3[ 20 ] , op_flag[ 5 ];
    strcpy(label1, nextlab());
    strcpy(label2, nextlab());
    strcpy(label3, nextlab());

    if ( symid == FORTK ) {    //for|(...)
        getsym();
        if ( symid != LSBRASY ) {//for(|...)
                error(LEFTPARENTLACK, 1);//IWFLIRSPE
            cout<<"LSBRALACK"<<endl;
            return;
        }
        getsym();

        if ( symid != IDEN ) {    //for(i=x;...;...)
            error(UNACCEPTABLESENTENCE);//IWFLIRSPE
           cout<<"IDENTIFIERLACK"<<endl;
            return;
        }
        strcpy(names, markstr.c_str());

        getsym();
        if ( symid != ASSIGNSY ) {    //for(i=..;...;...)
            error(UNACCEPTABLESENTENCE);//IWFLIRSPE
           cout<<"ASSIGNLACK"<<endl;
            return;
        }


        s = searchst(names, 0);
        if ( s < 0 ) {     //如果是常量
            /*if ( s == -1 ) error(VARNOTDEFINE, 1);  //"="左边是不合法的标识符
            else    error(ASSIGNCONST);*/
            return;
        }


        getsym();
        expression();    //for(i=a+b|;...;...)
        fourvarcode("=", exprevalue, "  ", names);

        if ( symid != SEMICOLONSY ) {
                error(SEMICOLONLACK, 2);//IWFLIRSPE
            cout<<"SEMICOLONLACK"<<endl;
            return;
        }
        getsym();//for(i=a+b;|...;...)

        fourvarcode("jmp", "  ", "  ", label3);
        fourvarcode("lab:", "  ", "  ", label1);

        condition();//for(i=a+b;...;|...)
        fourvarcode("jne", "  ", "  ", label2);
        fourvarcode("lab:", "  ", "  ", label3);

        if ( symid != SEMICOLONSY ) {
                error(SEMICOLONLACK, 2);//IWFLIRSPE
            cout<<"SEMICOLONLACK"<<endl;
            return;
        }
        getsym();        //for(i=a+b;...;|...)

        if ( symid != IDEN ) {
                 error(IDENTIFIERLACK, 3);//IWFLIRSPE
            cout<<"IDENTIFIERLACK"<<endl;
            return;
        }
        strcpy(names1, markstr.c_str());

        s = searchst(names1, 0);
        if ( s < 0 ) {     //如果是常量
           /* if ( s == -1 ) error(VARNOTDEFINE, 1);  //"="左边是不合法的标识符
            else    error(ASSIGNCONST);
                */
            return;
        }

         //＜标识符＞＝＜标识符＞(+|-)＜步长＞!!!!!!!!!!!
        //＜步长＞    ::=  ＜非零数字＞｛＜数字＞｝

        getsym();
        if ( symid != ASSIGNSY ) {
                error(UNACCEPTABLESENTENCE);//IWFLIRSPE
            cout<<"ASSIGNLACK"<<endl;
            return;
        }
        getsym();
        if ( symid != IDEN ) {
            error(IDENTIFIERLACK, 3);//IWFLIRSPE
            cout<<"IDENTIFIERLACK"<<endl;
            return;
        }

        strcpy(names2, markstr.c_str());
        s = searchst(names2, 0);
        if ( s < 0 ) {     //如果是常量
          /*  if ( s == -1 ) error(VARNOTDEFINE, 1);  //"="左边是不合法的标识符
             else    error(ASSIGNCONST);*/
            return;
        }


        getsym();
        if ( symid != PLUSSY && symid != SUBSY ) {
                error(PLUSMINULACK);//IWFLIRSPE
            cout<<"PLUSSUBLACK"<<endl;
            return;
        }
        if ( symid == PLUSSY ) strcpy(op_flag, "+");
        else if ( symid == SUBSY ) strcpy(op_flag, "-");

        getsym();
        if ( symid != NUMET || num==0 ) {
                //此处要判断等号右边不为0！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
            error(UNKNOWRIGHTSYM, 1);     //等号右边不是合法的整数
            cout<<"NUMLACK"<<endl;
            return;
        }

        sprintf(place2,"%d",num);

        getsym();
        if ( symid != RSBRASY ) {
            error(RIGHTPARENTLACK, 1);//IWFLIRSPE
            cout<<"RSBRALACK"<<endl;
            return;
        }

        getsym();
        sentence();

        strcpy(place3, nextreg());
        fourvarcode(op_flag, names2, place2, place3);
        fourvarcode("=", place3, "  ", names1);

        fourvarcode("jmp", "  ", "  ", label1);
        fourvarcode("lab:", "  ", "  ", label2);

        return;
    }
}

//＜情况语句＞  ::=  switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞＜缺省＞‘}’

//＜情况表＞   ::=  ＜情况子语句＞{＜情况子语句＞}

//＜情况子语句＞  ::=  case＜常量＞：＜语句＞

//＜缺省＞   ::=  default : ＜语句＞

void casesentence()
{
    char label1[ 20 ],label2[20];
    char place1[50];
    int flg=0;

    strcpy(label2, nextlab());

    getsym();
    if ( symid != LSBRASY ) {
            error(LEFTPARENTLACK, 1);
        cout<<"LSBRALACK"<<endl;
        return;
    }
    getsym();
    expression();

    strcpy(place1,exprevalue);

    if ( symid != RSBRASY ) {
            error(RIGHTPARENTLACK, 1);
        cout<<"RSBRALACK"<<endl;
        return;
    }

    getsym();
    if ( symid != LBBRASY ) {
            error(LEFTBRACELACK, 1);
        cout<<"LBBRALACK"<<endl;
        return;
    }
    getsym();

    do{
        strcpy(label1, nextlab());

        char place2[50];

        if( symid == CASETK ){
            getsym();
            char ttt[50];
            if(symid == SUBSY || symid== PLUSSY|| symid == NUMET || symid == CHARET ){
                int t=1;

                if(symid == SUBSY || symid == PLUSSY){
                    t = (symid == SUBSY) ? -1 : 1 ;
                    getsym();
                }

                if(symid==NUMET)
                    sprintf(ttt,"%d",t*num);
                else{
                    //place2[0]='\'';
                    place2[0]=stret[1];
                   // place2[2]='\'';
                    place2[1]='\0';
                    sprintf(ttt,"%d",place2[0]);

                }

                fourvarcode("==", place1, ttt, "  ");
                //跳转如果不满足
                fourvarcode("jne", "  ", "  ", label1);
                getsym();
                //如果没有冒号
                if ( symid != COLONSY ) {
                        error(COLONLACK);
                    cout<<"COLONLACK"<<endl;
                    return;
                    break;
                }
                getsym();
                sentence();
                fourvarcode("jmp", "  ", "  ", label2);//满足条件，不再执行switch语句中其余部分
            }
            else{
                error(IMMLACK,1);//
                cout<<"IMMLACK"<<endl;
    //           return;
                ;
            }

            fourvarcode("lab:", "  ", "  ", label1);

        }
        else{

            error(KEYWORDERROR,2);//
            cout<<"CASETKLACK"<<endl;
      //      cout<< sym << "1111111111111111111111111111111111111111111" <<endl;
            return;
            break;
        }

    }while(symid==CASETK);

    //如果没有default
    if ( symid != DEFAULTTK ) {
            error(KEYWORDERROR,2);
        cout<<"DEFAULTTKLAKE"<<endl;
        return;
    }
    getsym();

    //如果没有冒号
    if ( symid != COLONSY ) {
            error(COLONLACK);
        cout<<"COLONLACK"<<endl;
        return;
    }
    getsym();
    sentence();

    if ( symid != RBBRASY ) {
        error(RIGHTBRACELACK, 1);
        cout<<"RBBRALACK"<<endl;
        return;
    }

    getsym();
    fourvarcode("lab:", "  ", "  ", label2);
    return;
}


//＜语句＞    ::= ＜条件语句＞｜＜循环语句＞| ‘{’＜语句列＞‘}’｜＜有返回值函数调用语句＞;

//                      | ＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞;|＜情况语句＞｜＜返回语句＞;
void sentence(){
    int s;

    //条件语句
    if ( symid == IFTK ) {
        ifsentence();
        cout<<"This is a if sentence!"<<endl;
        return;
    }

    //循环语句
    if ( symid == FORTK ) {
        loopsentence();
        cout<<"This is a loop sentence!"<<endl;
        return;
    }

       //情况语句
    if( symid == SWITCHTK){
        casesentence();
        cout<<"This is a switch sentence!"<<endl;
        return;
    }

    //'{'语句列'}'
    if ( symid == LBBRASY ) {
        getsym();
        sentencelist();
        //缺“}”
        if ( symid != RBBRASY ) {
                error(RIGHTBRACELACK, 1);
            cout<<"RBBRALACK"<<endl;
            return;
        }
        //不缺“}”
        getsym();
        cout<<"This is a sentence list!"<<endl;
        return;
    }

    //函数调用语句｜＜赋值语句＞;

    if ( symid == IDEN ) {
        int isVec = 0;
        char names[ MAXIDENLEN ];
        strcpy(names, markstr.c_str());
        char place2[ 100 ];

        getsym();
        //＜赋值语句＞;
        //＜赋值语句＞   ::=  ＜标识符＞＝＜表达式＞   |    ＜标识符＞'['<表达式>']'＝＜表达式＞

        if ( symid == LMBRASY ){ //如果是数组
            /*
            s = searchst(names, 0);
            if ( s == -1 )
            {
           //     error(VARNOTDEFINE, 0);
      //          return;
            }
*/
            getsym();
            expression();
            strcpy(place2, exprevalue);
            //数组越界检查？？？？？数组区分char类型数组和int类型数组检查？？？？

            if (isdigit(exprevalue[0])){
                int arrnums = 0;
                arrnums = arrnum(names);
                if (atoi(exprevalue) >= arrnums){
                    printf("Warning: Line:%d index of array out of boundary, which should be less than %d.\n",linenum, atoi(exprevalue));
                    error(ARRAYOUTBOUND);
                }
            }

            isVec = 1;
            if ( symid != RMBRASY ) {
                    error(RIGHTBRACKLACK, 1);
                cout<<"RMBRALACK"<<endl;
                return;
            }
            getsym();

        }
        if ( symid == ASSIGNSY ) {


            s = searchst(names, 0);
            if ( s < 0 ) {     //如果是常量
              //  error(ASSIGNCONST);            //"="左边是不合法的标识符

             //   return;
            }
            int pretk = searchkind(names,0);
            if( maintable.element[s].kind == CINTET || maintable.element[s].kind == CCHARET ){
                error(ASSIGNCONST);            //"="左边是不合法的标识符
                cout<< "CONST CANNOT ASSIGN" <<endl;
                return;
            }


            getsym();
            expression();


            if(termtk == INTTK && pretk == CHARTK){
                error(TYPECHANGE);
                cout<< "WARNING:INT CANNOT ASSIGH TO CHAR!!!" << endl;
   //             return;
            }


            if ( isVec ){
                fourvarcode("[]=", names, place2, exprevalue);
            }
            else{
                fourvarcode("=", exprevalue, "  ", names);
            }


            if ( symid != SEMICOLONSY ) {
                     error(SEMICOLONLACK, 2);
                cout<<"SEMICOLONLACK"<<endl;
                return;
            }
            getsym();
            cout<<"This is a assign sentence!"<<endl;
            return;
        }

        //函数调用语句
        if ( symid == LSBRASY ) {
            getsym();
            valueofpara();  //计算并记录参数的值以及个数
            if ( symid != RSBRASY ) {
                    error(RIGHTPARENTLACK, 1);
                cout<<"RSBRALACK"<<endl;
                return;
            }

            //查函数表

            s = searchst(names, 1);
            if ( s <0 ) {
               // error(FUNCTIONNOTFOUND);
             //  cout<< markstr << " 33333333333333333333333333333333333333333333333333333333333333" <<endl;
     //           return;
            }
            else if ( s <0 ){
             //   error(FORMALPARANUMUNMATCH, 1);
     //           return;
            }
            fourvarcode("call", names, "  ", "  ");

            getsym();
            if ( symid != SEMICOLONSY ) {
                    error(SEMICOLONLACK, 2);
                cout<<"SEMICOLONLACK"<<endl;
                return;
            }
            getsym();
        }

        else {
                error(UNACCEPTABLESENTENCE);    //不合法的句子
            cout<<"SENTENCEERROR"<<endl;    //不合法的句子
            return;
        }
        cout<<"This is a function diaoyong sentence!"<<endl;
        return;
    }

    //读语句
    if ( symid == SCANFTK ) {
        scanfsentence();
        if ( symid != SEMICOLONSY ) {
                error(SEMICOLONLACK, 2);
            cout<<"SEMICOLONLACK"<<endl;
            return;
        }
        getsym();
        cout<<"This is a scanf sentence!"<<endl;
        return;
    }


    //写语句
    if ( symid == PRINTFTK ) {

        printfsentence();
        if ( symid != SEMICOLONSY ) {
                error(SEMICOLONLACK, 2);
                //cout<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<< endl;
            cout<<"SEMICOLONLACK"<<endl;
            return;
        }
        getsym();
        cout<<"This is a printf sentence!"<<endl;
        return;
    }

    //返回语句
    if ( symid == RETURNTK ) {
        returnsentence();
        //返回语句后缺“；”
        if ( symid != SEMICOLONSY ) {
                error(SEMICOLONLACK, 2);
            cout<<"SEMICOLONLACK"<<endl;
            return;
        }
        getsym();
        cout<<"This is a return sentence!"<<endl;
        return;
    }


    //空语句
    if ( symid == SEMICOLONSY )
    {
        getsym();
        cout<<"This is a null sentence!"<<endl;
        return;
    }

    //不合法的句子
    cout<<"SENTENCEERROR"<<endl;
    error(UNACCEPTABLESENTENCE);
    return;
}

//＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
void complexsentence()
{
    if ( symid == CONSTTK ) {
        //调用常量说明子程序
        conststate();
        cout<<"This is a const statement!"<<endl;
    }

    //判断是否为变量说明
    if( symid == INTTK || symid == CHARTK ){
        while( symid == INTTK || symid == CHARTK )
            varstate();
        cout<<"This is a variable statement!"<<endl;
    }

    //语句列
    sentencelist();
    return;
}

//＜程序＞    ::= ［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
void program(){
   // getsym();

    if ( symid == CONSTTK ) {
        //调用常量说明子程序
        conststate();
        //如果是分号,则是正常的
        cout<<"This is a const statement!"<<endl;
    }

    int globvari=0;
    //变量定义和有返回值的函数是相同的声明头部。因此预读3个单词用于判断
    while ( symid == INTTK || symid == CHARTK ) {

        int tempid = symid;//恢复现场用
        char tempch = ch;//恢复现场用
        int temppin = pin;//恢复现场用

        int kind = symid;
        getsym();

        strcpy(name, markstr.c_str());//拷贝名字


        //如果标识符合法
        if ( symid != IDEN ) {
            error(IDENTIFIERLACK);//notdone
            cout<<"IDENTIFIERLACK"<<endl;
            continue;
//////////////////////////////////////////////////////////continue??????
        }
        getsym();
        //如果是逗号,中括号,    分号，则是变量定义
        if ( symid == COMMASY || symid == LMBRASY || symid == SEMICOLONSY ) {
            symid = tempid;
            pin = temppin;
            ch = tempch;
            //回到INTTK和CHARTK处调用 变量声明函数
            varstate();
            globvari=1;
            continue;
        }

        else if( symid == LSBRASY ){
            symid = tempid;
            pin = temppin;
            ch = tempch;
            break;
        }
        else{
            error(DEFINEERROR);
            cout<<"STATEMENTERROR"<<endl;
            continue;
        }


    }
    if( globvari==1 )
        cout<<"This is a variable statement!"<<endl;

    /*
    if ( symid == CONSTTK ) {
        errnum++;
        printf("Error %d: Line %d, 常量定义位置错误！\n", errnum, lnum);
        conststate();
        //如果是分号,则是正常的
    }
    sislob = 0;
    */

    //函数定义部分头出错
    if( symid != INTTK && symid != CHARTK && symid != VOIDTK ){

        error(FUNCDEFINEERROR);
        cout<<"FUNCTIONDEFINEERROR"<<endl;

    }

    int ismain=0;
    globdefine = 0;

    while ( symid == INTTK || symid == CHARTK || symid == VOIDTK ) {

        int temp = symid;

        //＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’  ‘{’＜复合语句＞‘}’
        if ( symid == INTTK || symid == CHARTK ) {

            defhead();
            if ( symid != LSBRASY ) {
                error(LEFTPARENTLACK);//ICV
                cout<<"LSBRALACK"<<endl;
                continue;
            }

            varcnt = 0;         //临时变量重新开始计数
            returnnum = 0;      //将是否存在返回值的标记初始化，0表示无返回值，即未出现return
            kind = FUNCTION;    //表示当前的函数是子程序，即非主函数
            value = (symid== INTTK) ? 1 : 2;          //对于函数来说，1表示返回值为Int,0返回值为void
            address = 0;
            paranum = 0;
            pushtable(name, kind, value, address, paranum);
            strcpy(funcname, name);//函数名拷贝
            if ( temp == INTTK ) fourvarcode("func", "int", "  ", funcname);
            if ( temp == CHARTK ) fourvarcode("func", "char", "  ", funcname);


            getsym();
            parametertable();
            //缺'('＜参数＞')'的右小括号
            if ( symid != RSBRASY ){
                    cout<< "bbbbbbbbbbbb"<<endl;
                error(RIGHTPARENTLACK);//ICV
                cout<<"RSBRALACK"<<endl;
                continue;
            }
            getsym();
            //缺'{'＜复合语句＞'}'的左大括号
            if ( symid != LBBRASY ) {
                error(LEFTBRACELACK);//ICV
                cout<<"LBBRALACK"<<endl;
                continue;
            }
            getsym();
            complexsentence();
            //缺'{'＜复合语句＞'}'的右大括号
            if ( symid != RBBRASY ) {
                error(RIGHTBRACELACK);//ICV
                cout<<"RBBRALACK"<<endl;
                continue;
            }

            //函数缺少返回值
            if ( returnnum == 0 ) {
                error(NONERETURN);//ICV
                cout<<"RETURNVALUELACK"<<endl;
                continue;
            }

            cout<<"This is a return function statement!"<<endl;
            getsym();
            fourvarcode("end", "  ", "  ", funcname);//函数部分四元式结束
            popst();//清除符号表，这里清空的是此子函数的符号表,不清除子函数名

        }

        //＜无返回值函数定义＞ ::= void＜标识符＞‘(’＜参数＞‘)’‘{’＜复合语句＞‘}’
        if ( symid == VOIDTK ) {
            getsym();



            if ( symid != IDEN && symid !=MAINTK) {
                error(IDENTIFIERLACK);//ICV
                cout<<"IDENTIFIERLACK"<<endl;
                continue;
            }

            varcnt = 0;//临时变量重新开始计数


          //  getsym();
            if (symid == MAINTK){
                ismain=1;
                break;
            }

            strcpy(name, markstr.c_str());

            kind = FUNCTION;
            value = 0;
            address = 0;
            paranum = 0;
            pushtable(name, kind, value, address, paranum);
            strcpy(funcname, name);
            fourvarcode("func", "void", "  ", funcname);

            getsym();
            if ( symid != LSBRASY ) {
                error(LEFTPARENTLACK);//ICV
                cout<<"LSBRALACK"<<endl;
                continue;
            }
            getsym();
            parametertable();
            if ( symid != RSBRASY ) {
                    error(RIGHTPARENTLACK);//ICV
                cout<<"RSBRALACK"<<endl;
                continue;
            }
            getsym();
            if ( symid != LBBRASY ) {
                error(LEFTBRACELACK);//ICV
                cout<<"LBBRALACK"<<endl;
                continue;
            }
            getsym();
            complexsentence();
            if ( symid != RBBRASY ) {
                error(RIGHTBRACELACK);//ICV
                cout<<"RBBRALACK"<<endl;
                continue;
            }

            cout<<"This is a nonreturn function statement!"<<endl;
            getsym();

            fourvarcode("end", "  ", "  ", funcname);
            popst();

        }
    }


    if( symid == VOIDTK )
        getsym();

    //缺少main关键字
    if(symid != MAINTK){
        error(MAINLACK);
        cout<<"FUNCTIONDEFINEERROR"<<endl;
    }

    varcnt = 0;        //临时变量重新开始计数
    strcpy(name, "main");
    kind = FUNCTION;
    value = 0;
    address = 0;
    paranum = 0;
    pushtable(name, kind, value, address, paranum);
    strcpy(funcname, name);
    fourvarcode("func", "  ", "  ", funcname);

    //void main(
    getsym();
    if ( symid != LSBRASY ) {
            error(LEFTPARENTLACK);//ICV
        cout<<"LSBRALACK"<<endl;
        //continue;
    }
    //void main()


    getsym();
    if ( symid != RSBRASY ) {
             error(RIGHTPARENTLACK);//ICV
        cout<<"RSBRALACK"<<endl;
        //continue;
    }

    //void main(){
    getsym();
    if ( symid != LBBRASY ) {
            error(LEFTBRACELACK);//ICV
        cout<<"LBBRALACK"<<endl;
        //continue;
    }

    getsym();
    complexsentence();

    fourvarcode("end", "  ", "  ", funcname);

    if ( symid != RBBRASY ) {
            error(RIGHTBRACELACK);//ICV
        cout<<"RBBRALACK"<<endl;
        //continue;
    }

    cout<<"This is a main function!"<<endl;
    cout<<"This is the program!"<<endl;
    return;


}


//＜参数＞     ::=    ＜参数表＞
//＜参数表＞    ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
void parametertable()
{
    int i = 0;     //记录参数个数
    int temp;
    int tparakind[MAXPARANUM];
    if ( symid == INTTK || symid == CHARTK ) {
        do{
            if ( symid == COMMASY )
                getsym();
            temp = symid;
            defhead();    //函数参数和声明头部时完全相同？？？？？？？？？？？？？？？？？？

            kind = (temp == INTTK) ? PARAINT : PARACHAR ;     //4表示为函数参数
            value = 0;
            address = i;  //地址为i，即参数的位置，地址全部为相对地址？
            paranum = 0;
            pushtable(name, kind, value, address, paranum);  //将行数参数插入符号表

            if ( temp == INTTK ) {
                fourvarcode("para", "int", "  ", name);
                tparakind[i]=INTTK;
            }
            else if ( temp == CHARTK ){
                fourvarcode("para", "char", "  ", name);
                tparakind[i]=CHARTK;
            }
            i++;//参数个数加一
        } while ( symid == COMMASY );//如果是逗号，则还有其他的参数

        paranum = i;//当前的参数个数
        updatepara(paranum,tparakind);//插入函数的参数个数


    }

    else if (symid == RSBRASY){
        return;
    }

    else{
            error(RIGHTPARENTLACK);//ICV
        cout<<"PARAERROR"<<endl;
    }
/*
    for(int i=0;i<maintable.index;i++){
        cout<<maintable.element[i].kind<<"  "<<maintable.element[i].name<<"  "<<maintable.element[i].value<<endl;
    }

*/
    return;
}



 //正负0问题！！！！！！！！！！！！！！！！！！！！！！！！！！
