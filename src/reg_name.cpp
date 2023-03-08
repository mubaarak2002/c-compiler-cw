#include <reg_name.h>

std::string reg_name(int num){
    switch (num){
        case 1: return "ra"; break;
        default: return "zero";
    }

}
