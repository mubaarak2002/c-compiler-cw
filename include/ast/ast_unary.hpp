#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>
#include "reg_name.h"

class Unary
    : public Expression
{
private:
    ExpressionPtr expr;
protected:
    Unary(const ExpressionPtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }
};

class NegOperator
    : public Unary
{
public:
    NegOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        // TODO-F: Implement this similar to how AddOperator was implemented.
        double expr = getExpr()->evaluate(w, bindings, extra);
        w << "li " << reg_name(5) << ", -1" << std::endl;
        w << "mul " << reg_name(expr) << ", " << reg_name(5) << ", " << reg_name(expr) << std::endl;
        return expr;

    }
};

class NotOperator
    : public Unary
{
public:
    NotOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        // TODO-F: Implement this similar to how AddOperator was implemented.
        double expr = getExpr()->evaluate(w, bindings, extra);
        w << "seqz " << reg_name(expr) << ", " << reg_name(expr) << std::endl;
        return expr;

    }
};
#endif
