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
        int &extra,
        int &funct
    ) const override
    {
        double init = getInit()->evaluate(w, bindings, extra, funct);
        std::string CONDITION = "CONDITION_" + std::to_string(extra);
        std::string FORLOOP = "FORLOOP_" + std::to_string(extra);
        std::string INCR = "INCR_" + std::to_string(extra);
        std::string EXIT = "EXIT_" + std::to_string(extra);
        extra++;
        w << "j " << CONDITION << std::endl;
        w << CONDITION << ":" << std::endl;
        double condition = getCond()->evaluate(w, bindings, extra, funct);
        w << "add " << reg_name(5) << ", " << reg_name(condition) << ", zero" << std::endl;
        w << "beq " << reg_name(5) << ", zero, " << EXIT <<std::endl;
        w << "j " << FORLOOP << std::endl;
        w << FORLOOP << ":" << std::endl;
        double content = getContent()->evaluate(w, bindings, extra, funct);
        w << "j " << INCR << std::endl;
        w << INCR << ":" << std::endl;
        double increment = getIncr()->evaluate(w, bindings, extra, funct);
        w << "j " << CONDITION << std::endl;
        w << EXIT << ":" << std::endl;
    }
};


#endif
