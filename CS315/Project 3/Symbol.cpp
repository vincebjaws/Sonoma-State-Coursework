#include "Symbol.hpp"

bool Symbol::find(char &character,std::vector<char> &index, std::vector<int> &value) {
    for(int i = 0; i<index.size(); i++){
        if(index[i] == character)
            return true;
    }
    return false;
}

int Symbol::topValue(std::stack<int> &stack) {
    if( stack.empty()) {
        std::cout << "main: Pop operation on an empty stack is not a good idea. Terminating...";
        exit(1);
    }
    int toReturn = stack.top();
    stack.pop();
    return toReturn;
}

int Symbol::evaluateExpression(const std::vector<Token *> &exprTokens, std::vector<char> &index, std::vector<int> &value) {
    std::stack<int> evalStack;
    Numbers numbers;
    for(Token *token : exprTokens) {
        if (token->isRomanNumber()) {
            std::string roman = token->romanNumber();
            //std::cout<<"THIS IS THE ROMAN NUMBER"<< roman;
            int number = numbers.converterToDecimal(roman);
            //std::cout<<"       THIS IS THE NUMBER"<< number;
            evalStack.push(number);
        }
       else if(token->isAVariable()){
           char variable = token->getVariable();
           if(find(variable, index, value)) {
               for (int i = 0; i < index.size(); i++) {
                   if (variable == index[i]) {
                       if(value[i] == NULL){
                            std::cout<<"VALUE NOT DEFINED";
                            exit(3);
                       }
                       evalStack.push(value[i]);
                   }
               }
           }
           else{
               std::cout<<"Variable not defined";
               exit(3);
           }
       }
        else if( !token->isRomanNumber() || !token->eol()) {
            int rightExpr = topValue(evalStack);
            int leftExpr = topValue(evalStack);
            if(token->isAdditionOperator())
                evalStack.push(leftExpr + rightExpr);
            else if(token->isSubtractionOperator())
                evalStack.push(leftExpr - rightExpr);
            else if(token->isMultiplicationOperator())
                evalStack.push(leftExpr * rightExpr);
            else if(token->isDivisionOperator())
                evalStack.push(leftExpr / rightExpr);
            else if(token->isModuloOperator())
                evalStack.push(leftExpr % rightExpr);
        }
        else if(token->eol())
            return topValue(evalStack);
        else {
            exit(2);
        }
    }
    return topValue(evalStack);
}


