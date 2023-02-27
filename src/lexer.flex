%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */
#include "histogram.hpp"


// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */
%}
Text [^]]
Letter [A-Za-z]
Num [0-9]

%%

[-]?({Num}+)([.]{Num}+)? {
   fprintf(stderr, "Number : %s\n", yytext); /* TODO: get value out of yytext and into yylval.numberValue */
   yylval.numberValue = strtod(yytext, NULL);
   return Number;
   }

({Letter}+) {
   fprintf(stderr, "Word: %s\n", yytext); /* TODO: get value out of yytext and into yylval.wordValue */
   yylval.wordValue = new std::string(yytext);
   return Word;
   }

\[{Text}*\] {
   fprintf(stderr, "Word in brackets: %s\n", yytext); /* TODO: get value out of yytext and into yylval.wordValue */
   std::string text(yytext);
   text = text.substr(1, text.size() - 2);
   yylval.wordValue = new std::string(text);
   return Word;
   }

\n              { fprintf(stderr, "Newline\n"); }

. {
   fprintf(stderr, "unknown : %s\n", yytext);
}
%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
