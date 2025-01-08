#include "../include/sjlexer.hpp"


std::vector<std::string> split(const std::string& str){
	std::vector<std::string> words;
	size_t start=0, end = 0;

	while((end = str.find(' ', start)) != std::string::npos){
		if(end > start){
			words.push_back(str.substr(start, end - start));
		}

		start = end + 1;
	}

	if(start < str.length()){
		words.push_back(str.substr(start));
	}

	return words;

}



Lexer::Lexer(const std::string& file_path){
	std::ifstream file(file_path);
	if(!file.is_open()){
		throw std::runtime_error("Cannot open file");
	}

	std::string line;
	while(std::getline(file, line)){
		if(line.length() != 0){
			token_vec.push_back(build_token(line));
		}
	}
}

std::unique_ptr<Token> Lexer::build_token(const std::string& line){
	std::vector<std::string> chunks = split(line);



/*
	The structure for building these tokens will follow the pattern below:
	If the first word is end: check if the length is one, if it is treat it as
	an endnode
	If the first word is display: Check if the length is two, if it is then
	treat it as display

	If the first word is jumpto: check the rest of the structure, then treat it as a 
	jump node

	From here we assume we are working with Assignments. 

	Check if the second string is isnow, then if the length is three. If it is three, then
	treat it as a simpleassign

	Check if the second string is isnow, the length is five, and the fourth string is in 
	the set of strings
*/

	if(chunks[0] == "end" && chunks.size() == 1){
		return std::make_unique<EndToken>();

	}else if(chunks[0] == "display" && chunks.size() == 2){
		return std::make_unique<DisplayToken>(chunks[1]);

	}else if(chunks[0] == "jumpto" && chunks.size() == 4){
		if(chunks[2] != "to"){
			std::runtime_error("Incorrect Jump Formatting");
		}
		return std::make_unique<JumpToken>(std::stoi(chunks[1]), chunks[3]);
	
	}else if(chunks.size() == 3){
		if(chunks[1] != "isnow"){
			std::runtime_error("Incorrect Simple Assignment Formatting");
		}
		return std::make_unique<SimpleAssignToken>(chunks[0], chunks[2]);

	}else if(chunks.size() == 5){
		if((chunks[1] != "isnow") || (valid_operations.find(chunks[3]) != valid_operations.end())) {
			std::runtime_error("Incorrect Evaluated Assignment Formatting");
		}
		return std::make_unique<SimpleAssignToken>(chunks[0], chunks[2], valid_operations.at(chunks[3]), chunks[4]);
	}

	std::cout << "Error caused by: " << line << std::endl;
	std::runtime_error("Unspecified incorrect syntax error");
}



