%{
#include <stdlib.h>
#include <stdio.h>
int yylex(void);
void yyerror(char *);
int xvhao=0;

void print_xvhao(){printf("%d:\t",++xvhao);}

%}
%token ID NUMBER RELOP1 RELOP2 WHILE MAIN
%left '+' '-'	//规定左结合与优先级
%left '*' '/'
%left '{' '}' '(' ')' '=' ';'
%%
program:
program MAIN block '\n' {print_xvhao();printf("program -> main block \n");printf("分析结束。\n-------------------\n");xvhao=0; }
|
; 

block:
'{' stmts '}'  {print_xvhao();printf("block -> { stmts }\n");}
;

stmts:
stmt stmts  {print_xvhao();printf("stmts -> stmt stmts\n");}
|
;

stmt:
ID '=' E ';'	 {print_xvhao();printf("stmt -> ID = E\n");}
| WHILE '(' bool ')' stmt  {print_xvhao();printf("stmt -> while(bool) stmt\n");}
| block			{print_xvhao();printf("stmt -> block\n");}
;

E:
E '+' F  {print_xvhao();printf("E -> E + F\n");}
|F	{print_xvhao();printf("E-> F\n");}
; 

F:
F '*' G  {print_xvhao();printf("F -> F * G\n");}
| G		{print_xvhao();printf("F -> G\n");}
;

G:
'(' E ')'  {print_xvhao();printf("G -> (E)\n");}
| T		{print_xvhao();printf("G -> T\n");}
;

bool:
T RELOP1 T	{print_xvhao();printf("bool -> T<=T\n");}
| T RELOP2 T	{print_xvhao();printf("bool -> T>=T\n");}
| T		{print_xvhao();printf("bool -> T\n");}
;

T:
ID		{print_xvhao();printf("T -> ID \n");}
| NUMBER	{print_xvhao();printf("T -> NUM: %d \n",$1);}
;

%%

int main(void) {
  yyparse();
  system("pause");
  return 0;
}

void yyerror(char *s) {
  printf("语法分析错误，%s\n", s);
}
