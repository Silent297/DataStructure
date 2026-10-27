#include "calculator.h"

namespace DATA_STRUCTURE {

std::string calculator::get_expr() {
    return expr;
}

bool calculator::legal() {
    int bracket = 0;
    // TODO
    char cur,last;
    last = '\0';
    std::string operation = "+-*/^";
    for(size_t i = 0; i < expr.size(); i++){
        cur = expr[i];
        if(cur == '(')
            bracket += 1;
        if(cur == ')'){
            bracket -= 1;
        }
        if(bracket < 0){
            return false;
        }
        if(operation.find(last) != std::string::npos && operation.find(cur) != std::string::npos)
            return false;
        last = expr[i];
    }
    if(operation.find(cur) != std::string::npos)
        return false;
    return bracket == 0;
}

int calculator::priority_regular(char c) {
    // TODO
    if(c == '^')
        return 3;
    else if(c == '*' || c == '/')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else if(c == '(' || c == ')')
        return 0;
    else
        return -1;
    }

int calculator::priority(char c1, char c2) {
    // TODO
    if(priority_regular(c1) >= priority_regular(c2))
        return 1;
    else
        return 0;
}

struct calculator::element calculator::read_num() {
    int num = 0, expo = 0, flag = 0;
    // TODO
    std::string operation = "+-*/^";
    std::string digit = "0123456789";
    while(expr_index >= expr.size() && digit.find(expr[expr_index]) != std::string::npos || expr[expr_index] == '.'){
        char c = expr[expr_index];
        if(digit.find(c) != std::string::npos){
            int n = c - '0';
            num = num * 10 + n;
            if(flag == 1){
                expo++;
            }
        }
        if(c == '.')
            flag = 1;
        expr_index++;
    }
    if(flag == 1){
        return {flag, 0, num * pow(10, -expo)};
    }
    else{
        return {flag, num, 0};
    }
}

struct calculator::element calculator::operate(struct calculator::element element1, char c, struct calculator::element element2) {
    // TODO
    return {0, 0, 0};
}

struct calculator::element calculator::get_ans() {
    // TODO
    return {0, 0, 0};
}

}