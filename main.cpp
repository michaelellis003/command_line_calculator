#include "CLI11.h"
#include "tokenizer.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) { // Standard main function
    CLI::App app{"Mathematical expression parser and evaluator"};

    std::string_view expression; // Variable to hold the expression
    app.add_option("-e,--expression", expression, "Mathematical Expression to evaluate")
        ->required();

    try {
        app.parse(argc, argv); // Explicitly call parse
    } catch (const CLI::ParseError &e) {
        // Handle errors explicitly
        return app.exit(e);
    }

    // Use parsed value
    std::queue<Token> tokenized_exp = tokenizer(expression); // Call the tokenizer function with the expression
    
    std::cout << "Queue contents (will empty the queue): \n";
    while (!tokenized_exp.empty()) {
        std::cout << "Value: " << tokenized_exp.front().value << " ";
        std::cout << "Precedence: " << tokenized_exp.front().precedence << "\n";
        tokenized_exp.pop(); // Remove the front element
    }
    std::cout << std::endl;

    //shuntingYard(expression); // Call the tokenizer function with the expression
    //std::cout << "Expression: " << expression << std::endl;

    return 0;
}
