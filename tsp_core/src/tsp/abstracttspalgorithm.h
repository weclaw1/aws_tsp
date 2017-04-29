#ifndef ABSTRACTTSPALGORITHM_H
#define ABSTRACTTSPALGORITHM_H

#include "weightedgraph.h"

class AbstractTSPAlgorithm
{
    public:
        virtual ~AbstractTSPAlgorithm() {}
        virtual void execute() = 0;
        virtual WeightedGraph getResultGraph() = 0;
        virtual int getTourWeight() const = 0;
};

#endif // ABSTRACTTSPALGORITHM_H
