#include <set>
#include <tuple>
#include "walk.h"

namespace DATA_STRUCTURE {

void walk::print_para() {
    std::cout << steps << std::endl;
    for (int i = 0; i < gold_num; i++) {
        std::cout << *(gold + 2 * i) << " " << *(gold + 2 * i + 1) << " " << *(gold_value + i) << std::endl;
    }
}

int walk::compute_distance(int i, int x, int y) {
    // TODO
    return ceil( (double) abs(x - gold[2*i]) / 2) + ceil( (double) abs(y - gold[2*i+1]) / 2);
}

int walk::get_value() {
    int max_value = 0;
    // TODO
    walk::element cur = {};
    cur.x = 0, cur.y = 0;
    cur.steps = steps;
    cur.value = 0;
    cur.get_gold = {};
    cur.gold_state.assign(gold_num, '0');
    q.push(cur);

    std::set<std::tuple<int, int, int, std::string>> visited;
    visited.insert(std::make_tuple(cur.x, cur.y, cur.steps, cur.gold_state));

    while(q.empty() == false){
        cur = q.top();
        q.pop();
        if(cur.steps == 0){
            continue;
        }
        walk::element next = {};

        const int dx[8] = {1, 2, -1, -2, 0, 0, 0, 0};
        const int dy[8] = {0, 0, 0, 0, 1, 2, -1, -2};
        for(int i = 0; i < 8; i++){
            next.x = cur.x + dx[i], next.y = cur.y + dy[i], next.steps = cur.steps - 1, next.get_gold = cur.get_gold, next.value = cur.value, next.gold_state = cur.gold_state;
            for(int j = 0; j < gold_num; j++){
                if(next.get_gold.find(j)){
                    continue;
                }
                if(compute_distance(j, next.x, next.y) == 0){
                    next.get_gold.insert(j);
                    next.value += gold_value[j];
                    next.gold_state[j] = '1';
                }
            }
            max_value = (next.value >= max_value) ? next.value : max_value;

            bool can_gain_more = false;
            for (int j = 0; j < gold_num; ++j) {
                if (next.get_gold.find(j))
                    continue;
                if (compute_distance(j, next.x, next.y) <= next.steps) {
                    can_gain_more = true;
                    break;
                    }
                }
            if (!can_gain_more)
                continue;

            auto key = std::make_tuple(next.x, next.y, next.steps, next.gold_state);
            if (visited.count(key) == 0) {    
                visited.insert(key);    
                q.push(next);
            }
        }
    }

    return max_value;
}

}