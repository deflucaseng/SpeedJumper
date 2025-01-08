#ifndef SJPARSER_HPP
#define SJPARSER_HPP

#include "sjoperations.hpp"
#include "sjtoken.hpp"
#include "sjsymboltable.hpp"
#include "sjnodes.hpp"
#include "sjnodetype.hpp"
#include <set>
#include <vector>
#include <memory>
#include <stdexcept>

class Parser {
	public:
        Parser(const std::vector<std::unique_ptr<Token>>& vec_tokens) {
            for (const std::unique_ptr<Token>& giventoken : vec_tokens) {
                switch(giventoken->gettokentype()) {
                    case TokenType::ENDTOKEN:
                        vec_nodes.push_back(build_endnode());
                        break;
                    case TokenType::JUMPTOKEN: {
                        // Clone the token instead of moving it
                        auto jump_token = std::unique_ptr<JumpToken>(
                            static_cast<JumpToken*>(giventoken->clone())
                        );
                        vec_nodes.push_back(build_jumpnode(std::move(jump_token)));
                        break;
                    }
                    case TokenType::DISPLAYTOKEN: {
                        auto display_token = std::unique_ptr<DisplayToken>(
                            static_cast<DisplayToken*>(giventoken->clone())
                        );
                        vec_nodes.push_back(build_displaynode(std::move(display_token)));
                        break;
                    }
                    case TokenType::SIMPLEASSIGNTOKEN: {
                        auto assign_token = std::unique_ptr<SimpleAssignToken>(
                            static_cast<SimpleAssignToken*>(giventoken->clone())
                        );
                        vec_nodes.push_back(build_simpleassignnode(std::move(assign_token)));
                        break;
                    }
                    case TokenType::EVALUATEDASSIGNTOKEN: {
                        auto eval_token = std::unique_ptr<EvaluatedAssignToken>(
                            static_cast<EvaluatedAssignToken*>(giventoken->clone())
                        );
                        vec_nodes.push_back(build_evaluatedassignnode(std::move(eval_token)));
                        break;
                    }
                }
            }
        }

		bool isInteger(const std::string& str) {
			try{
				std::stoi(str);
				return true;
			}catch(...){
				return false;
			}
		}

		bool isBool(const std::string& str){
			return (str == "True" || str == "true" || str == "False" || str == "false");
		}

		std::vector<std::unique_ptr<Node>>& getnodes() {return vec_nodes;}

		// Update function signatures to take by value:
		std::unique_ptr<EndNode> build_endnode();
		std::unique_ptr<JumpNode> build_jumpnode(std::unique_ptr<JumpToken> jumptoken);
		std::unique_ptr<SimpleAssignNode> build_simpleassignnode(std::unique_ptr<SimpleAssignToken> simpleassigntoken);
		std::unique_ptr<EvaluatedAssignNode> build_evaluatedassignnode(std::unique_ptr<EvaluatedAssignToken> evaluatedassigntoken);
		std::unique_ptr<DisplayNode> build_displaynode(std::unique_ptr<DisplayToken> displaytoken);
    // ...

        
        std::unordered_map<std::string, VarType> gettable() const{
            return symbol_table.gettable();
        }



        
	private:
		SymbolTable symbol_table;
		std::vector<std::unique_ptr<Node>> vec_nodes;
		std::set<Operation> boolean_operations = {
			Operation::OR,
			Operation::AND,
			Operation::NOR,
			Operation::XOR,
			Operation::XNOR,
			Operation::NAND,
			Operation::EQUALS,
			Operation::NEQUALS
		};

		std::set<Operation> integer_operations = {
			Operation::PLUS,
			Operation::MINUS,
			Operation::TIMES,
			Operation::DIVIDED
		};

};


#endif