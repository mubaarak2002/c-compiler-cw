#include <reg_name.h>

std::string reg_name(int num){
    switch (num){
        case 0: return "zero"; break;
        case 1: return "ra"; break;
        case 2: return "sp"; break;
        case 3: return "gp"; break;
        case 4: return "tp"; break;
        case 5: return "t0"; break;
        case 6: return "t1"; break;
        case 7: return "t2"; break;
        case 8: return "s0"; break;
        case 9: return "s1"; break;
        case 10: return "a0"; break;
        case 11; return "a1"; break;
        case 12: return "a2"; break;
        case 13: return "a3"; break;
        case 14: return "a4"; break;
        case 15: return "a5"; break;
        case 16: return "a6"; break;
        case 17: return "a7"; break;
        case 18: return "s2"; break;
        case 19: return "s3"; break;
        case 20: return "s4"; break;
        case 21: return "s5"; break;
        case 22: return "s6"; break;
        case 23: return "s7"; break;
        case 24: return "s8"; break;
        case 25: return "s9"; break;
        case 26: return "s10"; break;
        case 27: return "s11"; break;
        case 28: return "t3"; break;
        case 29: return "t4"; break;
        case 30: return "t5"; break;
        case 31: return "t6"; break;
        default: return "zero";
    }

}
