#include "weightedgraphtextfilereader.h"
#include <sstream>

WeightedGraphTextFileReader::WeightedGraphTextFileReader()
{

}

WeightedGraph WeightedGraphTextFileReader::createFromStream(std::istream &instream)
{
    WeightedGraph newGraph;
    std::vector<std::string> nodeNameVector;

    std::string nodeNames;
    getline(instream, nodeNames);
    std::istringstream nodeNamesStream(nodeNames);
    std::string nodeName;
    while(nodeNamesStream >> nodeName)
    {
        nodeNameVector.push_back(nodeName);
        newGraph.addNode(nodeName);
    }

    std::string row;
    int rowIndex = 0;

    while(getline(instream, row))
    {
        std::istringstream rowStrStream(row);
        int dist;
        int columnIndex = 0;
        while(rowStrStream >> dist)
        {
            if(dist != 0) {
                newGraph.addEdge(nodeNameVector[columnIndex], nodeNameVector[rowIndex], dist);
            }
            columnIndex++;
        }
        rowIndex++;
    }

    return newGraph;
}
