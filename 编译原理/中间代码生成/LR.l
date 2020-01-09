%{
#include <stdlib.h>
#include <string.h>
void yyerror(char *);
#include "y.tab.h"
#include "node.h"
%}

letter			[A-Za-z_]
digit			[0-9]
id			({letter}|\_)(\_|{letter}|{digit})*

%%

while		{return WHILE;}
main		return MAIN;
{id}		{fill_ID(&yylval,yytext);return ID;}

"<="	          {return RELOP1;}
">="	          {return (RELOP2);}
[0-9]+       { fill_NUM(&yylval,yytext); return NUMBER; }
[-+*/\n(){}=;]     return *yytext;
[ \t\n]         ;/* 去除空格 */
.            yyerror("无效字符");
%%

int fill_ID(node *dst,char *yytext){
	strcpy(dst->text,yytext);
	
	//dst->text=yytext;
	//printf("%s\t%s\n",yytext,dst->text);
	return 0;
}

int fill_NUM(node *dst,char *yytext){
	dst->a=atoi(yytext);
	return 0;
}

int yywrap(void) {
  return 1;
}
