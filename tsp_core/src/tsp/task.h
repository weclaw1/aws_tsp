#ifndef TASK_H
#define TASK_H

#include<string>
#include "weightedgraph.h"
#include "json.hpp"

using json = nlohmann::json;

struct Task {
    Task(const std::string &token, WeightedGraph inputGraph) : token(token), inputGraph(inputGraph) {}
    std::string token;
    WeightedGraph inputGraph;

    static Task fromJson(nlohmann::json j);

};



struct TaskResult {

    TaskResult(const std::string &token, WeightedGraph resultGraph) : token(token), resultGraph(resultGraph) {}
    std::string token;
    WeightedGraph resultGraph;

    static nlohmann::json toJson(TaskResult taskResult) ;
};




#endif // TASK_H
