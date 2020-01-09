%{
#include <stdio.h> 
#define LT				1
#define	LE				2
#define GT				3
#define	GE				4
#define	EQ				5
#define NE				6

#define WHILE				18
#define	DO				19
#define ID				20
#define NUMBER				21
#define RELOP				22
#define IF                      40
#define ELSE                    41

#define MAIN                    44
#define INT                     45
#define FLOAT                   46
#define DOUBLE                  47
#define RETURN                  48
#define CONST                   49
#define VOID                    50
#define CONTINUE                        51
#define BREAK                   52
#define CHAR                    53
#define UNSIGNED                        54
#define ENUM                    55
#define LONG                    56
#define SWITCH                  57
#define CASE                    58
#define AUTO                    59
#define STATIC                  60

#define NEWLINE				23
#define ERRORCHAR			24

#define SCHAR				25
#define STRING				26

int yylval;
%}

/* 这里进行正规定义和状态定义。
 * 下面就是正规定义，注意，正规定义和状态定义都要顶着行首写。
 */
 
delim			[ \t \n]
/* \用来表示转义，例如\t表示制表符，\n表示换行符。*/
ws			{delim}+
letter			[A-Za-z_]

schar			\'(\\.|[^"\\])\'
string			\"(\\.|[^"\\])*\"
digit			[0-9]
id			({letter}|\_)(\_|{letter}|{digit})*
/* 注意：上面正规定义中出现的小括号表示分组，而不是被匹配的字符。
 *       而大括号括起的部分表示正规定义名。
 */
number	{digit}+(\.{digit}+)?([eE][+-]?{digit}+)?([uUlL]|([uU][lL])|([lL][uU]))?



/* %%作为lex文件三个部分的分割符，必须位于行首 */
/* 下面这个%%不能省略 */
%%

  /* 第二部分是翻译规则部分。 */
  /* 写在这一部分的注释要有前导空格，否则lex编译出错。*/
  /* 翻译规则的形式是：正规式  {动作}
   * 其中，正规式要顶行首写，动作要以C语法写（动作会被拷贝到yylex()函数中，），\
   * 正规式和动作之间要用空白分割。
   */
  
{ws}	          {;/* 此时词法分析器没有动作，也不返回，而是继续分析。 */}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"	{;}
"/""/"[^\n]*				{;}
  /* 正规式部分用大括号扩住的表示正规定义名，例如{ws}。
   * 没有扩住的直接表示正规式本身。
   * 一些元字符没办法表示它本身，此时可以用转义字符或用双引号括起来，例如"<"
   * lex有顺序优先级，关键字应该放在id前面
   */
while	          {return (WHILE);}
do		          {return (DO);}
if                      {yylval=IF;return(IF);}
else                    {yylval=ELSE;return(ELSE);}
main                    {yylval=MAIN;return(MAIN);}
int                     {yylval=INT;return(INT);}
float                   {yylval=FLOAT;return(FLOAT);}
double                  {yylval=DOUBLE;return(DOUBLE);}
return                  {yylval=RETURN;return(RETURN);}
const                   {yylval=CONST;return(CONST);}
void                    {yylval=VOID;return(VOID);}
continue                        {yylval=CONTINUE;return(CONTINUE);}
break                   {yylval=BREAK;return(BREAK);}
char                    {yylval=CHAR;return(CHAR);}
unsigned                        {yylval=UNSIGNED;return(UNSIGNED);}
enum                    {yylval=ENUM;return(ENUM);}
long                    {yylval=LONG;return(LONG);}
switch                  {yylval=SWITCH;return(SWITCH);}
case                    {yylval=CASE;return(CASE);}
auto                    {yylval=AUTO;return(AUTO);}
static                  {yylval=STATIC;return(STATIC);}

{id}	          {yylval = installID (); return (ID);}

{number}	      {yylval = installNum (); return (NUMBER);}
{schar}			{return (SCHAR);}
{string}		{return (STRING);}
"<"	            {yylval = LT; return (RELOP);}
"<="	          {yylval = LE; return (RELOP);}
"="	            {yylval = EQ; return (RELOP);}
"<>"	          {yylval = NE; return (RELOP);}
">"	            {yylval = GT; return (RELOP);}
">="	          {yylval = GE; return (RELOP);}
"+"		{return(RELOP);}
"++"		{return(RELOP);}
"--"		{return(RELOP);}
"-"		{return(RELOP);}
"*"		{return(RELOP);}
"/"		{return(RELOP);}
"{"		{return(RELOP);}
"}"		{return(RELOP);}
";"		{return(RELOP);}
"("		{return(RELOP);}
")"		{return(RELOP);}
"=="		{return(RELOP);}
"!="		{return(RELOP);}
"&&"		{return(RELOP);}
"||"		{return(RELOP);}
"#"		{return(RELOP);}

