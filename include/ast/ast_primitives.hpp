#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
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

        else if(extra == -2){ // sets the function label
            w << id << ":" << std::endl;
        }
        else if(extra == -3){ // call function
            w << "j " << id << std::endl;
        }
        else{ // check if variable name already exists
            for(double i = 0; i < 32; i++){
                if (bindings.at(i) == id){
                    reg = i;
                    break;
                }

            }
            if (reg == 0.0){ // makes new variable in a saved register if doesnt already exist
                if (bindings.at(8.0) == empty){ bindings.at(8.0) == id; reg = 8.0; }
                else if (bindings.at(9.0) == empty){ bindings.at(9.0) == id; reg = 9.0; }
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
        if (bindings.at(6.0) == empty){ bindings.at(6.0) = value; reg = 6.0;}
        else if (bindings.at(7.0) == empty){ bindings.at(7.0) = value; reg = 7.0;}
        else if (bindings.at(28.0) == empty){ bindings.at(28.0) = value; reg = 28.0;}
        else if (bindings.at(29.0) == empty){ bindings.at(29.0) = value; reg = 29.0;}
        else if (bindings.at(30.0) == empty){ bindings.at(30.0) = value; reg = 30.0;}
        else if (bindings.at(31.0) == empty){ bindings.at(31.0) = value; reg = 31.0;}
        w << "li " << reg_name(reg) << ", " << value << std::endl;
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

        //return bindings.at(id);
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
        if (reg != 10){
            w << "add " << reg_name(10) << ", " << reg_name(reg) << ", zero" << std::endl;
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

#endif
