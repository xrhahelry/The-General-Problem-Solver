#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <string>
#include <vector>

typedef struct Operation {
    std::string action;
    std::vector<std::string> preconds;
    std::vector<std::string> add;
    std::vector<std::string> remove;
} Operation;

typedef struct Problem {
    std::vector<std::string> start;
    std::vector<std::string> finish;
    std::vector<Operation> operators;

    Problem(std::vector<std::string> begin, std::vector<std::string> end,
            std::vector<Operation> actions)
        : start(begin), finish(end), operators(actions) {}
    Problem() {}
} Problem;

#endif
