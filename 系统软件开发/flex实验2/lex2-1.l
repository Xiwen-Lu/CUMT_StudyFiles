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

#define INCLUDE                   59
#define STATIC                  60

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
id			({letter}|\_)(\_|{letter}|{digit})*
number	{digit}+(\.{digit}+)?([eE][+-]?{digit}+)?([uUlL]|([uU][lL])|([lL][uU]))?

%%

{ws}	          {;}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"	{;}
"/""/"[^\n]*				{;}

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
"#"include                   {yylval=INCLUDE;return(INCLUDE);}
static                  {yylval=STATIC;return(STATIC);}

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

.		{yylval = OTHER; return OTHER;}
 
%%

int yywrap (){
  return 1;
}

void writeout(int c){
  switch(c){
  	case OTHER: printf("   OTHER: %s", yytext);break;
	case RELOP: printf("   OTHER: %s", yytext);break;
	case WHILE: fprintf(yyout, "(WHILE, \"%s\") ", yytext);break;
	case DO: fprintf(yyout, "(DO, \"%s\") ", yytext);break;
	case NUMBER: printf("     NUM: %s", yytext);break;
	case ID:printf("      ID: %s", yytext);break;
	case NEWLINE: fprintf(yyout, "\n");break;

	case STRING:printf("  STRING: %s",yytext);break;
	case IF:fprintf(yyout,"(IF,\"%s\")",yytext);break;
	case ELSE:fprintf(yyout,"(ELSE,\"%s\")",yytext);break;
	case MAIN:printf("    MAIN: %s",yytext);break;
	case INT:printf("     INT: %s",yytext);break;
	case FLOAT:printf("   FLOAT: %s",yytext);break;
	case DOUBLE:fprintf(yyout,"(DOUBLE,\"%s\")",yytext);break;
	case RETURN:printf("  RETURN: %s",yytext);break;
	case CONST:fprintf(yyout,"(CONST,\"%s\")",yytext);break;
	case VOID:fprintf(yyout,"(VOID,\"%s\")",yytext);break;
	case CONTINUE:fprintf(yyout,"(CONTINUE,\"%s\")",yytext);break;
	case BREAK:fprintf(yyout,"(BREAK,\"%s\")",yytext);break;
	case CHAR:fprintf(yyout,"(CHAR,\"%s\")",yytext);break;
	case UNSIGNED:fprintf(yyout,"(UNSIGNED,\"%s\")",yytext);break;
	case ENUM:fprintf(yyout,"(ENUM,\"%s\")",yytext);break;
	case LONG:fprintf(yyout,"(LONG,\"%s\")",yytext);break;
	case INCLUDE:printf(" INCLUDE: %s",yytext);break;
	case STATIC:fprintf(yyout,"(STATIC,\"%s\")",yytext);break;
	default:printf("\t\t row:%n \t column:%n",row,column);break;
  }
  return;
}

int main (int argc, char ** argv){
	int c=0;
	while (c = yylex()){
		writeout(c);
		writeout(NEWLINE);
	}
	return 0;
}

int yyerror(char *s){
    fprintf(stderr,"%s\n",s);
    return 1;
}
