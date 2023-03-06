#include <fstream>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <unordered_map>

#include "ast.hpp"

#include "cli.h"

typedef std::unordered_map<std::string,std::string> histogram_type;

void compile(std::ostream &w)
{
    const Expression *ast=parseAST();

    histogram_type registers = {
        {"zero", "."},
        {"ra", "."},
        {"sp", "."},
        {"gp", "."},
        {"tp", "."},
        {"t0", "."},
        {"t1", "."},
        {"t2", "."},
        {"s0", "."},
        {"s1", "."},
        {"a0", "."},
        {"a1", "."},
        {"a2", "."},
        {"a3", "."},
        {"a4", "."},
        {"a5", "."},
        {"a6", "."},
        {"a7", "."},
        {"s2", "."},
        {"s3", "."},
        {"s4", "."},
        {"s5", "."},
        {"s6", "."},
        {"s7", "."},
        {"s8", "."},
        {"s9", "."},
        {"s10", "."},
        {"s11", "."},
        {"t3", "."},
        {"t4", "."},
        {"t5", "."},
        {"t6", "."}
    };


    // evaluate it
    std::map<std::string,double> bindings;
    double res=ast->evaluate(w, bindings);

    w << ".text" << std::endl;
    w << ".globl f" << std::endl;
    w << std::endl;

    w << "f:" << std::endl;
    w << "addi  t0, zero, 0" << std::endl;
    w << "addi  t0, t0,   5" << std::endl;
    w << "add   a0, zero, t0" << std::endl;
    w << "ret" << std::endl;

    w << registers["a0"] << std::endl;
    registers["a0"] = "var";
    w << registers["a0"] << std::endl;

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
