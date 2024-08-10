#include "gps.hpp"
#include "problem.hpp"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> gps(vector<string> initial_states, vector<string> goal_states,
                   vector<Operation> &operators) {
    string prefix = "Executing ";
    for (auto &op : operators) {
        op.add.push_back(prefix + op.action);
    }

    vector<string> goal_stack;
    vector<string> final_states =
        achieve_all(initial_states, operators, goal_states, goal_stack);

    if (final_states.empty()) {
        return {};
    } else {
        vector<string> filtered_states;
        for (const auto &state : final_states) {
            if (state.find(prefix) == 0) {
                filtered_states.push_back(state);
            }
        }
        return filtered_states;
    }
}

vector<string> achieve_all(vector<string> states, vector<Operation> &operators,
                           vector<string> goals, vector<string> &goal_stack) {
    for (auto &goal : goals) {
        states = achieve(states, operators, goal, goal_stack);
        if (states.empty()) {
            return {};
        }
    }

    for (auto &goal : goals) {
        if (std::find(states.begin(), states.end(), goal) == states.end()) {
            return {};
        }
    }
    return states;
}

vector<string> achieve(vector<string> states, vector<Operation> operators,
                       string goal, vector<string> &goal_stack) {
    if (std::find(states.begin(), states.end(), goal) != states.end()) {
        return states;
    }

    if (std::find(goal_stack.begin(), goal_stack.end(), goal) !=
        goal_stack.end()) {
        return {};
    }

    for (auto &op : operators) {
        if (std::find(op.add.begin(), op.add.end(), goal) == op.add.end()) {
            continue;
        }
        vector<string> result =
            apply_operator(op, states, operators, goal, goal_stack);
        if (!result.empty()) {
            return result;
        }
    }
    return {};
}

vector<string> apply_operator(Operation operation, vector<string> states,
                              vector<Operation> operators, string goal,
                              vector<string> &goal_stack) {
    vector<string> new_goal_stack;
    new_goal_stack.push_back(goal);
    new_goal_stack.insert(new_goal_stack.end(), goal_stack.begin(),
                          goal_stack.end());
    vector<string> result =
        achieve_all(states, operators, operation.preconds, new_goal_stack);
    if (result.empty()) {
        return {};
    }
    vector<string> add_list = operation.add;
    vector<string> delete_list = operation.remove;

    vector<string> merge_list;

    for (auto &state : result) {
        if (std::find(delete_list.begin(), delete_list.end(), state) ==
            delete_list.end()) {
            merge_list.push_back(state);
        }
    }
    merge_list.insert(merge_list.end(), add_list.begin(), add_list.end());
    return merge_list;
}
