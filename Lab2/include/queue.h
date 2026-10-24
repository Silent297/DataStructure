#pragma once

#include "list.h"

namespace DATA_STRUCTURE {

template<class data_base>
class queue : public list<data_base> {
    public:
        queue() = default;
        ~queue() = default;

        bool empty() override {
            if(top_index == tail_index){
                return true;
            }
            else{
                return false;
            }
        }
        void pop() override {
            if(empty()){
                return;
            }
            top_index = (top_index - 1 + MAX_LINK_LIST_NUM) % MAX_LINK_LIST_NUM;
        }
        data_base top() override {
            if(empty()){
                return data_base{};
            }
            data_base tmp;
            tmp = list_data[top_index];
            return tmp;
        }
        void push(data_base push_data) override {
            if((top_index + 1) % MAX_LINK_LIST_NUM == tail_index){
                return;
            }
            list_data[tail_index] = push_data;
            tail_index = (tail_index - 1 + MAX_LINK_LIST_NUM) % MAX_LINK_LIST_NUM;
        }
        void clear() override {
            top_index = tail_index = 0;
        }
    private:
        int top_index = 0;
        int tail_index = 0;
        data_base list_data[MAX_LINK_LIST_NUM];
};

}
