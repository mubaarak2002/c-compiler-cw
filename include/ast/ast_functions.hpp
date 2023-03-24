#ifndef ast_functions_hpp
#define ast_functions_hpp

#include <string>
#include <iostream>
#include<math.h>
#include "reg_name.h"

class Function
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
    ExpressionPtr content;
protected:
    Function(ExpressionPtr _left, ExpressionPtr _right, ExpressionPtr _content)
        : left(_left)
        , right(_right)
        , content(_content)
    {}
public:
    virtual ~Function()
    {
        delete left;
        delete right;
        delete content;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    ExpressionPtr getContent() const
    { return content; }

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

class UserFunct
    : public Function
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    UserFunct(ExpressionPtr _left, ExpressionPtr _right, ExpressionPtr _content)
        : Function(_left, _right, _content)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {
        int functname = -2;
        double left=getLeft()->evaluate(w, bindings, functname, funct);
        int isfunct = -1;
        double right=getRight()->evaluate(w, bindings, isfunct, funct);
        double content = getContent()->evaluate(w, bindings, extra, funct);
        //return ret;
    }
};

class IfElseControl
    : public Function
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    IfElseControl(ExpressionPtr _left, ExpressionPtr _right, ExpressionPtr _content)
        : Function(_left, _right, _content)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra,
        int &funct
    ) const override
    {

        double expr=getLeft()->evaluate(w, bindings, extra, funct);
        std::string IFTRUE = "IFTRUE_" + std::to_string(extra);
        std::string ELSE = "ELSE_" + std::to_string(extra);
        std::string ENDIF = "ENDIF_" + std::to_string(extra);
        extra++;
        w << "add " << reg_name(5) << ", " << reg_name(expr) << ", zero" << std::endl;
        w << "beq " << reg_name(5) << ", zero, " << ELSE <<std::endl;
        w << "j " << IFTRUE << std::endl;
        w << IFTRUE << ":" << std::endl;
        double content=getRight()->evaluate(w, bindings, extra, funct);
        w << "j " << ENDIF << std::endl;
        w << ELSE << ":" << std::endl;
        double else_content=getContent()->evaluate(w, bindings, extra, funct);
        w << "j " << ENDIF << std::endl;
        w << ENDIF << ":" << std::endl;
        return 5;
    }
};


#endif
