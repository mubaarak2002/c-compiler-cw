#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
#include <bitset>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "reg_name.h"

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        double reg = 0;
        std::string empty = ".";
        if(extra == -1){ // sets the function arguments (10 - 17)
            for(double i = 10; i < 18; i++){
                if (bindings.at(i) == empty){
                    bindings.at(i) = id;
                    reg = i;
                    break;
                }
            }
        }
        else if(extra == -101){ // sets the float function arguments (42 - 49)
            for(double i = 42; i < 50; i++){
                if (bindings.at(i) == empty){
                    bindings.at(i) = id;
                    reg = i;
                    break;
                }
            }
        }
        else if(extra == -201){ // sets the float function arguments (74 - 81)
            for(double i = 74; i < 81; i++){
                if (bindings.at(i) == empty){
                    bindings.at(i) = id;
                    reg = i;
                    break;
                }
            }
        }
        else if(extra == -2){ // sets the int function label
            w << id << ":" << std::endl;
            return 0;
        }
        else if(extra == -102){ // sets the float function label
            w << id << ":" << std::endl;
            return 0;
        }
        else if(extra == -202){ // sets the double function label
            w << id << ":" << std::endl;
            return 0;
        }
        else if(extra == -3){ // call int function
            w << "j " << id << std::endl;
            return 0;
        }
        else if(extra == -103){ // call float function
            w << "j " << id << std::endl;
            return 0;
        }
        else if(extra == -203){ // call double function
            w << "j " << id << std::endl;
            return 0;
        }
        else{ // check if variable name already exists
            for(double i = 0; i <= 95; i++){
                if (bindings.at(i) == id){
                    reg = i;
                    break;
                }

            }
            if((extra <= -4) && (extra > -13)){ // call int function
            w << "add " << reg_name(6-extra) << ", " << reg_name(reg) << ", zero" <<  std::endl;
            }
            if (reg == 0.0){ // makes new variable in a saved register if doesnt already exist
                if(extra == -100){ // floats
                    for(double i = 50; i < 63; i++){
                        if (bindings.at(i) == empty){
                            bindings.at(i) = id;
                            reg = i;
                            break;
                        }
                    }
                }
                else if(extra == -200){ // doubles
                    for(double i = 82; i < 95; i++){
                        if (bindings.at(i) == empty){
                            bindings.at(i) = id;
                            reg = i;
                            break;
                        }
                    }
                }
                else{ // normal integers
                    if (bindings.at(8.0) == empty){ bindings.at(8.0) = id; reg = 8.0; }
                    else if (bindings.at(9.0) == empty){ bindings.at(9.0) = id; reg = 9.0; }
                    else if (reg == 0.0){
                        for(double i = 18; i < 28; i++){
                            if (bindings.at(i) == empty){
                                bindings.at(i) = id;
                                reg = i;
                                break;
                            }
                        }
                    }
                }
            }
        }

        // w << "registers full" << std::endl;
        //extend registers here if they are full
        return reg;

    }
};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    { // store number into temp registers
        std::string empty = ".";
        double reg = 0.0;
        if (extra == -100) { // floating point numbers

            float decimal = (float) value;
            union {
            float input;
            int output;
            } data;

            data.input = decimal;

            std::bitset<sizeof(float) * CHAR_BIT> bits(data.output);

            std::string bitstring = bits.to_string<char, std::char_traits<char>, std::allocator<char>>();
            w << "li " << reg_name(5) << ", 0b" << bitstring << std::endl;
            for(double i = 33; i < 42; i++){
                if (bindings.at(i) == empty){
                    bindings.at(i) = value;
                    reg = i;
                    break;
                }
            }
            w << "fmv.w.x " << reg_name(reg) << ", " << reg_name(5) << std::endl;
        }

        else if (extra == -200){ // double
            double decimal = (double) value;
            union {
            double input;
            uint64_t output;
            } data;

            data.input = decimal;

            std::bitset<sizeof(double) * CHAR_BIT> bits(data.output);

            std::string bitstring = bits.to_string<char, std::char_traits<char>, std::allocator<char>>();
            w << "li " << reg_name(5) << ", 0b" << bitstring << std::endl;
            for(double i = 33; i < 42; i++){
                if (bindings.at(i) == empty){
                    bindings.at(i) = value;
                    reg = i;
                    break;
                }
                w << "fmv.d.x " << reg_name(reg) << ", " << reg_name(5) << std::endl;
            }
        }
        else { // normal integers
            if((extra <= -4) && (extra > - 13)){
                w << "li " << reg_name(6-extra) << ", " << value << std::endl;
            }
            else{
                if (bindings.at(6.0) == empty){ bindings.at(6.0) = value; reg = 6.0;}
                else if (bindings.at(7.0) == empty){ bindings.at(7.0) = value; reg = 7.0;}
                else if (bindings.at(28.0) == empty){ bindings.at(28.0) = value; reg = 28.0;}
                else if (bindings.at(29.0) == empty){ bindings.at(29.0) = value; reg = 29.0;}
                else if (bindings.at(30.0) == empty){ bindings.at(30.0) = value; reg = 30.0;}
                else if (bindings.at(31.0) == empty){ bindings.at(31.0) = value; reg = 31.0;}
                w << "li " << reg_name(reg) << ", " << value << std::endl;
            }
        }
        return reg;
    }
};

