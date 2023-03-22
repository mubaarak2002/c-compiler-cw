#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include<math.h>
#include "reg_name.h"

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<"( ";
        left->print(dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(dst);
        dst<<" )";
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "add " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        // TODO-D : Implement this, based on AddOperator::evaluate
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "sub " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};


class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "mul " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "div " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class OROperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "|"; }
public:
    OROperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "or " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class ANDOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "&"; }
public:
    ANDOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "and " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class XOROperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    XOROperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "xor " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class LessThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    LessThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "slt " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class GreaterThanOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    GreaterThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "sgt " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class LessThanEqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    LessThanEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "slt " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        w << "xori " << reg_name(5) << ", " << reg_name(5) << ", 1" << std::endl;
        return 5;
    }
};

class GreaterThanEqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    GreaterThanEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "sgt " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        w << "xori " << reg_name(5) << ", " << reg_name(5) << ", 1" << std::endl;
        return 5;
    }
};

class EqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    EqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "li " << reg_name(5) << ", -1" << std::endl;
        w << "mul " << reg_name(5) << ", " << reg_name(5) << ", " << reg_name(vr) << std::endl;
        w << "add " << reg_name(5) << ", " << reg_name(5) << ", " << reg_name(vl) << std::endl;
        w << "seqz " << reg_name(5) << ", " << reg_name(5) << std::endl;
        return 5;
    }
};

class IfControl
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "If"; }
public:
    IfControl(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double expr=getLeft()->evaluate(w, bindings, extra);
        std::string IFTRUE = "IFTRUE_" + std::to_string(extra);
        std::string ENDIF = "ENDIF_" + std::to_string(extra);
        extra++;
        w << "add " << reg_name(5) << ", " << reg_name(expr) << ", zero" << std::endl;
        w << "beq " << reg_name(5) << ", zero, " << ENDIF <<std::endl;
        w << "j " << IFTRUE << std::endl;
        w << IFTRUE << ":" << std::endl;
        double content=getRight()->evaluate(w, bindings, extra);
        w << "j " << ENDIF << std::endl;
        w << ENDIF << ":" << std::endl;
        return 5;
    }
};

#endif
