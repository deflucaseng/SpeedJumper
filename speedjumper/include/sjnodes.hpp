#ifndef SJNODES_HPP
#define SJNODES_HPP

#include "sjoperations.hpp"
#include "sjnodetype.hpp"
#include <string>





class Node { 
	protected:
		NodeType node_type;


	public:
		virtual ~Node() = default;
		Node(NodeType type): node_type(type){}
		NodeType gettype() const{return node_type;}
};


class EndNode : public Node{
	private:

	public:
		EndNode(): Node(NodeType::END){}

};

class DisplayNode : public Node {
public:
    enum class DisplayType {
        BOOLLITERAL,
        INTLITERAL,
        BOOLVARIABLE,
        INTVARIABLE
    };

    DisplayNode(DisplayType displaytype, const std::string& displayval):
        Node(NodeType::DISPLAY), 
        displayval(displayval),  // Now makes a copy
        type(displaytype)        // Also initialize type!
    {}

    const std::string& getdisplayval() const {
        return displayval;            
    }

    DisplayType getdisplaytype() const {
        return type;
    }

private:
    std::string displayval;      // Store by value, not reference
    DisplayType type;
};


class JumpNode : public Node {
private:
    std::string conditiongiven;
    int jumpto;

public:
    JumpNode(int jump_to, const std::string& condition)
        : Node(NodeType::JUMP),          // Base class first
        conditiongiven(condition),       // First member variable
        jumpto(jump_to)                  // Second member variable
    {}

    const std::string& getCondition() const { return conditiongiven; }
    int getjump_to() const { return jumpto; }
};

class SimpleAssignNode : public Node{
	private:
		std::string var, value;

	public:
		SimpleAssignNode(const std::string& var, const std::string& value) : Node(NodeType::SIMPLEASSIGN), var(var), value(value){}

		const std::string& getvar() const{
			return var;
		}

		const std::string& getvalue() const{
			return value;
		}
};

class EvaluatedAssignNode : public Node {
private:
    std::string var;
    std::string lhs;
    std::string rhs;
    Operation operation;

public:
    EvaluatedAssignNode(const std::string& var, const std::string& lhs, Operation operation, const std::string& rhs)
        : Node(NodeType::EVALUATEDASSIGN),  // Base class first
          var(var),                         // Then members in order of declaration
          lhs(lhs),
          rhs(rhs),
          operation(operation)
    {}

    const std::string& getvar() const { return var; }
    const std::string& getlhs() const { return lhs; }
    const std::string& getrhs() const { return rhs; }
    Operation getop() const { return operation; }
};



#endif