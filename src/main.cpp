#include <iostream>
#include "loadgrap.h"

int main() {

    string filename;
    bool debug = false;
    AdjacencyList loadedGraph;
    unsigned int bfs_source = 5;

    filename = "../graphs/sample.graph";

    if (loadAdjListContiguous(filename, loadedGraph, debug))
        return -1;

    loadedGraph.print(debug);

    if (bfs_source <= loadedGraph.vertices){
        BFS(bfs_source, loadedGraph, debug);
    } else {
        cout << "[ERROR] - wrong source";
    }

    return 0;
}