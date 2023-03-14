#ifndef ast_blocks_hpp
#define ast_blocks_hpp

#include <string>
#include <iostream>
#include<math.h>
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
        std::map<double,std::string> &bindings
    ) const override
    {

        // TODO-C : Run bin/eval_expr with something like 5+a, where a=10, to make sure you understand how this works
        double first=getLeft()->evaluate(w, bindings);
        w << "next: ";
        double next=getRight()->evaluate(w, bindings);
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
        std::map<double,std::string> &bindings
    ) const override
    {

        // TODO-C : Run bin/eval_expr with something like 5+a, where a=10, to make sure you understand how this works
        double type=getLeft()->evaluate(w, bindings);
        double name=getRight()->evaluate(w, bindings); //should be std::string
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
        std::map<double,std::string> &bindings
    ) const override

    {

        w << "(";
        double left=getLeft()->evaluate(w, bindings);
        double right=getRight()->evaluate(w, bindings); //should be std::string
        w << ")" << std::endl;
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
        std::map<double,std::string> &bindings
    ) const override
    {

        w << "Assign: ";
        double left=getLeft()->evaluate(w, bindings);
        double right=getRight()->evaluate(w, bindings); //should be std::string
        //return name;
    }
};

#endif
