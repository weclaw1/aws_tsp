#ifndef NODE_H
#define NODE_H

#include<vector>
#include<memory>

class Node;

struct Edge {
    Edge(const std::shared_ptr<Node> &node, const int weight) : node(node), weight(weight) {}
    Edge() : weight(0) {}
    std::weak_ptr<Node> node;
    int weight;
};

struct Node {
    Node() : name("") {}
    Node(const std::string &name) : name(name) {}
    Node(const std::string &name, const std::vector<Edge> &edges) : name(name), edges(edges) {}
    std::string name;
    std::vector<Edge> edges;
};

#endif // NODE_H
