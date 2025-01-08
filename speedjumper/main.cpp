//#include "include/pch.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "include/pch.hpp"

namespace fs = std::filesystem;


void runcompiler(const std::string& srcpath, const std::string& filename, const std::string& writepath){
    Lexer lexer = Lexer("test/" + srcpath);
    Parser parser = Parser(lexer.getTokens());
    CodeGenerator codegen = CodeGenerator(parser.getnodes(), filename, writepath, parser.gettable());
}




int main() {
    const std::string path = "test";  // Folder name
    const std::string extension = ".eng";  // File extension to search for

    try {
        // Check if directory exists
        if (!fs::exists(path)) {
            std::cerr << "Error: Directory '" << path << "' does not exist." << std::endl;
            return 1;
        }

        // Check if path is actually a directory
        if (!fs::is_directory(path)) {
            std::cerr << "Error: '" << path << "' is not a directory." << std::endl;
            return 1;
        }

		std::cout << "Running SpeedJumper by Lucas Eng\n\n";


        // Counter for .eng files
        int fileCount = 1;

        // Iterate over all files in the directory
        for (const auto& entry : fs::directory_iterator(path)) {
            // Check if the current entry is a regular file
            if (fs::is_regular_file(entry)) {
                // Get the file extension
                std::string currentExtension = entry.path().extension().string();
                
                // Check if the extension matches .eng
                if (currentExtension == extension) {
                    std::cout << "Compiling and Executing File #"<< fileCount << ":\t" << entry.path().filename() << "\n\n" << std::endl;
                    fileCount++;




					runcompiler(entry.path().filename(), entry.path().filename(), "assembly");

                }
            }
        }



    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}