class Type
    : public Expression
{
private:
    std::string id;
public:
    Type(const std::string &_id)
        : id(_id)
    {}

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        double type = 0;
        if(id == "int"){
            type = 0;
        }
        else if(id == "float"){
            type = -100;
        }
        else if(id == "double"){
            type = -200;
        }
        return type;
    }
};

class Return
    : public Expression
{
private:
    ExpressionPtr expr;
public:
    Return(const ExpressionPtr _expr)
        : expr(_expr)
    {}

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        double reg=getExpr()->evaluate(w, bindings, extra, funct);
        if(reg > 63){
            if (reg != 74){
                w << "fadd.d " << reg_name(74) << ", " << reg_name(reg) << ", " << reg_name(95) << std::endl;
            }
        }
        else if(reg > 31){
            if (reg != 42){
                w << "fadd.s " << reg_name(42) << ", " << reg_name(reg) << ", " << reg_name(63) << std::endl;
            }
        }
        else{
        if (reg != 10){
                w << "add " << reg_name(10) << ", " << reg_name(reg) << ", zero" << std::endl;
            }
        }
        w << "ret" << std::endl;
    }
};

class Increment
    : public Expression
{
private:
    ExpressionPtr expr;
public:
    Increment(const ExpressionPtr _expr)
        : expr(_expr)
    {}

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        double reg=getExpr()->evaluate(w, bindings, extra, funct);
        w << "addi " << reg_name(reg) << ", " << reg_name(reg) << ", 1" << std::endl;
    }
};

class Decrement
    : public Expression
{
private:
    ExpressionPtr expr;
public:
    Decrement(const ExpressionPtr _expr)
        : expr(_expr)
    {}

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        double reg=getExpr()->evaluate(w, bindings, extra, funct);
        w << "addi " << reg_name(reg) << ", " << reg_name(reg) << ", -1" << std::endl;
    }
};

class FunctCall
    : public Expression
{
private:
    ExpressionPtr expr;
public:
    FunctCall(const ExpressionPtr _expr)
        : expr(_expr)
    {}

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        int callFunct = -3;
        double expr=getExpr()->evaluate(w, bindings, callFunct, funct);
        return 10;
    }
};

class Empty
    : public Expression
{
private:
public:

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {

        //return bindings.at(id);
    }
};

class Break
    : public Expression
{
private:
public:

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        std::string EXIT = "EXIT_" + std::to_string(extra-1);
        w << "j " << EXIT << std::endl;
    }
};

class Continue
    : public Expression
{
private:
public:

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        std::string EXIT = "LOOP_" + std::to_string(extra-1);
        w << "j " << EXIT << std::endl;
    }
};

class EmptyArrayDecleration
    : public Expression
{
private:
    ExpressionPtr expr;
public:
    EmptyArrayDecleration(const ExpressionPtr _expr)
        : expr(_expr)
    {}

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        int arrname = -2;
        double expr=getExpr()->evaluate(w, bindings, arrname, funct);
        w << ".zero 4" << std::endl;

    }
};

#endif
