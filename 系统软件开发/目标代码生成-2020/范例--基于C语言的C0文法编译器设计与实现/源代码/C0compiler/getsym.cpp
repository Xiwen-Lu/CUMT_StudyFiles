//
//  getsym.cpp
//  Compiler
//
//  Created by Yang Hu on 2017/11/28.
//  Copyright © 2017年 Yang Hu. All rights reserved.
//
#include <cstdlib>
#include <string.h>

#include <iostream>
#include <fstream>

#include "global.h"


using namespace std;

string  key[14]={"main","int","char","const","void",
    "if","else","switch","case","default",
    "for","printf","scanf","return"};

string keyType[14]={"MAINTK","INTTK","CHARTK","CONSTTK","VOIDTK",
    "IFTK","ELSETK","SWITCHTK","CASETK","DEFAULTTK",
    "FORTK","PRINTFTK","SCANFTK","RETURNTK"};

string  symbol[20]={
    "=","+","-","*","/",
    "<","<=",">",">=","!=",
    "==","(",")","[","]",
    "{","}",",",":",";" };

string symbolType[20]={
    "ASSIGNSY","PLUSSY","SUBSY","MULTSY","DIVSY",
    "LESSY","LESEQSY","GRTSY","GRTEQSY","NEQUALSY",
    "EQUALSY","LSBRASY","RSBRASY","LMBRASY","RMBRASY",
    "LBBRASY","RBBRASY","COMMASY","COLONSY","SEMICOLONSY"};

char ch=' ';           ///存放最新读进的源程序字符
string strToken;       ///存放构成单词的字符串

int k=0;

string markstr;  //记录全局变量标识符

//char markstr [MAXIDENLEN];

int num=0;          //记录全局变量数字
string stret="";          //记录全局变量 字符，字符串

int linenum = 1;


string sym="";
int symid=0;

void GetChar()    ///---------1
{
    ch= text[pin];
    pin++;
}

void GetFChar()     ///-------2
{
    while(1)
    {
        if(ch==' '||ch=='\t'||ch=='\n'){
            if( ch == '\n' )
                linenum++;
            GetChar();


        }
        else break;
    }
}


bool IsLetter()   ///---------4
{
    if( ( ch>='a' &&ch<='z') ||( ch>='A' &&ch<='Z')||ch=='_' )
        return true;
    return false;
}

bool IsDigit()   ///---------5
{
    if( ch>='0' &&ch<='9')
        return true;
    return false;
}

void Concat()   ///----------3
{
    strToken+=ch;
}

void Retract()   ///----------7
{
    ch=' ';
    pin--;
}

int Reserve()    ///---------6
{
    for(int i=0;i<14;i++)
    {
        if(strToken==key[i])  return i;
    }
    return -1;
}

int FindInSymbol(string str)    ///---------8
{
    for(int i=0;i<20;i++)
    {
        if(str==symbol[i])  return i;
    }
    return -1;
}

