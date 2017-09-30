#include <iostream>
#include "bfs.h"
#include "dijkstra.h"

int main() {

    string filename;
    bool debug = true;
    AdjacencyList loadedGraph;
    unsigned int bfs_source = 5;
    unsigned int dijkstra_source = 5;

    filename = "../graphs/sample_weighted.graph";
    bool is_weighted = true;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file... " << endl;

    if (loadAdjListContiguous(filename, loadedGraph, is_weighted,debug))
        return -1;

    cout << "[MAIN] - Print loaded graph" << endl;
    loadedGraph.print(debug);

    executeDijkstra(dijkstra_source, loadedGraph, debug);

//    if (bfs_source <= loadedGraph.num_vertices){
//        printBFS(bfs_source, loadedGraph, debug);
//    } else {
//        cout << "[ERROR] - wrong source" << endl;
//    }

    return 0;
}