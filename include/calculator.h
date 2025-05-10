#pragma once

#include "tokenizer.h"
#include <stack>
#include <cmath>       // For mathematical operations like std::pow.
#include <stdexcept>   // For exception handling with std::runtime_error.
#include <string>

// Applies the given operator (from operatorToken) to the top elements of the operand stack.
// Modifies the operandStack in place by popping the required operands and pushing the result.
// Throws a runtime error if there are insufficient operands for an operator
// or if the operator is invalid.
void applyOperation(std::stack<double>& operandStack, const Token& operatorToken);

// Evaluates a mathematical expression represented as a vector of tokens.
// Returns the computed result as a double.
// Throws runtime errors for syntax or evaluation issues (e.g., mismatched parentheses).
double calculate(const std::vector<Token>& tokenized_expression);