.						{yylval = ERRORCHAR; return ERRORCHAR;}
 /*.匹配除换行之外的任何字符，一般可作为最后一条翻译规则。*/
 
%%
int installID () {
  /* 把词法单元装入符号表并返回指针。*/
	return ID;
}

int installNum () {
	/* 类似上面的过程，但词法单元不是标识符而是数 */
  return NUMBER;
}

int yywrap (){
  return 1;
}

void writeout(int c){
  switch(c){
  	case ERRORCHAR: fprintf(yyout, "(ERRORCHAR, \"%s\") ", yytext);break;
	case RELOP: fprintf(yyout, "(RELOP, \"%s\") ", yytext);break;  	  
	case WHILE: fprintf(yyout, "(WHILE, \"%s\") ", yytext);break;
	case DO: fprintf(yyout, "(DO, \"%s\") ", yytext);break;
	case NUMBER: fprintf(yyout, "(NUM, \"%s\") ", yytext);break;
	case ID: fprintf(yyout, "(ID, \"%s\") ", yytext);break;
	case NEWLINE: fprintf(yyout, "\n");break;
	case SCHAR:fprintf(yyout,"(CHAR,%s)",yytext);break;
	case STRING:fprintf(yyout,"(STRING,%s)",yytext);break;
	case IF:fprintf(yyout,"(IF,\"%s\")",yytext);break;
	case ELSE:fprintf(yyout,"(ELSE,\"%s\")",yytext);break;
	case MAIN:fprintf(yyout,"(MAIN,\"%s\")",yytext);break;
	case INT:fprintf(yyout,"(INT,\"%s\")",yytext);break;
	case FLOAT:fprintf(yyout,"(FLOAT,\"%s\")",yytext);break;
	case DOUBLE:fprintf(yyout,"(DOUBLE,\"%s\")",yytext);break;
	case RETURN:fprintf(yyout,"(RETURN,\"%s\")",yytext);break;
	case CONST:fprintf(yyout,"(CONST,\"%s\")",yytext);break;
	case VOID:fprintf(yyout,"(VOID,\"%s\")",yytext);break;
	case CONTINUE:fprintf(yyout,"(CONTINUE,\"%s\")",yytext);break;
	case BREAK:fprintf(yyout,"(BREAK,\"%s\")",yytext);break;
	case CHAR:fprintf(yyout,"(CHAR,\"%s\")",yytext);break;
	case UNSIGNED:fprintf(yyout,"(UNSIGNED,\"%s\")",yytext);break;
	case ENUM:fprintf(yyout,"(ENUM,\"%s\")",yytext);break;
	case LONG:fprintf(yyout,"(LONG,\"%s\")",yytext);break;
	case SWITCH:fprintf(yyout,"(SWITCH,\"%s\")",yytext);break;
	case CASE:fprintf(yyout,"(CASE,\"%s\")",yytext);break;
	case AUTO:fprintf(yyout,"(AUTO,\"%s\")",yytext);break;
	case STATIC:fprintf(yyout,"(STATIC,\"%s\")",yytext);break;
	default:break;
  }
  return;
}

/* 辅助函数里可以使用yytext和yyleng这些外部定义的变量。
 * yytext指向输入缓冲区当前词法单元(lexeme)的第一个字符，
 * yyleng给出该词法单元的长度		*/

/* 如果你的词法分析器并不是作为语法分析器的子程序，
 * 而是有自己的输入输出，你可以在这里定义你的词法
 * 分析器的main函数，main函数里可以调用yylex()
 */

int main (int argc, char ** argv){
	int c,j=0;
	if (argc>=2){
	  if ((yyin = fopen(argv[1], "r")) == NULL){
	    printf("Can't open file %s\n", argv[1]);
	    return 1;
	  }
	  if (argc>=3){
	    yyout=fopen(argv[2], "w");
	  }
	}
	/* yyin和yyout是lex中定义的输入输出文件指针，它们指明了
	 * lex生成的词法分析器从哪里获得输入和输出到哪里。
	 * 默认：键盘输入，屏幕输出。 
	 */
	while (c = yylex()){
		writeout(c);
		j++;
		if (j%5 == 0) writeout(NEWLINE);
	}
	if(argc>=2){
	  fclose(yyin);
	  if (argc>=3) fclose(yyout);
	}
	return 0;
}

int yyerror(char *s){
    fprintf(stderr,"%s\n",s);
    return 1;
}
