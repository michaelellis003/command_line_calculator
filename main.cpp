#include "CLI11.h"
#include "tokenizer.h"
#include "calculator.h"
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

    double answer = calculate(tokenized_exp); // Call the shunting yard algorithm with the tokenized expression
    std::cout << expression << " = " << answer << std::endl;

    return 0;
}
