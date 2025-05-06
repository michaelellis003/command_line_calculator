/**
 * @file tokenizer.h
 * @brief Header file for tokenizing mathematical expressions into tokens for parsing.
 *
 * This file defines the structures and functions necessary for tokenizing
 * mathematical expressions into a sequence of tokens. These tokens are used
 * in parsing algorithms such as the Shunting Yard algorithm to evaluate or
 * transform expressions.
 *
 * Features:
 * - Defines the `Token` struct to represent individual tokens in an expression.
 * - Provides utility functions for determining operator precedence and associativity.
 * - Includes a tokenizer function to convert a string expression into a vector of tokens.
 *
 * Token Types:
 * - `NUMBER`: Represents numeric values.
 * - `OPERATOR`: Represents mathematical operators such as `+`, `-`, `*`, `/`, `^`.
 * - `LEFT_PAREN`: Represents the left parenthesis `(`.
 * - `RIGHT_PAREN`: Represents the right parenthesis `)`.
 * - `UNKNOWN`: Represents unrecognized or uninitialized tokens.
 *
 * Precedence Levels:
 * - `PREC_ADD_SUB`: Precedence for addition and subtraction operators (`+`, `-`).
 * - `PREC_MUL_DIV`: Precedence for multiplication and division operators (`*`, `/`).
 * - `PREC_POWER`: Precedence for the power operator (`^`).
 *
 * Usage:
 * - Use the `tokenizer` function to parse a mathematical expression into tokens.
 * - Use utility functions like `getPrecedence` and `isOperatorLeftAssociative` to
 *   assist in parsing and evaluating expressions.
 *
 * @author Michael Ellis
 * @date 2023
 */
#pragma once

#include <iostream>
#include <vector>
#include <string_view>

const int PREC_ADD_SUB = 1;
const int PREC_MUL_DIV = 2;
const int PREC_POWER = 3;

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


std::vector<Token> tokenizer(const std::string_view expression);
