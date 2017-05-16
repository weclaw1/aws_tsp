#ifndef WEIGHTEDGRAPHTEXTFILEREADER_H
#define WEIGHTEDGRAPHTEXTFILEREADER_H


#include<iostream>
#include "weightedgraph.h"

class WeightedGraphTextFileReader
{
public:
    WeightedGraphTextFileReader();
    static WeightedGraph createFromStream(std::istream &instream);
};

#endif // WEIGHTEDGRAPHTEXTFILEREADER_H
