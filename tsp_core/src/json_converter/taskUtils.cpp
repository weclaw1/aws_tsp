#include "TaskUtils.h"
#include <string>
#include "tsp\weightedgraph.h"
#include "tsp\task.h"
#include <exception>

 Task TaskUtils::fromJson(nlohmann::json j)
{
	  const std::string token = " ";
	  WeightedGraph  graph;

	  Task  task(token,graph);


	  if (j.find("nodes") != j.end())
	  {
		  nlohmann::json nodes = j["nodes"];
		  if (!nodes.empty()) {
			  for (nlohmann::json::iterator it = nodes.begin(); it != nodes.end(); ++it)
			  {
				  graph.addNode((*it)["id"].get<std::string>());
			  }
		  }
	  }
	  else  throw std::invalid_argument("wrong format of json");


	  if (j.find("edges") != j.end())
	  {
		  nlohmann::json edges = j["edges"];
		  if (!edges.empty()) {

			  for (nlohmann::json::iterator it; it != edges.end(); ++it)
			  {
				  nlohmann::json edge = *it;
				  graph.addEdge(edge["from"].get<std::string>(), edge["to"].get<std::string>(), edge["length"].get<int>());
			  }
		  }
	  }else throw std::invalid_argument("wrong format of json");

	return task;

}

 nlohmann::json TaskUtils::toJson(TaskResult taskResult)
{
	nlohmann::json j;

	std::map<std::string, std::shared_ptr<Node>> map = taskResult.resultGraph.getNodesMap();

	if (!map.empty()) {
		j = nlohmann::json{ "nodes" , "edges" };
		for (std::map<std::string, std::shared_ptr<Node>> ::iterator it = map.begin(); it != map.end(); ++it)
		{
			std::shared_ptr<Node> node = it->second;

			j["nodes"].push_back({ "id", it->first });

			for (Edge &edge : node->edges)
			{
				nlohmann::json edgeJ ;

				j["edges"].push_back({
					{"from" , it->first} ,
					{"to" , edge.node.lock()->name} ,
					{"length", edge.weight}
				});

			}
		}
	}
	return j;
}
