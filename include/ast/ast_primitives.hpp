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
        std::map<double,std::string> &bindings
    ) const override
    {

        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        w << "Variable: " << id << std::endl;

        double reg = 0;

        if (bindings.at(8.0) == id){ reg = 8.0; }
        else if (bindings.at(9.0) == id){ reg = 9.0; }
        else if (reg == 0.0){
            for(double i = 18; i < 28; i++){
                if (bindings.at(i) == id){
                    reg = i;
                    break;
                }
            }
        }
        std::string empty = ".";
        if (reg == 0.0){
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
        std::map<double,std::string> &bindings
    ) const override
    {
        // Using li to store in temp register and return register number
        w << value << std::endl;
        return value;
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
        std::map<double,std::string> &bindings
    ) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        w << id << "Type" << std::endl;
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

    virtual void print(std::ostream &dst) const override{
    }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings
    ) const override
    {
        w << "Return" << std::endl;
    }
};

#endif
