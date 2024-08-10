#include "gps.hpp"
#include "problem.hpp"
#include <iostream>

Problem define_problem();

int main() {
    Problem problem = define_problem();
    std::vector<std::string> start = problem.start;
    std::vector<std::string> finish = problem.finish;
    std::vector<Operation> operators = problem.operators;
    std::vector<std::string> actions = gps(start, finish, operators);

    for (auto &action : actions) {
        std::cout << action << std::endl;
    }
    return 0;
}

Problem define_problem() {
    std::vector<std::string> start = {
        "at door", "on floor", "has ball", "hungry", "chair at door",
    };

    std::vector<std::string> finish = {"not hungry"};

    std::vector<Operation> ops = {
        {"climb on chair",
         {"chair at middle room", "at middle room", "on floor"},
         {"at bananas", "on chair"},
         {"at middle room", "on floor"}},
        {"push chair from door to midle room",
         {"chair at door", "at door"},
         {"chair at middle room", "at middle room"},
         {"chair at door", "at door"}},
        {"walk from door to middle room",
         {"at door", "on floor"},
         {"at middle room"},
         {"at door"}},
        {"grasp bananas",
         {"at bananas", "empty handed"},
         {"has bananas"},
         {"empty handed"}},
        {"drop ball", {"has ball"}, {"empty handed"}, {"has ball"}},
        {"eat bananas",
         {"has bananas"},
         {"empty handed", "not hungry"},
         {"has bananas", "hungry"}}};

    return {start, finish, ops};
}
