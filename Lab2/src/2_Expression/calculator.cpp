#include <stdexcept>
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
    else if(c == ')' || c == '(')
        return 0;
    else
        return -1;
    }

int calculator::priority(char c1, char c2) {
    // TODO
    if(priority_regular(c1) == 0 && priority_regular(c2) == 0)
        return 0;
    if(priority_regular(c1) >= priority_regular(c2))
        return 1;
    else
        return -1;
}

struct calculator::element calculator::read_num() {
    int num = 0, expo = 0, flag = 0;
    // TODO
    std::string operation = "+-*/^";
    std::string digit = "0123456789";
    while(expr_index < expr.size() && (digit.find(expr[expr_index]) != std::string::npos || expr[expr_index] == '.') ){
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
    calculator::element result;
    switch(c){
        case '+': 
            if(element1.flag == 0 && element2.flag == 0){
                result.flag = 0;
                result.num_int = element1.num_int + element2.num_int;
                result.num_double = 0;
            }
            else if(element1.flag == 1 && element2.flag == 0){
                result.flag = 1;
                result.num_double = element1.num_double + element2.num_int;
                result.num_int = 0;
            }
            else if(element1.flag == 0 && element2.flag == 1){
                result.flag = 1;
                result.num_double = element1.num_int + element2.num_double;
                result.num_int = 0;
            }
            else{
                result.flag = 1;
                result.num_double = element1.num_double + element2.num_double;
                result.num_int = 0;
            }
            break;
        case '-':
                if(element1.flag == 0 && element2.flag == 0){
                result.flag = 0;
                result.num_int = element1.num_int - element2.num_int;
                result.num_double = 0;
            }
            else if(element1.flag == 1 && element2.flag == 0){
                result.flag = 1;
                result.num_double = element1.num_double - element2.num_int;
                result.num_int = 0;
            }
            else if(element1.flag == 0 && element2.flag == 1){
                result.flag = 1;
                result.num_double = element1.num_int - element2.num_double;
                result.num_int = 0;
            }
            else{
                result.flag = 1;
                result.num_double = element1.num_double - element2.num_double;
                result.num_int = 0;
            }
            break;
        case '*':
            if(element1.flag == 0 && element2.flag == 0){
                result.flag = 0;
                result.num_int = element1.num_int * element2.num_int;
                result.num_double = 0;
            }
            else if(element1.flag == 1 && element2.flag == 0){
                result.flag = 1;
                result.num_double = element1.num_double * element2.num_int;
                result.num_int = 0;
            }
            else if(element1.flag == 0 && element2.flag == 1){
                result.flag = 1;
                result.num_double = element1.num_int * element2.num_double;
                result.num_int = 0;
            }
            else{
                result.flag = 1;
                result.num_double = element1.num_double * element2.num_double;
                result.num_int = 0;
            }
            break;
        case '/':
            if(element1.flag == 0 && element2.flag == 0){
                if(element2.num_int == 0)
                    throw std::runtime_error("division by zero");
                result.flag = 1;
                result.num_double = (double)element1.num_int / element2.num_int;
                result.num_int = 0;
            }
            else if(element1.flag == 1 && element2.flag == 0){
                if(element2.num_int == 0)
                    throw std::runtime_error("division by zero");
                result.flag = 1;
                result.num_double = element1.num_double / element2.num_int;
                result.num_int = 0;
            }
            else if(element1.flag == 0 && element2.flag == 1){
                if(element2.num_double == 0)
                    throw std::runtime_error("division by zero");
                result.flag = 1;
                result.num_double = element1.num_int / element2.num_double;
                result.num_int = 0;
            }
            else{
                if(element2.num_double == 0)
                    throw std::runtime_error("division by zero");
                result.flag = 1;
                result.num_double = element1.num_double / element2.num_double;
                result.num_int = 0;
            }
            break;
        case '^':
            if(element1.flag == 0 && element2.flag == 0){
                if(element1.num_int == 0 && element2.num_int < 0)
                    throw std::domain_error("a negative power of zero");
                result.flag = 1;
                result.num_double = pow(element1.num_int, element2.num_int);
                result.num_int = 0;
            }
            else if(element1.flag == 1 && element2.flag == 0){
                if(element1.num_double == 0 && element2.num_int < 0)
                    throw std::domain_error("a negative power of zero");
                result.flag = 1;
                result.num_double = pow(element1.num_double, element2.num_int);
                result.num_int = 0;
            }
            else if(element1.flag == 0 && element2.flag == 1){
                if(element1.num_int == 0 && element2.num_double < 0)
                    throw std::domain_error("a negative power of zero");
                result.flag = 1;
                result.num_double = pow(element1.num_int, element2.num_double);
                result.num_int = 0;
            }
            else{
                if(element1.num_double == 0 && element2.num_double < 0)
                    throw std::domain_error("a negative power of zero");
                result.flag = 1;
                result.num_double = pow(element1.num_double, element2.num_double);
                result.num_int = 0;
            }
            break;
    }
    return result;
}

struct calculator::element calculator::get_ans() {
    // TODO
    expr_index = 0;
    op.clear();
    num.clear();
    char cur = '\0';
    calculator::element num1 = {}, num2 = {};

    while(expr_index < expr.size()){
        cur = expr[expr_index];
        std::string operation = "+-*/^()";
        std::string digit = "0123456789";

        if(operation.find(cur) != std::string::npos){
            if(op.empty() || cur == '(')
                op.push(cur);
            else if(cur == ')'){
                while(op.top() != '('){
                        num2 = num.top();
                        num.pop();
                        num1 = num.top();
                        num.pop();
                        num.push(operate(num1, op.top(), num2));
                        op.pop();
                }
                op.pop();
            }
            else if(cur == '-' && expr[expr_index - 1] == '('){
                expr_index++;
                calculator::element negative = read_num();
                negative.num_int = -negative.num_int;
                negative.num_double = - negative.num_double;
                num.push(negative);
                continue;
            }
            else{
                switch(priority(op.top(), cur)){
                    case 1:
                        while(priority(op.top(), cur) == 1){
                            num2 = num.top();
                            num.pop();
                            num1 = num.top();
                            num.pop();
                            num.push(operate(num1, op.top(), num2));
                            op.pop();
                        }
                        op.push(cur);
                        break;
                    case -1:
                        op.push(cur);
                        break;
                    case 0:
                        op.pop();
                        break;
                }
            }
            expr_index++;
        }
        
        else if(digit.find(cur) != std::string::npos){
            num.push(read_num());
        }

    }
    while(op.empty() == false){
            cur = op.top();
            op.pop();
            num2 = num.top();
            num.pop();
            num1 = num.top();
            num.pop();
            num.push(operate(num1, cur, num2));
    }

    return num.top();
}
}