#include <vector>

bool Is_legal(std::vector<char> &opt){
    std::vector<int> stack;
    for(size_t i = 0; i < opt.size(); i++){
        if(opt[i] == 'I')
            stack.push_back(1);
        else if(opt[i] == 'O'){
            if(stack.empty())
                return false;
            else{
                stack.pop_back();
            }
        }
    }
    if(!stack.empty())
        return false;
    else
        return true;
}