#include <iostream>
#include <memory>

#include "tsp/farthestinsertiontsp.h"
#include "tsp/weightedgraph.h"
#include "tsp/node.h"

int main()
{
  std::unique_ptr<WeightedGraph> graph = std::make_unique<WeightedGraph>();
  graph->addNode("a");
  graph->addNode("b");
  graph->addNode("c");
  graph->addNode("d");
  graph->addNode("e");
  graph->addEdge("a", "b", 500);
  graph->addEdge("a", "c", 200);
  graph->addEdge("a", "d", 185);
  graph->addEdge("a", "e", 205);
  graph->addEdge("b", "c", 305);
  graph->addEdge("b", "d", 360);
  graph->addEdge("b", "e", 340);
  graph->addEdge("c", "d", 320);
  graph->addEdge("c", "e", 165);
  graph->addEdge("d", "e", 302);
  FarthestInsertionTSP tsp_solver(std::move(graph));
  tsp_solver.execute();
  tsp_solver.getResultGraph().print();
  std::cout<< tsp_solver.getTourWeight();
  return 0;
}
