#include <iostream>
#include "bfs.h"
#include "dijkstra.h"

int main() {

    string filename;

    AdjacencyList loadedGraph;

    unsigned int bfs_source = 5;
    unsigned int dijkstra_source = 5;
    unsigned int graph_diameter = 0;
    bool debug = false;

    //filename = "../graphs/sample_weighted.graph";
    filename = "../graphs/3_conn_comp.graph";

    bool is_weighted = false;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file... " << endl;

    if (loadAdjListContiguous(filename, loadedGraph, is_weighted,debug))
        return -1;

    cout << "[MAIN] - Print loaded graph" << endl;
    loadedGraph.print(debug);

//    executeDijkstra(dijkstra_source, loadedGraph, debug);

//    auto *source_distances = new unsigned int [loadedGraph.num_vertices]; //array with all the distances from the source
//    if (bfs_source <= loadedGraph.num_vertices){
//        executeBFS(bfs_source, loadedGraph, source_distances, debug);
//    } else {
//        cout << "[ERROR] - wrong source" << endl;
//    }

    //graph_diameter = estimateDiameter(loadedGraph, 5, debug);

    //cout << "Estimated graph diameter: " << graph_diameter << endl;

    printConnectedGraph(loadedGraph);

//    delete [] source_distances;
    return 0;
}