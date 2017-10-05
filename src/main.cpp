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

    int start, end;

    start = time(nullptr);


    //filename = "../graphs/3_conn_comp.graph";
    //filename = "../graphs/actor_collaboration.graph";
    //filename = "../graphs/roadNet_PA.graph";
    //filename = "../graphs/orkut_groupmemberships.graph"; // d=8.
    filename = "../graphs/wikipedia_link_en.graph";

    bool is_weighted = false;

    ifstream file(filename);
    if (!file.good())
        cout << "No such file... " << endl;

    cout << time(nullptr)-start << "] Cleaning file...";
    string command = "../graphs/clear_graph_file.sh " + filename;
    cout << command << endl;
    system(command.c_str());

    cout << time(nullptr)-start << "] Loading graph..." << endl;
    if (loadAdjListContiguous(filename, loadedGraph, is_weighted,debug))
        return -1;

    // cout << "[MAIN] - Print loaded graph" << endl;
    // loadedGraph.print(debug);

//    executeDijkstra(dijkstra_source, loadedGraph, debug);

//    auto *source_distances = new unsigned int [loadedGraph.num_vertices]; //array with all the distances from the source
//    if (bfs_source <= loadedGraph.num_vertices){
//        executeBFS(bfs_source, loadedGraph, source_distances, debug);
//    } else {
//        cout << "[ERROR] - wrong source" << endl;
//    }
    //cout << time(nullptr)-start << "] Estimating diameter..."<< endl;

    //cout << "Estimated graph diameter: " << graph_diameter << endl;

    // cout << time(nullptr)-start << "Print connected components...";
    // printConnectedGraph(loadedGraph);

    cout << time(nullptr)-start << "] Estimating diameter..."<< endl;
    cout << time(nullptr)-start << "] Diameter: " << estimateAccurateDiameter(loadedGraph,5);


//    delete [] source_distances;
    return 0;
}