void getsym(){

    int code;
    strToken="";
    GetChar();
    GetFChar();

    //  cout<<ch<<" []"<<endl;
    {
        //   GetChar();

        //识别标示符和关键字
        if(IsLetter()){

            while(IsLetter() || IsDigit())
            {
                Concat();
                GetChar();
            }
            Retract();
            code=Reserve();
            if(code!=-1)   ///识别出来的是关键字

            {
                sym=keyType[code];
                symid=code+1;
                cout<<++k<<" "+keyType[code]+" "<<strToken<<endl;
            }
            else            ///识别出来的是标示符
            {
                cout<<++k<<" IDENTIFIER "<<strToken<<endl;
                sym="IDEN";
                symid=IDEN;
                markstr = strToken;
                //strcpy(markstr,strToken);
            }


        }
        //无符号整数、0  型常量
        else if(IsDigit() && ch!= '0'){

            num=0;

            while ( IsDigit() ){

                num = num * 10 + (int)( ch - '0' );
                Concat();
                GetChar();
            }

            Retract();
            cout<<++k<<" NUMET "<<strToken<<endl;
       //     cout<<"aaaa   "<<num<<endl;
            sym="NUMET";
            symid=NUMET;

        }
        else if(IsDigit() && ch== '0'){
            GetChar();
            //单个0
            if(!IsDigit()){
                cout<<++k<<" NUMET "<<0<<endl;
                sym="NUMET";
                symid=NUMET;
                num=0;

            }
            else
                cout<<"error0"<<endl;
            Retract();

        }
        //识别字符常量'\''
        else if(ch=='\''){
            Concat();
            GetChar();
            if(IsLetter()||IsDigit()||ch=='+'||ch=='-'||ch=='*'||ch=='/'){
                Concat();
                GetChar();
                if(ch=='\'')
                    Concat();
                else{
                    cout<<"SINGLEQUOTESLACK"<<endl;
                    error(SINGLEQUOTESLACK);
                    //exit(1);
                }
                cout<<++k<<" CHARET "<<strToken<<endl; //输出信息
                sym="CHARET";
                symid=CHARET;

                stret=strToken;

            }
            else{
                error(UNACCEPTATLECHAR);
                cout<<"UNACCEPTATLECHAR"<<endl;
                exit(1);
            }
        }


        //识别字符串常量
        else if(ch=='\"'){
            Concat();
            GetChar();

            while(ch!='"')
            {
                if(ch==32||ch==33||(ch>=35&&ch<=126)){
                    Concat();
                    GetChar();
                }
                else{
                    error(DOUBLEQUOTESLACK);
                   // exit(1);
                }
            }
            Concat();
            cout<<++k<<" STRINGET "<<strToken<<endl;

            stret=strToken;

            sym="STRINGET";
            symid=STRINGET;
        }

        //识别=、==
        else if(ch=='=')
        {
            Concat();
            GetChar();
            int code;
            //==
            if(ch=='=')
            {
                Concat();
                code=FindInSymbol(strToken);
                cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
                sym="EQUALSY";
                symid=EQUALSY;
            }
            //=
            else
            {
                code=FindInSymbol(strToken);
                cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
                sym="ASSIGNSY";
                symid=ASSIGNSY;
                Retract();
            }
        }
        ///<,<=
        else if(ch=='<')
        {
            Concat();
            GetChar();
            int code;
            ///<=
            if(ch=='=')
            {
                Concat();
                code=FindInSymbol(strToken);
                cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
                sym="LESEQSY";
                symid=LESEQSY;
            }
            ///<
            else
            {
                code=FindInSymbol(strToken);
                cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
                sym="LESSY";
                symid=LESSY;
                Retract();
            }
        }
        //>,>=
        else if(ch=='>')
        {
            Concat();
            GetChar();
            int code;
            //>=
            if(ch=='=')
            {
                Concat();
                code=FindInSymbol(strToken);
                cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
                symid=GRTEQSY;
                sym="GRTEQSY";
            }
            //>
            else
            {
                code=FindInSymbol(strToken);
                cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
                symid=GRTSY;
                sym="GRTSY";
                Retract();
            }
        }
        //!=
        else if(ch=='!')
        {
            Concat();
            GetChar();
            int code;
            //!=
            if(ch=='=')
            {
                Concat();
                code=FindInSymbol(strToken);
                cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
                symid=NEQUALSY;
                sym="NEQUALSY";
            }
            else
            {
                cout<<"error4"<<endl;
                exit(1);
            }
        }

        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('
                ||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']'
                ||ch==';'||ch==':'||ch==',')
        {
            int code;
            Concat();
            code=FindInSymbol(strToken);
            cout<<++k<<" "+symbolType[code]+" "<<strToken<<endl;
            symid=code+15;
            sym=symbolType[code];
        }
        else if(ch == '\0'){
   //         cout<<"lexi over"<<endl;
            symid = -1;
            return;
        }
        else
        {
            cout<<"error5"<<endl;
            error(UNEXPECTEDCHAR);

           // exit(1);
        }

    }

}

