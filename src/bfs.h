//
// Created by Andrea Ferlini on 28/09/2017.
//

#ifndef PRACTICAL2_BFS_H
#define PRACTICAL2_BFS_H

#include "loadgraph.h"
#include <vector>

/// FUNCTIONS

int executeBFS(unsigned int source, AdjacencyList &adjGraph, unsigned int *distance_array, unsigned int& n_visited,  bool debug);

unsigned int estimateDiameter(AdjacencyList &adjGraph, unsigned int source=0, int convergence_th=2, bool debug = false);

int printConnectedGraph(AdjacencyList &adjGraph, bool debug = false);

int estimateAccurateDiameter(AdjacencyList &adjGraph,int convergence_th=2, bool debug = false);

#endif //PRACTICAL2_BFS_H
