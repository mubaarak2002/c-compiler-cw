#ifndef ast_functions_hpp
#define ast_functions_hpp

#include <string>
#include <iostream>
#include<math.h>

class Function
    : public Expression
{
private:
    std::string value;
    ExpressionPtr right;
protected:
    Function(const std::string &_value, ExpressionPtr _right)
        : value(_value)
        , right(_right)
    {}
public:
    virtual ~Function()
    {
        delete right;
    }

    virtual const char *getOpcode() const =0;

    std::string getValue() const
    { return value; }

    ExpressionPtr getRight() const
    { return right; }

};

class Type
    : public Function
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    Type(const std::string &_value, ExpressionPtr _right)
        : Function(_value, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        const std::map<std::string,double> &bindings
    ) const override
    {
        // TODO-C : Run bin/eval_expr with something like 5+a, where a=10, to make sure you understand how this works
        std::string val = getValue();
        double name=getRight()->evaluate(w, bindings);
        w << val << ": " << name << std::endl;
    }
};

#endif
