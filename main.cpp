#include "gps.hpp"
#include "problem.hpp"
#include <iostream>

using namespace std;

Problem define_problem();

int main() {
    Problem problem = define_problem();

    for (auto &action : gps(problem.start, problem.finish, problem.operators)) {
        cout << action << endl;
    }
    return 0;
}

Problem define_problem() {
    vector<string> start = {
        "at door", "on floor", "has ball", "hungry", "chair at door",
    };

    vector<string> finish = {"not hungry"};

    vector<Operation> operators = {
        {"climb on chair",
         {"chair at middle room", "at middle room", "on floor"},
         {"at bananas", "on chair"},
         {"at middle room", "on floor"}},
        {"push chair from door to middle room",
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

    return {start, finish, operators};
}
