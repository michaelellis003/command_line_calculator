#include "CLI11.h"
#include "tokenizer.h"
#
#include <iostream>

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
    std::vector<Token> tokenized_exp = tokenizer(expression); // Call the tokenizer function with the expression
    
    std::cout << "Queue contents (will empty the queue): \n";
    for (size_t i = 0; i < tokenized_exp.size(); ++i) {
        std::cout << "Value: " << tokenized_exp[i].value << " ";
        std::cout << "Precedence: " << tokenized_exp[i].precedence << "\n";
    }
    std::cout << std::endl;

    //shuntingYard(expression); // Call the tokenizer function with the expression
    //std::cout << "Expression: " << expression << std::endl;

    return 0;
}
