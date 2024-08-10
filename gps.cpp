#include "gps.hpp"
#include "problem.hpp"
#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> gps(std::vector<std::string> &initial_states,
                             std::vector<std::string> &goal_states,
                             std::vector<Operation> &operators) {
    std::string prefix = "Executing ";
    for (auto &op : operators) {
        op.add.push_back(prefix + op.action);
    }

    std::vector<std::string> goal_stack;
    std::vector<std::string> final_states =
        achieve_all(initial_states, operators, goal_states, goal_stack);

    if (final_states.empty()) {
        return {};
    } else {
        std::vector<std::string> filtered_states;
        for (const auto &state : final_states) {
            if (state.find(prefix) == 0) {
                filtered_states.push_back(state);
            }
        }
        return filtered_states;
    }
}

std::vector<std::string> achieve_all(std::vector<std::string> &states,
                                     std::vector<Operation> &operators,
                                     std::vector<std::string> &goals,
                                     std::vector<std::string> &goal_stack) {
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

std::vector<std::string> achieve(std::vector<std::string> &states,
                                 std::vector<Operation> &operators,
                                 std::string &goal,
                                 std::vector<std::string> &goal_stack) {
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
        std::vector<std::string> result =
            apply_operator(op, states, operators, goal, goal_stack);
        if (!result.empty()) {
            return result;
        }
    }
    return {};
}

std::vector<std::string> apply_operator(Operation &operation,
                                        std::vector<std::string> &states,
                                        std::vector<Operation> &operators,
                                        std::string &goal,
                                        std::vector<std::string> &goal_stack) {
    std::vector<std::string> new_goal_stack;
    new_goal_stack.push_back(goal);
    new_goal_stack.insert(new_goal_stack.end(), goal_stack.begin(),
                          goal_stack.end());
    std::vector<std::string> result =
        achieve_all(states, operators, operation.preconds, new_goal_stack);
    if (result.empty()) {
        return {};
    }
    std::vector<std::string> add_list = operation.add;
    std::vector<std::string> delete_list = operation.remove;

    std::vector<std::string> merge_list;

    for (auto &state : result) {
        if (std::find(delete_list.begin(), delete_list.end(), state) ==
            delete_list.end()) {
            merge_list.push_back(state);
        }
    }
    merge_list.insert(merge_list.end(), add_list.begin(), add_list.end());
    return merge_list;
}
