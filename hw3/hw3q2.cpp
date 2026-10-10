int Ack1(int m,int n){
    if(m == 0)
        return n+1 ;
    else if(m != 0 && n == 0)
        return Ack1(m-1,1);
    else if(m != 0 && n != 0)
        return Ack1(m-1, Ack1(m, n-1));
}

#include <stack>

enum class State{
    Waiting,Calculate
};

typedef struct ack{
    int m;
    int n;
    State state;      //用于指示
}ack;


int Ack2(int m,int n){
    std::stack<ack> s;
    s.push({m, n, State::Calculate});

    while(s.empty() == false){
        ack cur = s.top();
        s.pop();

        if(cur.state == State::Calculate){
            if(cur.m == 0){
                int result = cur.n + 1;
                if(s.empty()){
                    return result;
                }
                else{
                    ack last = s.top();
                    s.pop();
                    last.n = result;
                    last.state = State::Calculate;
                    s.push(last);
                }
            }
            else if(cur.n == 0){
                s.push({cur.m-1, 1, State::Calculate});
            }
            else{
                s.push({cur.m-1, 0, State::Waiting});   //0表示n空缺，等待内层计算结果
                s.push({cur.m, cur.n-1, State::Calculate});
            }
        }
        else{
            s.push({cur.m, cur.n, State::Calculate});   //应该不会到达这个分支，前面的选择已经处理过了
        }
    }
    return 0;  //这里正常也是不会到达的
}


