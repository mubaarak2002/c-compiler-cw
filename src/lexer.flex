%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "lexer.hpp"


// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */
%}
Text [^)]
Letter [A-Za-z]
Num [0-9]

%%

[-]?({Num}+)([.]{Num}+)? {printf("Number:      %s\n", yytext); yylval.numberValue = strtod(yytext, NULL); return Number;}
\({Text}*\) {printf("In brackets: %s\n", yytext); return Word; std::string text(yytext); text = text.substr(1, text.size() - 2); yylval.wordValue = new std::string(text); return Word;}



"while" {printf("Syntax:      %s\n", yytext); return Syntax;}
"for" {printf("Syntax:      %s\n", yytext); return Syntax;}
"if" {printf("Syntax:      %s\n", yytext); return Syntax;}
"else" {printf("Syntax:      %s\n", yytext); return Syntax;}
"return" {printf("Syntax:      %s\n", yytext); return Syntax;}

"int" {printf("Type:      %s\n", yytext); yylval.wordValue = new std::string(yytext); return Type;}
"char" {printf("Type:      %s\n", yytext); yylval.wordValue = new std::string(yytext); return Type;}
"unsigned" {printf("Type:      %s\n", yytext); yylval.wordValue = new std::string(yytext); return Type;}

{Letter}+ {printf("Word:        %s\n", yytext); return Word; yylval.wordValue = new std::string(yytext);}

[=] {printf("Operator:    %s\n", yytext); yylval.wordValue = new std::string(yytext); return Operator;}
[+] {printf("Operator:    %s\n", yytext); yylval.wordValue = new std::string(yytext); return Operator;}
[-] {printf("Operator:    %s\n", yytext); yylval.wordValue = new std::string(yytext); return Operator;}
[/] {printf("Operator:    %s\n", yytext); yylval.wordValue = new std::string(yytext); return Operator;}
[*] {printf("Operator:    %s\n", yytext); yylval.wordValue = new std::string(yytext); return Operator;}



\n { fprintf(stderr, "Newline\n"); }
[ ] {}
.	 {printf("Unknown:                        %s\n", yytext);}

%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
