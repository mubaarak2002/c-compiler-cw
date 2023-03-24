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
        std::string code = "";
        double reg;
        if((vl > 31) || (vr > 31)){
            code = "fadd.s ";
            reg = 63;
        }
        else{
            code = "add ";
            reg = 5;
        }
        w << code << reg_name(reg) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return reg;
    }
};

class AddAssign
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddAssign(ExpressionPtr _left, ExpressionPtr _right)
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
        w << "add " << reg_name(vl) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
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
        double vl=getLeft()->evaluate(w, bindings, extra);
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "sub " << reg_name(5) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
        return 5;
    }
};

class SubAssign
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    SubAssign(ExpressionPtr _left, ExpressionPtr _right)
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
        w << "sub " << reg_name(vl) << ", "  << reg_name(vl) << ", " << reg_name(vr) << std::endl;
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

class NotEqualOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    NotEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
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

class WhileControl
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "If"; }
public:
    WhileControl(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        std::string CONDITION = "CONDITION_" + std::to_string(extra);
        std::string WHILETRUE = "WHILETRUE_" + std::to_string(extra);
        std::string EXIT = "EXIT_" + std::to_string(extra);
        extra++;
        w << "j " << CONDITION << std::endl;
        w << CONDITION << ":" << std::endl;
        double expr=getLeft()->evaluate(w, bindings, extra);
        w << "add " << reg_name(5) << ", " << reg_name(expr) << ", zero" << std::endl;
        w << "beq " << reg_name(5) << ", zero, " << EXIT << std::endl;
        w << "j " << WHILETRUE << std::endl;
        w << WHILETRUE << ":" << std::endl;
        double content=getRight()->evaluate(w, bindings, extra);
        w << "j " << CONDITION << std::endl;
        w << EXIT << ":" << std::endl;
        return 5;
    }
};

class LogicalAnd
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "&"; }
public:
    LogicalAnd(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        w << "addi t0, " << reg_name(vl) << ", 0" << std::endl;
        w << "beq t0, zero, .FALSE" << std::endl;
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "addi t0, " << reg_name(vr) << ", 0" << std::endl;
        w << "beq t0, zero, .FALSE" << std::endl;
        w << "li " << reg_name(5) << " ,1" << std::endl;
        w << "j .TRUE" << std::endl;
        w << ".FALSE:" << std::endl;
        w << "li " << reg_name(5) << " ,0" << std::endl;
        w << ".TRUE:" << std::endl;
        return 5;
    }
};

class LogicalOr
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "&"; }
public:
    LogicalOr(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        double vl=getLeft()->evaluate(w, bindings, extra);
        w << "addi t0, " << reg_name(vl) << ", 0" << std::endl;
        w << "bne t0, zero, .TRUE" << std::endl;
        double vr=getRight()->evaluate(w, bindings, extra);
        w << "addi t0, " << reg_name(vr) << ", 0" << std::endl;
        w << "beq t0, zero, .FALSE" << std::endl;
        w << ".TRUE:" << std::endl;
        w << "li " << reg_name(5) << " ,1" << std::endl;
        w << "j .END" <<std::endl;
        w << ".FALSE:" << std::endl;
        w << "li " << reg_name(5) << " ,0" << std::endl;
        w << ".END:" << std::endl;
        return 5;
    }
};

#endif
