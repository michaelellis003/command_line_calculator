#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <queue>
#include <stack>

const int PREC_ADD_SUB = 1;
const int PREC_MUL_DIV = 2;
const int PREC_POWER = 3;
const int PREC_UNARY = 4; // Unary operators have higher precedence

// Enum to represent the type of a token
enum class TokenType {
    NUMBER,
    OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN,
    UNKNOWN     // For errors or uninitialized
};

// Struct to represent a token
struct Token {
    std::string value;      // The string representation of the token (e.g., "3.14", "+")
    TokenType type = TokenType::UNKNOWN;
    int precedence = 0;
    bool isLeftAssociative = true;

    // Constructor for numbers
    Token(std::string val, TokenType t) :
        value(std::move(val)), type(t) {}

    // Constructor for operators/parentheses
    Token(char opChar, TokenType t, int prec = 0, bool assoc = true) :
        value(1, opChar), type(t), precedence(prec), isLeftAssociative(assoc) {}

    Token(std::string val, TokenType t, int prec, bool assoc) :
        value(std::move(val)), type(t), precedence(prec), isLeftAssociative(assoc) {}

};

// Function to determine operator precedence
int getPrecedence(char op);

// Function to check if a character is an operator
bool isOperatorChar(char c);

// Function to determine if an operator character is left-associative
bool isOperatorLeftAssociative(char op);


std::queue<Token> tokenizer(const std::string_view expression);

// Shunting-yard algorithm to convert infix string to postfix (RPN) vector of Tokens
//void shuntingYard(const std::string_view expression);