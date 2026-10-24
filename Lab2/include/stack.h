#pragma once

#include "list.h"

namespace DATA_STRUCTURE {

template<class data_base>
class stack : public list<data_base> {
    public:
        stack() = default;
        ~stack() = default;

        bool empty() override {
            if(top_index == 0){
                return true;
            }
            else{
                return false;
            }
        }
        void pop() override {
            if(top_index == 0){
                return;
            }
            else{
                top_index -= 1;
            }
        }
        data_base top() override {
            if(top_index == 0){
                return data_base{};
            }
            data_base tmp;
            tmp = list_data[top_index];
            return tmp;
        }
        void push(data_base push_data) override {
            if(top_index == MAX_LINK_LIST_NUM - 1){
                return;
            }
            top_index += 1;
            list_data[top_index] = push_data;
        }
        void clear() override {
            top_index = 0;
        }
    private:
        int top_index = 0;
        data_base list_data[MAX_LINK_LIST_NUM];
};

}
