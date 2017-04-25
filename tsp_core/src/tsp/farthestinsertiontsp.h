#ifndef FARTHESTINSERTIONTSP_H
#define FARTHESTINSERTIONTSP_H

#include "weightedgraph.h"
#include <chrono>
#include <string>
#include <set>

#include <random>

class FarthestInsertionTSP
{
public:
    FarthestInsertionTSP(std::unique_ptr<WeightedGraph> inputGraph)
        : inputGraph(std::move(inputGraph)), tourWeight(0),
          rng(std::chrono::system_clock::now().time_since_epoch().count()) { }
    void execute();
    WeightedGraph getResultGraph();

    int getTourWeight() const;

private:
    std::unique_ptr<WeightedGraph> inputGraph;
    WeightedGraph result;
    int tourWeight;
    std::shared_ptr<Node> getRandomNode();
    void init();
    std::string maxDistNode();
    void insertWithMinimumCost(const std::string &maxDistNode);
    std::set<std::string> removed;
    std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)
};

#endif // FARTHESTINSERTIONTSP_H
