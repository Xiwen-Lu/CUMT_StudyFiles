%{
#include <stdio.h> 
#define LT				1
#define	LE				2
#define GT				3
#define	GE				4
#define	EQ				5
#define NE				6
#define ID				20
#define NUMBER				21
#define RELOP				22
#define MAIN                    44
#define INT                     45
#define FLOAT                   46
#define RETURN                  48
#define CONST                   49
#define WS                       51
#define INCLUDE                   59
#define NEWLINE				23
#define OTHER			24
#define STRING				26

int yylval;
int column=0;
int row=0;
%}

delim			[ \t \n]
ws			{delim}+
letter			[A-Za-z_]
schar			\'(\\.|[^"\\])\'
string			\"(\\.|[^"\\])*\"
digit			[0-9]
H			[a-fA-F0-9]
id			({letter}|\_)(\_|{letter}|{digit})*
number	{digit}+(\.{digit}+)?([eE][+-]?{digit}+)?([uUlL]|([uU][lL])|([lL][uU]))?

%%
{ws}	          {return WS;}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"	{;}
"/""/"[^\n]*				{;}

main                    {yylval=MAIN;return(MAIN);}
int                     {yylval=INT;return(INT);}
float                   {yylval=FLOAT;return(FLOAT);}
return                  {yylval=RETURN;return(RETURN);}
0[0-7]*			{yylval=NUMBER;return(NUMBER);}
0[xX]{H}+		{yylval=NUMBER;return(NUMBER);}
"#"include                   {yylval=INCLUDE;return(INCLUDE);}

{id}	          { return (ID);}
{number}	      { return (NUMBER);}
{string}		{return (STRING);}
"<<"		{return(RELOP);}
"<"	            {yylval = LT; return (RELOP);}
"<="	          {yylval = LE; return (RELOP);}
"="	            {yylval = EQ; return (RELOP);}
"<>"	          {yylval = NE; return (RELOP);}
">"	            {yylval = GT; return (RELOP);}
">="	          {yylval = GE; return (RELOP);}
"+"		{return(RELOP);}
"/"		{return(RELOP);}
"{"		{return(RELOP);}
"}"		{return(RELOP);}
";"		{return(RELOP);}
"("		{return(RELOP);}
")"		{return(RELOP);}
.		{yylval = OTHER; return OTHER;}

%%
int yywrap (){
  return 1;
}
void count(){
	int i;
	for(i=0;yytext[i]!='\0';++i){
		if(yytext[i]=='\n'){
			column=0;
			row++;
		}
		else if(yytext[i]=='\t')
			column+=8-(column%8);
		else
			column++;
	}
	
}
void writeout(int c){
  switch(c){
  	case OTHER: printf("   OTHER: %s", yytext);break;
	case RELOP: printf("   OTHER: %s", yytext);break;
	case NUMBER: printf("     NUM: %s", yytext);break;
	case ID:printf("      ID: %s", yytext);break;
	case NEWLINE:break;
	case STRING:printf("  STRING: %s",yytext);break;
	case MAIN:printf("    MAIN: %s",yytext);break;
	case INT:printf("     INT: %s",yytext);break;
	case FLOAT:printf("   FLOAT: %s",yytext);break;
	case RETURN:printf("  RETURN: %s",yytext);break;
	case WS:break;
	case INCLUDE:printf(" INCLUDE: %s",yytext);break;
	default:break;
  }
  if(c!=WS){
	if(yyleng<8)printf("\t");
	printf("\t\t row:%d \t column:%d \n",row,column);
  }
  count();
  return;
}
int main (int argc, char ** argv){
	int c=0;
	while (c = yylex()){
		writeout(c);
	}
	return 0;
}
int yyerror(char *s){
    fprintf(stderr,"%s\n",s);
    return 1;
}
