#pragma once

#include "tokenizer.h"
#include <stack>

const int PREC_UNARY = 4; // Unary operators have higher precedence

// Shunting-yard algorithm to convert infix string to postfix (RPN) vector of Tokens
void shuntingYard(std::vector<Token> tokenized_expression);

