#include <iostream>
#include <vector>
#include <string>

int main() {
    const int N = 8;              
    const int TOTAL = 6561;       
    char choices[3] = {' ', '+', '-'};
   for (int opt_num = 0; opt_num < TOTAL; opt_num++) {
        int temp = opt_num;
        std::vector<char> opts(N);
        for (int i = N - 1; i >= 0; i--) {
            opts[i] = choices[temp % 3];
            temp /= 3;
        }

        std::string expr = "1";
        int result = 0;
        int cur_num = 1;
        char sign = '+';

        for (int i = 0; i < N; i++) {
            int digit = i + 2;
            char op = opts[i];

            if (op == ' ') {
                cur_num = cur_num * 10 + digit;
                expr += std::to_string(digit);
            } else {
                if (sign == '+') 
                    result += cur_num;
                else             
                    result -= cur_num;

                sign = op;
                cur_num = digit;
                expr += op;
                expr += std::to_string(digit);
            }
        }

        if (sign == '+')   
            result += cur_num;
        else            
            result -= cur_num;

        if (result == 110) {
            std::cout << expr << " = 110" << std::endl;
        }
    }

    return 0;
}