#include "tokenizer.h"
#include <cctype> 

// Converts a TokenType enum to its string representation.
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::NUMBER:       return "NUMBER";
        case TokenType::OPERATOR:     return "OPERATOR";
        case TokenType::LEFT_PAREN:   return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:  return "RIGHT_PAREN";
        case TokenType::UNKNOWN:      return "UNKNOWN";
        default:                      return "INVALID_TYPE";
    }
}

// Overloads the stream insertion operator for Token to provide a readable string representation.
std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "Token { "
       << "Value: \"" << token.value << "\", "
       << "Type: " << tokenTypeToString(token.type) << ", "
       << "Precedence: " << token.precedence << ", "
       << "IsLeftAssociative: " << (token.isLeftAssociative ? "true" : "false")
       << " }";
    return os;
}

// Returns the precedence of an operator. Higher values indicate higher precedence.
int getPrecedence(char op) {
    if (op == '+' || op == '-') return PREC_ADD_SUB; // Addition and subtraction
    if (op == '*' || op == '/') return PREC_MUL_DIV; // Multiplication and division
    if (op == '^') return PREC_POWER;               // Exponentiation
    return 0; // Non-operator characters have no precedence.
}

// Checks if a character is a recognized operator.
bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Determines if a binary operator is left-associative.
bool isBinaryOperatorLeftAssociative(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/') {
        return true; // Standard arithmetic operators are left-associative.
    }
    if (op == '^') {
        return false; // Exponentiation is right-associative.
    }
    return true; // Default to left-associative for unknown operators.
}

// Tokenizes a mathematical expression into a vector of Token objects.
std::vector<Token> tokenizer(const std::string_view expression) {
    std::vector<Token> tokens;

    for (size_t i = 0; i < expression.length(); ++i) {
        char char_token = expression[i];

        if (isspace(char_token)) {
            // Skip whitespace.
            continue;
        } else if (isOperatorChar(char_token)) {
            // Handle operators.
            tokens.push_back(
                Token(
                    char_token, 
                    TokenType::OPERATOR, 
                    getPrecedence(char_token), 
                    isBinaryOperatorLeftAssociative(char_token)
                )
            );
        } else if (char_token == '(') {
            // Handle left parenthesis.
            tokens.push_back(Token(char_token, TokenType::LEFT_PAREN));
        } else if (char_token == ')') {
            // Handle right parenthesis.
            tokens.push_back(Token(char_token, TokenType::RIGHT_PAREN));
        } else if (isdigit(char_token) || char_token == '.') {
            // Handle numeric values, including floating-point numbers.
            std::string number_str;

            if (char_token == '.') {
                // Prepend '0' if the number starts with a decimal point.
                number_str += '0';
            }

            // Accumulate digits and decimal points.
            while (i < expression.length() && 
                   (isdigit(expression[i]) || expression[i] == '.')) {
                number_str += expression[i];
                i++;
            }
            i--; // Adjust index after overshooting in the loop.

            tokens.push_back(Token(number_str, TokenType::NUMBER));
        } else {
            // Report invalid characters.
            std::cerr << "Invalid character in expression: " << char_token << std::endl;
        }
    }

    return tokens;
}
