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
        int &extra
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
        else if(extra == -101){ // sets the float function arguments (32 - 39)
            for(double i = 32; i < 40; i++){
                if (bindings.at(i) == empty){
                    bindings.at(i) = id;
                    reg = i;
                    break;
                }
            }
        }
        else if(extra == -2){ // sets the function label
            w << id << ":" << std::endl;
        }
        else if(extra == -3){ // call function
            w << "j " << id << std::endl;
        }
        else{ // check if variable name already exists
            for(double i = 0; i <= 63; i++){
                if (bindings.at(i) == id){
                    reg = i;
                    break;
                }

            }
            if((extra <= -4) && (extra > -13)){ // call function
            w << "add " << reg_name(6-extra) << ", " << reg_name(reg) << ", zero" <<  std::endl;
            }
            if (reg == 0.0){ // makes new variable in a saved register if doesnt already exist
                if(extra == -100){ // checks if it is a float
                    for(double i = 40; i < 64; i++){
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
        int &extra
    ) const override
    { // store number into temp registers
        std::string empty = ".";
        double reg = 0.0;
        if (floor(value) != value) { // floating point numbers
            float decimal = (float) value;
            union {
            float input;
            int output;
            } data;

            data.input = decimal;

            std::bitset<sizeof(float) * CHAR_BIT> bits(data.output);

            std::string bitstring = bits.to_string<char, std::char_traits<char>, std::allocator<char>>();
            int float2int = std::strtol(bitstring.c_str(), NULL, 2);
            w << "li " << reg_name(5) << ", " << float2int << std::endl;
            for(double i = 61; i > 39; i--){
                if (bindings.at(i) == empty){
                    bindings.at(i) = value;
                    reg = i;
                    break;
                }
            }
            w << "fmv.wx " << reg_name(reg) << ", " << reg_name(5) << std::endl;
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
        int &extra
    ) const override
    {
        double type = 0;
        if(id == "int"){
            type = -1;
        }
        else if(id == "float"){
            type = -101;
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
        int &extra
    ) const override
    {
        double reg=getExpr()->evaluate(w, bindings, extra);
        if(reg > 31){
            if (reg != 32){
                w << "fadd.s " << reg_name(32) << ", " << reg_name(reg) << ", " << reg_name(62) << std::endl;
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
        int &extra
    ) const override
    {
        double reg=getExpr()->evaluate(w, bindings, extra);
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
        int &extra
    ) const override
    {
        double reg=getExpr()->evaluate(w, bindings, extra);
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
        int &extra
    ) const override
    {
        int callFunct = -3;
        double expr=getExpr()->evaluate(w, bindings, callFunct);
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
        int &extra
    ) const override
    {

        //return bindings.at(id);
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
        int &extra
    ) const override
    {
        int arrname = -2;
        double expr=getExpr()->evaluate(w, bindings, arrname);
        w << ".zero 4" << std::endl;

    }
};

#endif
