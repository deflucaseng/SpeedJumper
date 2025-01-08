#ifndef SJCODEGEN_HPP
#define SJCODEGEN_HPP


#include <vector>
#include "sjnodes.hpp"


#include <string>
#include <variant>

#include <fmt/os.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include "sjsymboltable.hpp"
#include <iostream>

// If you still get errors, you might need these as well
#include <system_error>


class CodeGenerator{


	public:

		using NodeVariant = std::variant<
		std::unique_ptr<DisplayNode>,
		std::unique_ptr<SimpleAssignNode>,
		std::unique_ptr<EvaluatedAssignNode>,
		std::unique_ptr<JumpNode>,
		std::unique_ptr<EndNode>
		>;




		CodeGenerator(std::vector<std::unique_ptr<Node>>& nodes, const std::string& filename, const std::string& writepath, const std::unordered_map<std::string, VarType> symboltable);
		NodeVariant convertToVariant(std::unique_ptr<Node> node) {
			switch(node->gettype()) {
				case NodeType::DISPLAY:
					return NodeVariant{
						std::unique_ptr<DisplayNode>(static_cast<DisplayNode*>(node.release()))
					};
				case NodeType::SIMPLEASSIGN:
					return NodeVariant{
						std::unique_ptr<SimpleAssignNode>(static_cast<SimpleAssignNode*>(node.release()))
					};
				case NodeType::EVALUATEDASSIGN:
					return NodeVariant{
						std::unique_ptr<EvaluatedAssignNode>(static_cast<EvaluatedAssignNode*>(node.release()))
					};
				case NodeType::JUMP:
					return NodeVariant{
						std::unique_ptr<JumpNode>(static_cast<JumpNode*>(node.release()))
					};
				case NodeType::END:
					return NodeVariant{
						std::unique_ptr<EndNode>(static_cast<EndNode*>(node.release()))
					};
				default:
					throw std::runtime_error("Unknown node type");
			}
		}
		std::string displaygen(const std::unique_ptr<DisplayNode>& node);
		std::string endgen(const std::unique_ptr<EndNode>& node);
		std::string evalassigngen(const std::unique_ptr<EvaluatedAssignNode>& node);
		std::string jumpgen(const std::unique_ptr<JumpNode>& node);
		std::string simpleassigngen(const std::unique_ptr<SimpleAssignNode>& node);
		void nodeconverter(std::unique_ptr<Node> node, auto& out);
		void symboltableconverter(const std::unordered_map<std::string, VarType> symboltable, auto& out);






	private:
		const std::unordered_map<std::string, VarType> cgsymboltable;

		class NodeVisitor {
			CodeGenerator& codeGen;
			public:
				NodeVisitor(CodeGenerator& gen): codeGen(gen){}


				std::string operator()(const std::unique_ptr<DisplayNode>& node) {
					return codeGen.displaygen(node);
				}
				std::string operator()(const std::unique_ptr<SimpleAssignNode>& node) {
					return codeGen.simpleassigngen(node);
				}
				std::string operator()(const std::unique_ptr<EvaluatedAssignNode>& node) {
					return codeGen.evalassigngen(node);
				}
				std::string operator()(const std::unique_ptr<JumpNode>& node) {
					return codeGen.jumpgen(node);
				}
				std::string operator()(const std::unique_ptr<EndNode>& node) {
					return codeGen.endgen(node);
				}
		};

		std::unordered_map<Operation, std::string> eval_assign = {
		{Operation::PLUS, R"(
mov eax, {lhs}
mov ebx, {rhs}
add eax, ebx
mov dword [{var}], eax
)"},
		{Operation::MINUS, R"(
mov eax, {lhs}
mov ebx, {rhs}
sub eax, ebx
mov dword [{var}], eax\
)"},
		{Operation::TIMES, R"(
mov eax, {lhs}
mov ebx, {rhs}
mul ebx
mov dword [{var}], eax
)"},
		{Operation::DIVIDED, R"(
xor edx, edx
mov eax, {lhs}
mov ebx, {rhs}
div ebx
mov dword [{var}], eax
)"},
		{Operation::EQUALS, R"(
mov eax, {lhs}
mov ebx, {rhs}
cmp eax, ebx
setz cl
movzx ecx, cl
mov dword [{var}], ecx
)"},
		{Operation::NEQUALS, R"(
mov eax, {lhs}
mov ebx, {rhs}
cmp eax, ebx
setz cl
xor cl, 1
movzx ecx, cl
mov dword [{var}], ecx
)"},
		{Operation::AND, R"(
mov eax, {lhs}
mov ebx, {rhs}
and eax, ebx
mov dword [{var}], eax
)"},
		{Operation::OR, R"(
mov eax, {lhs}
mov ebx, {rhs}
or eax, ebx
mov dword [{var}], eax
)"},
		{Operation::XOR, R"(
mov eax, {lhs}
mov ebx, {rhs}
xor eax, ebx
mov dword [{var}], eax
)"},
		{Operation::XNOR, R"(
mov eax, {lhs}
mov ebx, {rhs}
xor eax, ebx
not eax
mov dword [{var}], eax
)"},
		{Operation::NAND, R"(
mov eax, {lhs}
mov ebx, {rhs}
and eax, ebx
not eax
mov dword [{var}], eax
)"},
		{Operation::NOR,  R"(
mov eax, {lhs}
mov ebx, {rhs}
or eax, ebx
not eax
mov dword [{var}], eax
)"}
		};
};

#endif