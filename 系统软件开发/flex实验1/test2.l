%{
    int wordCount = 0;
%}

chars [A-Za-z\_\'\.\"]
numbers ([0-9])+
delim [ \n\t]
whitespace {delim}+
words {chars}+

%%
{words} {wordCount++;printf("chars:%s\n",yytext);}
{delim} {printf("delim:%s\n",yytext);}
{whitespace} {printf("whitespace:%s\n",yytext);}
{numbers} {}
. {}
%%
void main()
{
    yylex();
    printf("No of words:%d\n", wordCount);
}
int yywrap()
{
	return 1;
}