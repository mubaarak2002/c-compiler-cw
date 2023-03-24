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
        int varType = extra + type;
        double reg=getRight()->evaluate(w, bindings, varType);
        return reg;
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

class CallArgs
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    CallArgs(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override

    {
        double left=getLeft()->evaluate(w, bindings, extra);
        extra--;
        double right=getRight()->evaluate(w, bindings, extra);
        //return ;
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

        double reg=getLeft()->evaluate(w, bindings, extra);
        int type = extra;
        if(reg > 63){
            type = -200;
        }
        else if(reg > 31){
            type = -100;
        }
        double right=getRight()->evaluate(w, bindings, type);
        if(reg > 63){
            w << "fadd.d " << reg_name(reg) << ", " << reg_name(right) << ", " << reg_name(95) << std::endl;
        }
        else if(reg > 31){
            w << "fadd.s " << reg_name(reg) << ", " << reg_name(right) << ", " << reg_name(63) << std::endl;
        }
        else{
            w << "add " << reg_name(reg) << ", " << reg_name(right) << ", zero" << std::endl;
        }
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

class ArrayDecleration
    : public Block
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    ArrayDecleration(ExpressionPtr _left, ExpressionPtr _right)
        : Block(_left, _right)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {
        int arrname = -2;
        int getval = -3;
        double left=getLeft()->evaluate(w, bindings, arrname);
        double value=getRight()->evaluate(w, bindings, getval);
        w << ".zero " << value*4 << std::endl;

    }
};

#endif
