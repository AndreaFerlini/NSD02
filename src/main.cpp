#include <iostream>
#include "bfs.h"

int main() {

    string filename;
    bool debug = false;
    AdjacencyList loadedGraph;
    unsigned int bfs_source = 5;

    filename = "../graphs/sample.graph";

    ifstream file(filename);
    if (!file.good())
        cout << "No such file... " << endl;

    if (loadAdjListContiguous(filename, loadedGraph, debug))
        return -1;

    loadedGraph.print(debug);

    if (bfs_source <= loadedGraph.num_vertices){
        printBFS(bfs_source, loadedGraph, debug);
    } else {
        cout << "[ERROR] - wrong source";
    }

    return 0;
}