#include "lexer.hpp"
#include <iostream>
#include <fstream>
#include "lexer.hpp"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    if (input.empty()) {
        std::cerr << "Error: Input file is empty." << std::endl;
        return 1;
    }
    Lexer lex(std::move(input));
    std::vector<std::unique_ptr<TokenBase>> tokens = lex.feast();

    for (auto& token : tokens) {
        token->print();
    }
    std::cout << "End of tokens\n";

    return 0;
} 
