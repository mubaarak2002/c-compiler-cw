#include "reg_name.h"

std::string reg_name(double num){
    switch (int(num)){
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
        case 11: return "a1"; break;
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
        // floating point registers
        case 32: return "ft0"; break;
        case 33: return "ft1"; break;
        case 34: return "ft2"; break;
        case 35: return "ft3"; break;
        case 36: return "ft4"; break;
        case 37: return "ft5"; break;
        case 38: return "ft6"; break;
        case 39: return "ft7"; break;
        case 40: return "fs0"; break;
        case 41: return "fs1"; break;
        case 42: return "fa0"; break;
        case 43: return "fa1"; break;
        case 44: return "fa2"; break;
        case 45: return "fa3"; break;
        case 46: return "fa4"; break;
        case 47: return "fa5"; break;
        case 48: return "fa6"; break;
        case 49: return "fa7"; break;
        case 50: return "fs2"; break;
        case 51: return "fs3"; break;
        case 52: return "fs4"; break;
        case 53: return "fs5"; break;
        case 54: return "fs6"; break;
        case 55: return "fs7"; break;
        case 56: return "fs8"; break;
        case 57: return "fs9"; break;
        case 58: return "fs10"; break;
        case 59: return "fs11"; break;
        case 60: return "ft8"; break;
        case 61: return "ft9"; break;
        case 62: return "ft10"; break;
        case 63: return "ft11"; break;
        default: return "zero";
    }

}
