#ifndef SJTOKEN_HPP
#define SJTOKEN_HPP

#include <string>
#include "sjoperations.hpp"

enum class TokenType {
    ENDTOKEN,
    JUMPTOKEN,
    DISPLAYTOKEN,
    SIMPLEASSIGNTOKEN,
    EVALUATEDASSIGNTOKEN
};

class Token {
protected:
    TokenType token_type;

public:
    Token(TokenType type) : token_type(type) {}
    virtual ~Token() = default;
    TokenType gettokentype() const { return token_type; }
    virtual Token* clone() const = 0;  // Add this pure virtual method
};

class EndToken : public Token {
public:
    EndToken() : Token(TokenType::ENDTOKEN) {}
    Token* clone() const override {
        return new EndToken(*this);
    }
};

class JumpToken : public Token {
private:
    std::string condition;
    int jump_to;
public:
    JumpToken(int jump, const std::string& cond) 
        : Token(TokenType::JUMPTOKEN), condition(cond), jump_to(jump) {}
    
    const std::string& getCondition() const { return condition; }
    int getJumpTo() const { return jump_to; }
    Token* clone() const override {
        return new JumpToken(*this);
    }
};

class DisplayToken : public Token {
private:
    std::string display_val;
public:
    DisplayToken(const std::string& val) 
        : Token(TokenType::DISPLAYTOKEN), display_val(val) {}
    
    const std::string& getDisplayValue() const { return display_val; }
    Token* clone() const override {
        return new DisplayToken(*this);
    }
};

class SimpleAssignToken : public Token {
private:
    std::string var;
    std::string value;

public:
    SimpleAssignToken(const std::string& variable, const std::string& val) 
        : Token(TokenType::SIMPLEASSIGNTOKEN), var(variable), value(val) {}
    
    const std::string& getVariable() const { return var; }
    const std::string& getValue() const { return value; }
    Token* clone() const override {
        return new SimpleAssignToken(*this);
    }
};

class EvaluatedAssignToken : public Token {
private:
    std::string var;
    std::string lhs;
    Operation op;
    std::string rhs;

public:
    EvaluatedAssignToken(const std::string& variable, 
                        const std::string& left, Operation oper, 
                        const std::string& right)
        : Token(TokenType::EVALUATEDASSIGNTOKEN), var(variable), lhs(left), op(oper), rhs(right) {}
    
    const std::string& getVariable() const { return var; }
    const std::string& getLHS() const { return lhs; }
    enum Operation getOperator() const { return op; }
    const std::string& getRHS() const { return rhs; }
    Token* clone() const override {
        return new EvaluatedAssignToken(*this);
    }
};

#endif