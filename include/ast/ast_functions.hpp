#ifndef ast_functions_hpp
#define ast_functions_hpp

#include <string>
#include <iostream>
#include<math.h>

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
        const std::map<std::string,double> &bindings
    ) const override
    {

        w << std::endl << std::endl << "-------Function name : ";
        double left=getLeft()->evaluate(w, bindings);
        w << "-------Arguements: ";
        double right=getRight()->evaluate(w, bindings);
        w << "-------Code: ";
        double content = getContent()->evaluate(w, bindings);
        w << std::endl << std::endl;
        //return ret;
    }
};


#endif
