#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../src/tsp/farthestinsertiontsp.h"
#include "../src/tsp/weightedgraph.h"
#include "../src/tsp/weightedgraphtextfilereader.h"

#include <fstream>

TEST_CASE( "Farthest Insertion TSP works", "[tsp]" ) {

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

    REQUIRE( graph->size() == 5 );
    //adding edge creates 2 edges - one for first node and one for second node
    REQUIRE( graph->edgesSize() == 20 );

    long graphEdgesWeight = graph->totalEdgesWeight();

    FarthestInsertionTSP tsp_solver(std::move(graph));

    SECTION( "farthest insertion algorithm executes without exception" ) {
        REQUIRE_NOTHROW(tsp_solver.execute());
    }

    SECTION( "after executing resulting graph has 10 edges" ) {
        tsp_solver.execute();

        REQUIRE( tsp_solver.getResultGraph().edgesSize() == 10 );

    }

    SECTION( "resulting solution edges weight is optimal" ) {
        tsp_solver.execute();

        REQUIRE( tsp_solver.getTourWeight() == 1220 );
    }

    SECTION( "resulting solution edges weight is less than total input edge weight" ) {
        tsp_solver.execute();
        REQUIRE( tsp_solver.getTourWeight() < graphEdgesWeight );
    }
}

TEST_CASE( "WeightedGraphTextFileReader works", "[input][graph][tsp]") {
    std::ifstream file ("test_graph.txt");
    REQUIRE( file.is_open() );
    WeightedGraph graphFromFile = WeightedGraphTextFileReader::createFromStream(file);
    WeightedGraph graph;
    graph.addNode("a");
    graph.addNode("b");
    graph.addNode("c");
    graph.addNode("d");
    graph.addNode("e");
    graph.addEdge("a", "b", 500);
    graph.addEdge("a", "c", 200);
    graph.addEdge("a", "d", 185);
    graph.addEdge("a", "e", 205);
    graph.addEdge("b", "c", 305);
    graph.addEdge("b", "d", 360);
    graph.addEdge("b", "e", 340);
    graph.addEdge("c", "d", 320);
    graph.addEdge("c", "e", 165);
    graph.addEdge("d", "e", 302);
    REQUIRE( graphFromFile.toString() == graph.toString() );
}

//TEST_CASE( "AsyncTSPRunner works", "[async][tsp]") {
//    std::unique_ptr<WeightedGraph> graph = std::make_unique<WeightedGraph>();
//    graph->addNode("a");
//    graph->addNode("b");
//    graph->addNode("c");
//    graph->addNode("d");
//    graph->addNode("e");
//    graph->addEdge("a", "b", 500);
//    graph->addEdge("a", "c", 200);
//    graph->addEdge("a", "d", 185);
//    graph->addEdge("a", "e", 205);
//    graph->addEdge("b", "c", 305);
//    graph->addEdge("b", "d", 360);
//    graph->addEdge("b", "e", 340);
//    graph->addEdge("c", "d", 320);
//    graph->addEdge("c", "e", 165);
//    graph->addEdge("d", "e", 302);
//}
