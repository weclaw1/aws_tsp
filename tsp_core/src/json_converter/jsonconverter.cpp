#include "jsonconverter.h"
#include "tsp\task.h"
#include <exception>
JsonConverter::JsonConverter()
{

}
TaskResult JsonConverter::fromJson(nlohmann::json j)
{
	const std::string token = " ";
    WeightedGraph graph;

	nlohmann::json nodes = j["nodes"];
	nlohmann::json edges = j["edges"];

	if (!nodes.empty() && !edges.empty()){

		addNodeToGraph(nodes,graph);
		addEdgeToGraph(edges, graph);

		if (!completeGraph(graph))
			throw std::invalid_argument("graph is not complete");

	}
	else throw std::invalid_argument("inavlid graph");

	return TaskResult(token,graph);
}

nlohmann::json JsonConverter::toJson(TaskResult taskResult)
{
	nlohmann::json j=TaskResult::toJson(taskResult);
	return j;

}



void JsonConverter::addNodeToGraph(nlohmann::json nodes, WeightedGraph graph)
{
	for (nlohmann::json::iterator it; it != nodes.end(); ++it){
		std::string nodeId = (*it)["id"].get<std::string>();
		graph.addNode(nodeId);
	}
}

void JsonConverter::addEdgeToGraph(nlohmann::json edges, WeightedGraph graph)
{
	for (nlohmann::json::iterator it; it != edges.end(); ++it) {

		const std::string from = (*it)["from"].get<std::string>();
		const std::string to = (*it)["to"].get<std::string>();

		if (graph.contains(from) && graph.contains(to) && from != to) {
			if ((*it)["length"].get<int>() >= 0) {
				graph.addEdge(from, to, (*it)["length"].get<int>());
			}
		}
	}
}

bool JsonConverter::completeGraph(WeightedGraph graph)
{
	const int n = graph.size();

	if (graph.edgesSize() == (n*(n - 1)) / 2) return true;
	else return false;
}