#ifndef ast_blocks_hpp
#define ast_blocks_hpp

#include <string>
#include <iostream>
#include <math.h>
#include "reg_name.h"

class Block
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Block(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Block()
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
class Sequence
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    Sequence(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {

        // TODO-C : Run bin/eval_expr with something like 5+a, where a=10, to make sure you understand how this works
        double first=getLeft()->evaluate(w, bindings, extra);
        double next=getRight()->evaluate(w, bindings, extra);
        return first;
    }
};

class Decleration
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    Decleration(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {

        double type=getLeft()->evaluate(w, bindings, extra);
        double name=getRight()->evaluate(w, bindings, extra);
        //return name;
    }
};

class Args
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    Args(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override

    {

        double left=getLeft()->evaluate(w, bindings, extra);
        double right=getRight()->evaluate(w, bindings, extra); //should be std::string
        //return name;
    }
};


class Assign
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    Assign(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {

        double left=getLeft()->evaluate(w, bindings, extra);
        double right=getRight()->evaluate(w, bindings, extra); //should be std::string
        //return name;
        w << "add "<<reg_name(left)<<", "<<reg_name(right)<<", zero" << std::endl;
    }
};

class SimpleFunct
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    SimpleFunct(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {

        int functname = -2;
        double left=getLeft()->evaluate(w, bindings, functname);
        double content=getRight()->evaluate(w, bindings, extra);
        //return ret;
    }
};

class FunctCallwArgs
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    FunctCallwArgs(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        int functArgs = -4;
        double args=getRight()->evaluate(w, bindings, functArgs);
        int callFunct = -3;
        double left=getLeft()->evaluate(w, bindings, callFunct);
        return 10;
    }
};

#endif
