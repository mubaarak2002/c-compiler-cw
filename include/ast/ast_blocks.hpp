#ifndef ast_blocks_hpp
#define ast_blocks_hpp

#include <string>
#include <iostream>
#include<math.h>

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
        const std::map<std::string,double> &bindings
    ) const override
    {

        // TODO-C : Run bin/eval_expr with something like 5+a, where a=10, to make sure you understand how this works
        double first=getLeft()->evaluate(w, bindings);
        w << "next: ";
        double next=getRight()->evaluate(w, bindings);
        return first;
    }
};

#endif
