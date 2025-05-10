#pragma once

#include <iostream>
#include <vector>
#include <string_view>

// Precedence levels for mathematical operators. Higher values indicate
// higher precedence. These constants are used to determine the order of
// operations in expressions.
const int PREC_ADD_SUB = 1;  // Precedence for addition (+) and subtraction (-).
const int PREC_MUL_DIV = 2;  // Precedence for multiplication (*) and division (/).
const int PREC_POWER = 3;    // Precedence for exponentiation (^).

// Represents the type of a token in a mathematical expression.
enum class TokenType {
    NUMBER,        // Numeric values (e.g., "3.14", "42").
    OPERATOR,      // Mathematical operators (e.g., '+', '-', '*', '/').
    LEFT_PAREN,    // Left parenthesis '('.
    RIGHT_PAREN,   // Right parenthesis ')'.
    UNKNOWN        // Unrecognized or invalid tokens.
};

// Converts a `TokenType` to its string representation (e.g., "NUMBER").
// Useful for debugging.
std::string tokenTypeToString(TokenType type);

// Represents a token in a mathematical expression, such as a number,
// operator, or parenthesis. Includes metadata for operators like precedence
// and associativity.
struct Token {
    std::string value;  // The string value of the token (e.g., "3.14", "+").
    TokenType type;     // The type of the token.
    int precedence;     // Operator precedence (0 for non-operators).
    bool isLeftAssociative;  // True if the operator is left-associative.

    // Constructs a token for a number or non-operator symbol.
    Token(std::string val_str, TokenType t)
        : value(std::move(val_str)), type(t), precedence(0), isLeftAssociative(true) {}

    // Constructs a token for a single character (e.g., a parenthesis).
    Token(char val_char, TokenType t)
        : value(1, val_char), type(t), precedence(0), isLeftAssociative(true) {}

    // Constructs a token for an operator with specified precedence and associativity.
    Token(char val_char, TokenType t, int prec, bool is_left_assoc)
        : value(1, val_char), type(t), precedence(prec), isLeftAssociative(is_left_assoc) {}
};

// Outputs a human-readable representation of the token to the stream.
// Example: "Token(value='+', type=OPERATOR, precedence=1, isLeftAssociative=true)"
std::ostream& operator<<(std::ostream& os, const Token& token);

// Returns the precedence level for a given operator character (e.g., '+' or '*').
// Returns 0 if the character is not a recognized operator.
int getPrecedence(char op);

// Returns true if the given character is a recognized mathematical operator
// (e.g., '+', '-', '*', '/', '^').
bool isOperatorChar(char c);

// Determines if a binary operator is left-associative (e.g., '+' is left-associative).
// Returns false for right-associative operators (e.g., '^') or unrecognized operators.
bool isBinaryOperatorLeftAssociative(char op);

// Tokenizes a mathematical expression string into a vector of tokens.
// Example: "3 + 4 * (2 - 1)" -> [NUMBER(3), OPERATOR(+), NUMBER(4), OPERATOR(*), LEFT_PAREN, NUMBER(2), OPERATOR(-), NUMBER(1), RIGHT_PAREN]
std::vector<Token> tokenizer(const std::string_view expression);
