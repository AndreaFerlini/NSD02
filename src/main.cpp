#include <iostream>
#include "loadgrap.h"

int main() {

    string filename;
    bool debug = false;
    AdjacencyList loadedGraph;

    filename = "../graphs/sample.graph";

    if (loadAdjListContiguous(filename, loadedGraph, debug))
        return -1;

    loadedGraph.print(debug);

    return 0;
}