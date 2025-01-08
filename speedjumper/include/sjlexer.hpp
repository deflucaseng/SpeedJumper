#ifndef SJLEXER_HPP
#define SJLEXER_HPP

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sjoperations.hpp>
#include <map>
#include <iostream>
#include "sjtoken.hpp"





class Lexer{
	public:
		Lexer(const std::string& file_path);

		std::unique_ptr<Token> build_token(const std::string& line);
		const std::vector<std::unique_ptr<Token>>& getTokens() const {return token_vec;}
		void clear() {token_vec.clear();}
		size_t size() const {return token_vec.size();}

	private:
		std::vector<std::unique_ptr<Token>> token_vec;
		std::map<std::string, Operation> valid_operations = {
			{"plus", Operation::PLUS},
			{"minus", Operation::MINUS},
			{"times", Operation::TIMES},
			{"divided", Operation::DIVIDED},
			{"or", Operation::OR},
			{"and", Operation::AND},
			{"nor", Operation::NOR},
			{"xnor", Operation::XNOR},
			{"nand", Operation::NAND},
			{"xor", Operation::XOR},
			{"isequalto", Operation::EQUALS},
			{"isnotequalto", Operation::NEQUALS}
		};
};
#endif