#ifndef GPS_HPP
#define GPS_HPP

#include "problem.hpp"
#include <string>
#include <vector>

std::vector<std::string> gps(std::vector<std::string> initial_states,
                             std::vector<std::string> goal_states,
                             std::vector<Operation> &operators);

std::vector<std::string> achieve_all(std::vector<std::string> states,
                                     std::vector<Operation> &operators,
                                     std::vector<std::string> goals,
                                     std::vector<std::string> &goal_stack);

std::vector<std::string> achieve(std::vector<std::string> states,
                                 std::vector<Operation> operators,
                                 std::string goal,
                                 std::vector<std::string> &goal_stack);

std::vector<std::string> apply_operator(Operation operation,
                                        std::vector<std::string> states,
                                        std::vector<Operation> operators,
                                        std::string goal,
                                        std::vector<std::string> &goal_stack);

#endif
