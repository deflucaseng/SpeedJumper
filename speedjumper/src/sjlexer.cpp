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
	std::cout << "Phase 1: Lexing step\n\tStatus ===============> Completed Successfully" << std::endl;

}

std::unique_ptr<Token> Lexer::build_token(const std::string& line) {
    std::vector<std::string> chunks = split(line);
    
    if(chunks.empty()) {
        throw std::runtime_error("Empty line after splitting: " + line);
    }

    // Check for EndToken - requires exactly 1 word
    if(chunks.size() == 1) {
        if(chunks[0] == "end") {
            return std::make_unique<EndToken>();
        }
        throw std::runtime_error("Invalid single-word command: " + line);
    }

    // Check for DisplayToken - requires exactly 2 words
    if(chunks.size() == 2) {
        if(chunks[0] == "display") {
            return std::make_unique<DisplayToken>(chunks[1]);
        }
        throw std::runtime_error("Invalid two-word command: " + line);
    }

    // Check for SimpleAssignToken - requires exactly 3 words
    if(chunks.size() == 3) {
        if(chunks[1] == "isnow") {
            return std::make_unique<SimpleAssignToken>(chunks[0], chunks[2]);
        }
        throw std::runtime_error("Invalid assignment format (expected 'isnow'): " + line);
    }

    // Check for JumpToken - requires exactly 4 words
    if(chunks.size() == 4) {
		//std::cout << chunks[0] << " "<< chunks[1] << " "<< chunks[2] << " "<< chunks[3] << " " << std::endl;
        if(chunks[0] == "jumpto") {
            if(chunks[2] != "if") {
                throw std::runtime_error("Invalid jump format (expected 'to'): " + line);
            }
            try {
                return std::make_unique<JumpToken>(std::stoi(chunks[1]), chunks[3]);
            } catch(const std::invalid_argument&) {
                throw std::runtime_error("Invalid jump value (expected number): " + line);
            }
        }
        throw std::runtime_error("Invalid four-word command: " + line);
    }

    // Check for EvaluatedAssignToken - requires exactly 5 words
    if(chunks.size() == 5) {
        if(chunks[1] != "isnow") {
            throw std::runtime_error("Invalid evaluated assignment (expected 'isnow'): " + line);
        }
        if(valid_operations.find(chunks[3]) == valid_operations.end()) {
            throw std::runtime_error("Invalid operation in assignment: " + line);
        }
        return std::make_unique<EvaluatedAssignToken>(
            chunks[0], 
            chunks[2], 
            valid_operations.at(chunks[3]), 
            chunks[4]
        );
    }

    throw std::runtime_error("Invalid syntax (unexpected number of words): " + line);
}