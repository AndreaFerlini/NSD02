//
// Created by Andrea Ferlini on 28/09/2017.
//

#ifndef PRACTICAL2_BFS_H
#define PRACTICAL2_BFS_H

#include "loadgraph.h"

/// FUNCTIONS
int executeBFS(unsigned int source, AdjacencyList &adjGraph, unsigned int *distance_array, bool debug = false);

unsigned int estimateDiameter(AdjacencyList &adjGraph, int convergence_th, bool debug = false);
#endif //PRACTICAL2_BFS_H
