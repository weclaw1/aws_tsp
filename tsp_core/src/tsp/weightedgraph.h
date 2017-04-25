#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include<vector>
#include<string>
#include<map>
#include<memory>

#include "node.h"

class WeightedGraph
{
public:
    WeightedGraph(std::vector<std::shared_ptr<Node>> &nodes);
    WeightedGraph();
    void addNode(const std::string &name);
    void removeNode(const std::string &name);
    void addEdge(const std::string &firstNode, const std::string &secondNode, int weight);
    void removeEdge(const std::string &firstNode, const std::string &secondNode);
    std::map<std::string, std::shared_ptr<Node> > getNodesMap() const;
    std::size_t size();
    bool contains(const std::string &name);
    bool nodesHaveEdge(const std::string &firstNode, const std::string &secondNode);
    int edgeWeight(const std::string &from, const std::string &to);
    void print();
private:
    std::map<std::string, std::shared_ptr<Node>> nodesMap;
    std::size_t sizeOfGraph;

};

#endif // WEIGHTEDGRAPH_H
