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
        const std::map<double,std::string> &bindings
    ) const override
    {

        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        w << "Variable: " << id << std::endl;

        //extend registers here if they are full

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
        const std::map<double,std::string> &bindings
    ) const override
    {
        // Using li to store in temp register and return register number
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
        const std::map<double,std::string> &bindings
    ) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        w << id << std::endl;
        //return bindings.at(id);
    }
};

#endif
