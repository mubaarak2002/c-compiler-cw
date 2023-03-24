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
        int &extra,
        int &funct
    ) const override
    {

        // TODO-C : Run bin/eval_expr with something like 5+a, where a=10, to make sure you understand how this works
        double first=getLeft()->evaluate(w, bindings, extra, funct);
        double next=getRight()->evaluate(w, bindings, extra, funct);
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
        int &extra,
        int &funct
    ) const override
    {

        double type=getLeft()->evaluate(w, bindings, extra, funct);
        int varType = extra + type;
        double reg=getRight()->evaluate(w, bindings, varType, funct);
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
        int &extra,
        int &funct
    ) const override

    {

        double left=getLeft()->evaluate(w, bindings, extra, funct);
        double right=getRight()->evaluate(w, bindings, extra, funct); //should be std::string
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
        int &extra,
        int &funct
    ) const override

    {
        double left=getLeft()->evaluate(w, bindings, extra, funct);
        extra--;
        double right=getRight()->evaluate(w, bindings, extra, funct);
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
        int &extra,
        int &funct
    ) const override
    {

        double reg=getLeft()->evaluate(w, bindings, extra, funct);
        int type = extra;
        if(reg > 63){
            type = -200;
        }
        else if(reg > 31){
            type = -100;
        }
        double right=getRight()->evaluate(w, bindings, type, funct);
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
        int &extra,
        int &funct
    ) const override
    {

        int functname = -2;
        int InFunct = 1;
        double left=getLeft()->evaluate(w, bindings, functname, funct);
        double content=getRight()->evaluate(w, bindings, extra, InFunct);
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
        int &extra,
        int &funct
    ) const override
    {
        int functArgs = -4;
        double args=getRight()->evaluate(w, bindings, functArgs, funct);
        int callFunct = -3;
        double left=getLeft()->evaluate(w, bindings, callFunct, funct);
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
        int &extra,
        int &funct
    ) const override
    {
        int arrname = -2;
        int getval = -3;
        if(!funct){
            double left=getLeft()->evaluate(w, bindings, arrname, funct);
            double value=getRight()->evaluate(w, bindings, getval, funct);
            w << ".zero " << value*4 << std::endl;
        }

    }
};

#endif
