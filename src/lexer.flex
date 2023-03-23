%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

Text [^)]
Letter [A-Za-z]
Num [0-9]

%%

int             {  yylval.string=new std::string(yytext); return INT; }
return          { return RETURN; }

[(]             { return '('; }
[)]             { return ')'; }
[{]             { return '{'; }
[}]             { return '}'; }
[;]             { return ';'; }
[<]             { return '<'; }
[>]             { return '>'; }
"["             { return '['; }
"]"             { return ']'; }
"<="            { return GTE; }
">="            { return LTE; }
"=="            { return EQUAL; }
"!="            { return NOTEQUAL; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }
"++"            { return INCREMENT; }
"--"            { return DECREMENT; }
"+="            { return ADD_ASS; }
"-="            { return SUB_ASS; }
"!"             { return NOT; }

[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }
[,]             { return COMMA; }
[=]             { return '='; }
[\^]            { return '^'; }
[|]            { return '|'; }
[&]            { return '&'; }


({Num}+)([.]{Num}+)? { yylval.number=strtod(yytext, 0); return T_NUMBER;}

{Letter}+       { yylval.string=new std::string(yytext); return T_VARIABLE; }

[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
