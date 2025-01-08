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
		enum class DisplayType{
			BOOLLITERAL,
			INTLITERAL,
			BOOLVARIABLE,
			INTVARIABLE

		};

		DisplayNode(DisplayType displaytype, const std::string& displayval):Node(NodeType::DISPLAY), displayval(displayval){}

		const std::string& getdisplayval() const{
			return displayval;			
		}

		DisplayType getdisplaytype() const {
			return type;

		}

	private:
		const std::string& displayval;
		DisplayType type;
};


class JumpNode : public Node{
	private:
		std::string condition;
		int jump_to;
	
	public:
		JumpNode(int jump_to, const std::string& condition):jump_to(jump_to), condition(condition), Node(NodeType::JUMP){}

		const std::string& getCondition() const {return condition;}
		int getjump_to() const {return jump_to;}
};

class SimpleAssignNode : public Node{
	private:
		std::string var, value;

	public:
		SimpleAssignNode(const std::string& var, const std::string& value) : var(var), value(value), Node(NodeType::SIMPLEASSIGN){}

		const std::string& getvar() const{
			return var;
		}

		const std::string& getvalue() const{
			return value;
		}
};

class EvaluatedAssignNode : public Node{
	private:
		std::string var, lhs, rhs;
		Operation operation;

	public:
		EvaluatedAssignNode(const std::string& var, const std::string& lhs, Operation operation, const std::string& rhs):
		var(var), lhs(lhs), operation(operation), rhs(rhs), Node(NodeType::EVALUATEDASSIGN){}

		const std::string getvar() const {return var;}
		const std::string getlhs() const {return lhs;}
		const std::string getrhs() const {return rhs;}
		Operation getop() const {return operation;}







};



#endif