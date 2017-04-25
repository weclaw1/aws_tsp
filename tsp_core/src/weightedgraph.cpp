#include "weightedgraph.h"
#include <stdexcept>
#include <iostream>

WeightedGraph::WeightedGraph(std::vector<std::shared_ptr<Node> > &nodes)
{
    sizeOfGraph = nodes.size();
    for(auto &node : nodes) {
        nodesMap[node->name] = node;
    }
}

WeightedGraph::WeightedGraph()
{
    sizeOfGraph = 0;
}

std::map<std::string, std::shared_ptr<Node> > WeightedGraph::getNodesMap() const
{
    return nodesMap;
}

std::size_t WeightedGraph::size()
{
    return sizeOfGraph;
}

bool WeightedGraph::contains(const std::__cxx11::string &name)
{
    if(nodesMap.count(name) > 0) {
        return true;
    }
    return false;
}

bool WeightedGraph::nodesHaveEdge(const std::string &firstNode, const std::string &secondNode)
{
    std::shared_ptr<Node> nodeFrom = nodesMap.at(firstNode);
    std::shared_ptr<Node> nodeTo = nodesMap.at(secondNode);
    for(Edge &edge : nodeFrom->edges) {
        if(edge.node->name == nodeTo->name) {
            return true;
        }
    }
    return false;
}

int WeightedGraph::edgeWeight(const std::__cxx11::string &from, const std::__cxx11::string &to)
{
    std::shared_ptr<Node> nodeFrom = nodesMap.at(from);
    std::shared_ptr<Node> nodeTo = nodesMap.at(to);
    for(Edge &edge : nodeFrom->edges) {
        if(edge.node->name == nodeTo->name) {
            return edge.weight;
        }
    }
    throw std::out_of_range(from + " does not have edge to " + to);
}

void WeightedGraph::print()
{
    for(auto &node : nodesMap) {
        if(node.second == nullptr) {
            continue;
        }
        std::cout << node.first << " - ";
        for(Edge &edge : node.second->edges) {
            std::cout << "( " << edge.weight << "->" << edge.node->name << " )";
        }
        std::cout << std::endl;
    }
}

void WeightedGraph::addNode(const std::string &name)
{
    nodesMap[name] = std::make_shared<Node>(Node(name));
    sizeOfGraph++;
}

void WeightedGraph::removeNode(const std::__cxx11::string &name)
{
    nodesMap.erase(name);
    sizeOfGraph--;
}

void WeightedGraph::addEdge(const std::string &firstNode, const std::string &secondNode, int weight)
{
    nodesMap.at(firstNode)->edges.push_back(Edge(nodesMap.at(secondNode), weight));
    nodesMap.at(secondNode)->edges.push_back(Edge(nodesMap.at(firstNode), weight));
}

void WeightedGraph::removeEdge(const std::string &firstNode, const std::string &secondNode)
{
    for(int i = 0; i < nodesMap.at(firstNode)->edges.size(); i++) {
        if(nodesMap.at(firstNode)->edges[i].node->name == secondNode) {
            nodesMap.at(firstNode)->edges.erase(nodesMap.at(firstNode)->edges.begin()+i);
            break;
        }
    }
    for(int i = 0; i < nodesMap.at(secondNode)->edges.size(); i++) {
        if(nodesMap.at(secondNode)->edges[i].node->name == firstNode) {
            nodesMap.at(secondNode)->edges.erase(nodesMap.at(secondNode)->edges.begin()+i);
            break;
        }
    }

}
