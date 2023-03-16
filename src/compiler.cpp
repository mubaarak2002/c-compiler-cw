#include <fstream>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <unordered_map>

#include "ast.hpp"

#include "cli.h"
#include "reg_name.h"

typedef std::map<double,std::string> histogram_type;
typedef int extra_int;
extra_int extra;

void compile(std::ostream &w)
{
    const Expression *ast=parseAST();
    histogram_type bindings = {
        {0, "."},
        {1, "."},
        {2, "."},
        {3, "."},
        {4, "."},
        {5, "."},
        {6, "."},
        {7, "."},
        {8, "."},
        {9, "."},
        {10, "."},
        {11, "."},
        {12, "."},
        {13, "."},
        {14, "."},
        {15, "."},
        {16, "."},
        {17, "."},
        {18, "."},
        {19, "."},
        {20, "."},
        {21, "."},
        {22, "."},
        {23, "."},
        {24, "."},
        {25, "."},
        {26, "."},
        {27, "."},
        {28, "."},
        {29, "."},
        {30, "."},
        {31, "."}
    };

    // evaluate it
    double res=ast->evaluate(w, bindings, extra);

    w << ".text" << std::endl;
    w << ".globl f" << std::endl;
    w << std::endl;

    w << "f:" << std::endl;
    w << "addi  t0, zero, 0" << std::endl;
    w << "addi  t0, t0,   5" << std::endl;
    w << "add   a0, zero, t0" << std::endl;
    w << "ret" << std::endl;

}

// TODO: uncomment the below if you're using Flex/Bison.
extern FILE *yyin;

int main(int argc, char **argv)
{

    // Parse CLI arguments, to fetch the values of the source and output files.
    std::string sourcePath = "";
    std::string outputPath = "";
    if (parse_command_line_args(argc, argv, sourcePath, outputPath))
    {
        return 1;
    }

    // TODO: uncomment the below lines if you're using Flex/Bison.
    // This configures Flex to look at sourcePath instead of
    // reading from stdin.
    yyin = fopen(sourcePath.c_str(), "r");
    if (yyin == NULL)
    {
        perror("Could not open source file");
        return 1;
    }

    // Open the output file in truncation mode (to overwrite the contents)
    std::ofstream output;
    output.open(outputPath, std::ios::trunc);

    // Compile the input
    std::cout << "Compiling: " << sourcePath << std::endl;
    compile(output);
    std::cout << "Compiled to: " << outputPath << std::endl;

    output.close();
    return 0;
}
