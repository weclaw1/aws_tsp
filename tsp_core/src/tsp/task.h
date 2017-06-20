#ifndef TASK_H
#define TASK_H

#include<string>
#include "weightedgraph.h"

struct Task {
    Task() {}
    Task(const std::string &token, WeightedGraph inputGraph) : token(token), inputGraph(inputGraph) {}
    std::string token;
    WeightedGraph inputGraph;
};

struct TaskResult {
    TaskResult() {}
    TaskResult(const std::string &token, WeightedGraph resultGraph) : token(token), resultGraph(resultGraph) {}
    std::string token;
    WeightedGraph resultGraph;
};

#endif // TASK_H
