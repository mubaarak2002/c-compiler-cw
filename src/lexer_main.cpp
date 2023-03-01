#include "lexer.hpp"

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>

// Use a hash-table to maintain a word -> count mapping.
// This deliberately uses std::unordered_map rather than std::map,
// because we don't need to enumerate the entries in key order.
// This allows us to use a hash-table, so we get O(1) operations
// rather than O(log n).
typedef std::unordered_map<std::string,unsigned> lexer_type;


// Define the instance of the variable that is declared in the histogram.hpp header
TokenValue yylval;

int main()
{
    lexer_type lexer; // Create the hash-table instance

    while(1){
        TokenType type=(TokenType)yylex();

        if(type==None){
            break; // No more tokens

        }else if(type==Number){
            // We have a number. The value will be
            // in yylval.numberValue

            // TODO: add to sum
            //sum = sum + yylval.numberValue;
            //std::cerr << "sum: " << sum << std::endl;
        }else if(type==Word){
            // We have a string. The value is in a string
            // _pointed to_ by yylval.wordValue. Note that
            // the string is allocated by the lexer, but
            // deallocated by us.

            // TODO: add yylval.wordValue to histogram
            //histogram[*yylval.wordValue]++;

            // TODO: Free the pointer yylval.wordValue to stop leaks
            yylval.wordValue = NULL;
        }else if(type==Syntax){


        }else if(type==Operator){


        }else if(type==Type){


        }else{
            assert(0); // There are only three token types.
            return 1;
        }
    }
}
