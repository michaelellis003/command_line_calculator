/**
 * @file tokenizer.cpp
 * @brief Implementation of a tokenizer for mathematical expressions.
 *
 * This file contains functions to tokenize a mathematical expression into
 * a sequence of tokens. The tokenizer supports operators, parentheses, 
 * and numeric values, including floating-point numbers. It also provides 
 * utility functions to determine operator precedence and associativity.
 *
 * Functions:
 * - getPrecedence(char op): Determines the precedence of a given operator.
 * - isOperatorChar(char c): Checks if a character is a valid operator.
 * - isBinaryOperatorLeftAssociative(char op): Determines if a binary operator 
 *   is left-associative.
 * - tokenizer(const std::string_view expression): Tokenizes a mathematical 
 *   expression into a vector of tokens.
 *
 * Supported Features:
 * - Operators: +, -, *, /, ^
 * - Parentheses: ( and )
 * - Numbers: Integers and floating-point values
 *
 * Notes:
 * - Exponentiation (^) is treated as a right-associative operator.
 * - Invalid characters in the expression are reported via standard error output.
 *
 * @author Michael Ellis
 * @date 2023
 */
#include "tokenizer.h"

// Function to determine operator precedence
int getPrecedence(char op) {
    if (op == '+' || op == '-') return PREC_ADD_SUB;
    if (op == '*' || op == '/') return PREC_MUL_DIV;
    if (op == '^') return PREC_POWER; // Exponentiation has higher precedence
    return 0; // Not an operator or parenthesis
}

// Function to check if a character is an operator
bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to determine if a BINARY operator character is left-associative
bool isBinaryOperatorLeftAssociative(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/') {
        return true;
    }
    if (op == '^') { // Binary Exponentiation is right-associative
        return false;
    }
    // By default, if we add new ops and forget, make them left.
    // Or throw an error for unknown operator.
    return true;
}

// Function to tokenize the input expression
std::vector<Token> tokenizer(const std::string_view expression) {
    std::vector<Token> tokens;

    for (size_t i = 0; i < expression.length(); ++i) {

        char char_token = expression[i];

        if (isspace(char_token)) { // Skip whitespace
            continue; // If no number is being built, just skip whitespace
        } else if (isOperatorChar(char_token)) {
            Token currToken{
                char_token, 
                TokenType::OPERATOR, 
                getPrecedence(char_token),
                isBinaryOperatorLeftAssociative(char_token)
            };
            tokens.push_back(currToken);
        } else if (char_token == '(') {
            Token currToken{
                char_token, 
                TokenType::LEFT_PAREN
            };
            tokens.push_back(currToken);
        } else if (char_token == ')') {
            Token currToken{
                char_token, 
                TokenType::RIGHT_PAREN
            };
            tokens.push_back(currToken);
        } else if (isdigit(char_token) || char_token == '.') {
            // Start building a number token
            std::string number_str;

            if (char_token == '.') {
                // Handle case where a number starts with a decimal point
                number_str += '0'; // Treat as "0."
            }

            while(i < expression.length() && 
                  (isdigit(expression[i]) || expression[i] == '.')) {
                number_str += expression[i];
                i++;
            }
            i--; // Adjust index since the loop will increment it
            Token currToken{
                number_str, 
                TokenType::NUMBER
            };
            tokens.push_back(currToken);

        } else {
            // Handle invalid characters
            std::cerr << "Invalid character in expression: " << char_token << std::endl;
        }
    }

    return tokens;
}