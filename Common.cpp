#include "Common.h"
#include <memory>
#include <vector>

using namespace std;

class ValuePart : public Expression {
public:
    ValuePart(int val)
    : value(val)
    {}
    
    int Evaluate() const override {
        return value;
    }
    
    string ToString() const override {
        return std::to_string(value);
    }
    
private:
    int value;
};

class BinOp : public Expression
{
public:
    BinOp(ExpressionPtr l, ExpressionPtr r) : left_op(move(l)), right_op(move(r)) {}
    
    int Evaluate() const override {
        return Oper(left_op->Evaluate(), right_op->Evaluate());
    }
    
    string ToString() const override {
        return ("(" + left_op->ToString() + ")" + Operation() + "(" + right_op->ToString() + ")");
    }
protected:
    virtual string Operation() const = 0;
    virtual int Oper(int lhs, int rhs) const = 0;
private:
    ExpressionPtr left_op;
    ExpressionPtr right_op;
};

class SumPart: public BinOp
{
public:
    SumPart(ExpressionPtr l, ExpressionPtr r)
    : BinOp(move(l), move(r))
    {}
private:
    int Oper(int lhs, int rhs) const override {
        return lhs + rhs;
    }
    
    string Operation() const override {
        return "+";
    }
    
private:
    int right, left;
};

class ProductPart: public BinOp
{
public:
    ProductPart(ExpressionPtr l, ExpressionPtr r)
    : BinOp(move(l), move(r))
    {}
private:
    int Oper(int lhs, int rhs) const override {
        return lhs * rhs;
    }
    
    string Operation() const override {
        return "*";
    }
    
private:
    int right, left;
};

ExpressionPtr Value(int value)
{
    return make_unique<ValuePart>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{
    return  make_unique<SumPart>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{
    return  make_unique<ProductPart>(move(left), move(right));
}
