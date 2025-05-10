#include "calculator.h"

// Applies an operator to the top two operands on the stack.
// Throws a runtime error if there are insufficient operands for an operator
// or if the operator is invalid.
void applyOperation(std::stack<double>& operandStack, const Token& operatorToken) {
    if (operandStack.size() < 2) {
        throw std::runtime_error("Syntax Error: Insufficient operands for operator " + operatorToken.value);
    }

    // Pop the top two operands.
    double op2 = operandStack.top(); operandStack.pop();
    double op1 = operandStack.top(); operandStack.pop();

    // Perform the operation based on the operator.
    char op_char = operatorToken.value[0];
    if (op_char == '+') {
        operandStack.push(op1 + op2);
    } else if (op_char == '-') {
        operandStack.push(op1 - op2);
    } else if (op_char == '*') {
        operandStack.push(op1 * op2);
    } else if (op_char == '/') {
        if (op2 == 0) {
            throw std::runtime_error("Math Error: Division by zero");
        }
        operandStack.push(op1 / op2);
    } else if (op_char == '^') {
        operandStack.push(std::pow(op1, op2));
    } else {
        throw std::runtime_error("Syntax Error: Unknown operator " + operatorToken.value);
    }
}

// Evaluates a mathematical expression represented as a vector of tokens.
// Returns the computed result as a double.
// Throws runtime errors for syntax or evaluation issues (e.g., mismatched parentheses).
double calculate(const std::vector<Token>& tokenized_expression) {
    std::stack<double> operandStack;  // Stack for operands (numbers).
    std::stack<Token> operatorStack; // Stack for operators and parentheses.

    if (tokenized_expression.empty()) {
        throw std::runtime_error("Evaluation Error: Empty expression");
    }

    for (const auto& token : tokenized_expression) {
        if (token.type == TokenType::NUMBER) {
            // Push numbers directly onto the operand stack.
            operandStack.push(std::stod(token.value));
        } else if (token.type == TokenType::LEFT_PAREN) {
            // Push left parentheses onto the operator stack.
            operatorStack.push(token);
        } else if (token.type == TokenType::RIGHT_PAREN) {
            // Process operators until a matching left parenthesis is found.
            while (!operatorStack.empty() && operatorStack.top().type != TokenType::LEFT_PAREN) {
                applyOperation(operandStack, operatorStack.top());
                operatorStack.pop();
            }

            // Ensure a matching left parenthesis exists.
            if (operatorStack.empty() || operatorStack.top().type != TokenType::LEFT_PAREN) {
                throw std::runtime_error("Syntax Error: Mismatched parentheses (missing '(').");
            }

            // Pop the left parenthesis.
            operatorStack.pop();
        } else if (token.type == TokenType::OPERATOR) {
            // Process operators based on precedence and associativity.
            while (!operatorStack.empty() &&
                   operatorStack.top().type == TokenType::OPERATOR &&
                   ((operatorStack.top().precedence > token.precedence) ||
                    (operatorStack.top().precedence == token.precedence && token.isLeftAssociative))) {
                applyOperation(operandStack, operatorStack.top());
                operatorStack.pop();
            }

            // Push the current operator onto the stack.
            operatorStack.push(token);
        } else {
            throw std::runtime_error("Syntax Error: Unknown token type encountered.");
        }
    }

    // Process remaining operators in the stack.
    while (!operatorStack.empty()) {
        if (operatorStack.top().type == TokenType::LEFT_PAREN || operatorStack.top().type == TokenType::RIGHT_PAREN) {
            throw std::runtime_error("Syntax Error: Mismatched parentheses at end of expression.");
        }
        applyOperation(operandStack, operatorStack.top());
        operatorStack.pop();
    }

    // Ensure the operand stack contains exactly one result.
    if (operandStack.size() != 1) {
        throw std::runtime_error("Evaluation Error: Operand stack malformed at end of calculation.");
    }

    return operandStack.top();
}
