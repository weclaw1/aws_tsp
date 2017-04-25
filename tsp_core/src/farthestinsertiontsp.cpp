#include "farthestinsertiontsp.h"

#include <random>
#include <iterator>
#include <climits>

void FarthestInsertionTSP::execute()
{
    init();
    while(result.size() != inputGraph->size()) {
        std::string maxDistNode = this->maxDistNode();
        insertWithMinimumCost(maxDistNode);
    }
}

WeightedGraph FarthestInsertionTSP::getResultGraph()
{
    return result;
}

int FarthestInsertionTSP::getTourWeight() const
{
    return tourWeight;
}

std::shared_ptr<Node> FarthestInsertionTSP::getRandomNode()
{
    std::uniform_int_distribution<int> distribution(0,inputGraph->size()-1);
    auto randomIterator = std::next(std::begin(inputGraph->getNodesMap()), distribution(rng));
    return randomIterator->second;
}

void FarthestInsertionTSP::init()
{
    std::string randomNode = getRandomNode()->name;
    result.addNode(randomNode);
    removed.insert(randomNode);
}

std::string FarthestInsertionTSP::maxDistNode()
{
    int maxDist = INT_MIN;
    std::string maxDistNode;
    for(auto &node : inputGraph->getNodesMap()) {
        if(removed.count(node.first) > 0) {
            continue;
        }
        for(Edge &edge : node.second->edges) {
            if(result.contains(edge.node->name) && edge.weight > maxDist) {
                maxDist = edge.weight;
                maxDistNode = node.first;
            }
        }
    }
    return maxDistNode;
}

void FarthestInsertionTSP::insertWithMinimumCost(const std::string &maxDistNode)
{
    int lowestCost = INT_MAX;
    std::string nodeFrom;
    std::string nodeTo;
    int nodeFromDist, nodeToDist;

    if(result.size() == 1) {
        for(Edge &edge : inputGraph->getNodesMap()[maxDistNode]->edges) {
            if(result.contains(edge.node->name)) {
                nodeFrom = edge.node->name;
                nodeFromDist = edge.weight;
            }
        }
        result.addNode(maxDistNode);
        result.addEdge(nodeFrom, maxDistNode, nodeFromDist);
        removed.insert(maxDistNode);
        tourWeight = 2 * nodeFromDist;
        return;
    }

    for(auto &node : result.getNodesMap()) {
        for(Edge &edge : node.second->edges) {
            if(inputGraph->nodesHaveEdge(node.first, maxDistNode) && inputGraph->nodesHaveEdge(edge.node->name, maxDistNode)) {
                int cost = inputGraph->edgeWeight(node.first, maxDistNode) + inputGraph->edgeWeight(edge.node->name, maxDistNode) -
                        edge.weight;
                if(cost < lowestCost) {
                    lowestCost = cost;
                    nodeFrom = node.first;
                    nodeTo = edge.node->name;
                    nodeFromDist = inputGraph->edgeWeight(node.first, maxDistNode);
                    nodeToDist = inputGraph->edgeWeight(edge.node->name, maxDistNode);
                }
            }
        }
    }

    if(result.size() > 2) {
        result.removeEdge(nodeFrom, nodeTo);
    }
    result.addNode(maxDistNode);
    result.addEdge(nodeFrom, maxDistNode, nodeFromDist);
    result.addEdge(nodeTo, maxDistNode, nodeToDist);
    removed.insert(maxDistNode);
    tourWeight += lowestCost;
}

