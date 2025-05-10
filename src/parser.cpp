#include "parser.h"

void shuntingYard(std::vector<Token> tokenized_expression){
    std::stack<Token> operatorStack;
    std::vector<Token> outputQueue;

    for (const auto& token : tokenized_expression) {
        std::cout << "Processing token value: " << token << std::endl;

        if (token.type == TokenType::NUMBER) {
            outputQueue.push_back(token);
        } else if (token.type == TokenType::OPERATOR) {
            
            // While there is an operator at the top of the stack with greater precedence
            // or the same precedence and the operator is left associative
            // Pop operators from the stack to the output queue
            while(!operatorStack.empty() && 
                  operatorStack.top().precedence >= token.precedence) {
                    if (operatorStack.top().precedence > token.precedence){
                        outputQueue.push_back(operatorStack.top());
                        operatorStack.pop();
                    } else if (operatorStack.top().precedence == token.precedence && 
                               token.isLeftAssociative) {
                        outputQueue.push_back(operatorStack.top());
                        operatorStack.pop();
                    } else {
                        break; // Stop if the top operator is of lower precedence
                    }
               
            }

        } else {
            std::cerr << "Unknown token type: " << token.value << std::endl;
        }
    }
    std::cout << "Output queue contents: \n";
    for (const auto& outToken : outputQueue) {
            std::cout << outToken  << ' ';
    }
    
}