#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <json.hpp>
#include "tsp\task.h"

class JsonConverter
{
public:
    JsonConverter();
	TaskResult fromJson(nlohmann::json j);
	nlohmann::json toJson(TaskResult taskResult);
	void addNodeToGraph(nlohmann::json, WeightedGraph&);
	void addEdgeToGraph(nlohmann::json, WeightedGraph&);
	bool completeGraph(WeightedGraph);
};

#endif // JSONCONVERTER_H
