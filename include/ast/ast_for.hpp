#ifndef ast_for_hpp
#define ast_for_hpp

#include <string>
#include <iostream>
#include <math.h>
#include "reg_name.h"

class forClass
    : public Expression
{
private:
    ExpressionPtr init;
    ExpressionPtr cond;
    ExpressionPtr incr;
    ExpressionPtr content;
protected:
    forClass(ExpressionPtr _init, ExpressionPtr _cond,ExpressionPtr _incr, ExpressionPtr _content)
        : init(_init)
        , cond(_cond)
        , incr(_incr)
        , content(_content)
    {}
public:
    virtual ~forClass()
    {
        delete init;
        delete cond;
        delete incr;
        delete content;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getInit() const
    { return init; }

    ExpressionPtr getCond() const
    { return cond; }

    ExpressionPtr getIncr() const
    { return incr; }

    ExpressionPtr getContent() const
    { return content; }

    virtual void print(std::ostream &dst) const override
    {
        // dst<<"( ";
        // left->print(dst);
        // dst<<" ";
        // dst<<getOpcode();
        // dst<<" ";
        // right->print(dst);
        // dst<<" )";
    }

};

class ForControl
    : public forClass
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    ForControl(ExpressionPtr _init, ExpressionPtr _cond, ExpressionPtr _incr, ExpressionPtr _content)
        : forClass(_init, _cond, _incr, _content)
    {}

    virtual double evaluate(
        std::ostream &w,
        std::map<double,std::string> &bindings,
        int &extra
    ) const override
    {

        // double expr=getLeft()->evaluate(w, bindings, extra);
        // std::string IFTRUE = "IFTRUE_" + std::to_string(extra);
        // std::string ELSE = "ELSE_" + std::to_string(extra);
        // std::string ENDIF = "ENDIF_" + std::to_string(extra);
        // extra++;
        // w << "add " << reg_name(5) << ", " << reg_name(expr) << ", zero" << std::endl;
        // w << "beq " << reg_name(5) << ", zero, " << ELSE <<std::endl;
        // w << "j " << IFTRUE << std::endl;
        // w << IFTRUE << ":" << std::endl;
        // double content=getRight()->evaluate(w, bindings, extra);
        // w << "j " << ENDIF << std::endl;
        // w << ELSE << ":" << std::endl;
        // double else_content=getContent()->evaluate(w, bindings, extra);
        // w << "j " << ENDIF << std::endl;
        // w << ENDIF << ":" << std::endl;
        // return 5;
        w << "for loop " << std::endl;
    }
};


#endif
