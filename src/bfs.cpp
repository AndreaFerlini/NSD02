//
// Created by Andrea Ferlini on 28/09/2017.
//

#include "bfs.h"


// BFS from a given source
int executeBFS(unsigned int source, AdjacencyList &adjGraph, unsigned int *distance_array, bool debug){

    list <unsigned int> fifo;
    unsigned int it=0;
    unsigned int output_node=0;
    unsigned int target_neighbour=0;
    unsigned int temp_vertex;
    unsigned int bfs_index = 0;

    auto *parent_array = new unsigned int [adjGraph.num_vertices];
    auto *bfs = new unsigned int [adjGraph.num_vertices];

    distance_array = new unsigned int [adjGraph.num_vertices]();

    // Mark all the nodes as not visited
    bool *visited = new bool [adjGraph.num_vertices]();

    if (debug){
        for (unsigned int i=0; i < adjGraph.num_vertices; i++){
            cout << visited[i] << endl;
            // visited[i] = false;
        }
    }

    // Mark the source as visited and push it @ the end of the fifo
    visited[source-1] = true;
    fifo.push_back(source-1);

    if (debug){
        cout << "[BFS Tree] - parsing the fifo ..." << "size of the fifo " << fifo.size() << endl;
    }
    cout << endl << "Printing the BFS starting from " << source << endl;
    while (!fifo.empty()){
        output_node = fifo.front();

        fifo.pop_front();

        bfs[bfs_index] = output_node;
        bfs_index++;

        if (debug)
            cout << endl << "[BFS Tree] - iterating " << output_node+1 << "'s neighbours ..." << endl;

        for (it = adjGraph.getFirstNeighbourId(output_node); it < (adjGraph.getLastNeighbourId(output_node)); it++) {

            target_neighbour = adjGraph.neighbours_list[it];

            if (!visited[target_neighbour-1]) {
                if (debug)
                    cout << "[BFS Tree creation] - neighbour #" << it << ": " << target_neighbour << endl;

                fifo.push_back(target_neighbour - 1);
                visited[target_neighbour - 1] = true;
                parent_array[target_neighbour-1] = output_node+1;
                // TODO: vedere se ti va bene così
                distance_array[target_neighbour] = distance_array[output_node]+1;
            }
        }
        //cout << endl;
    }

//    for (unsigned int i=0; i < adjGraph.num_vertices; i++){
//        distance_array[i]=0;
//        temp_vertex = i;
//        while (temp_vertex != source-1){
//            distance_array[i]++;
//            temp_vertex = parent_array[temp_vertex]-1;
//        }
//    }

    if (debug){
        for (unsigned int  x = 0;  x < adjGraph.num_vertices; ++ x) {
            cout << "Node " << x+1 << " has parent " << parent_array[x] << " and distance " << distance_array[x] << endl;
        }
    }

    for (bfs_index=0; bfs_index<adjGraph.num_vertices; bfs_index++){
        cout << bfs[bfs_index]+1 << " (" << distance_array[bfs[bfs_index]] << ")"<<endl;
    }


    delete [] visited;
    delete [] parent_array;
    //delete [] distance_array;
    delete [] bfs;
    return 0;
}

unsigned int estimateDiameter(AdjacencyList &adjGraph, int convergence_th, bool debug){

    unsigned int diameter=0;
    unsigned int new_diameter=0;
    unsigned int source_new_bfs=0;

    //unsigned int *distance_array = nullptr;
    auto *distance_array = new unsigned int [adjGraph.num_vertices]();

    int counter = 0;

    srand ((unsigned int)time(nullptr));
    source_new_bfs = rand() % adjGraph.num_vertices + 1;

    executeBFS(source_new_bfs, adjGraph, distance_array, debug);

    if (distance_array == nullptr) {
        cout << "[estimateDiameter] - ERROR in loading distance array" << endl;
        return 0;
    }

    for (unsigned int i=0; i < adjGraph.num_vertices; i ++){
        if (distance_array[i]>=diameter){
            diameter = distance_array[i];
            source_new_bfs = i+1;
        }
    }

    while (counter < convergence_th){
        cout << "[estimateDiameter] - diameter: " << diameter << endl;
        executeBFS(source_new_bfs, adjGraph, distance_array, debug);
        for (unsigned int i=0; i < adjGraph.num_vertices; i ++){
            if (distance_array[i]>=new_diameter){
                new_diameter = distance_array[i];
                source_new_bfs = i+1;
            }
        }
        if (diameter == new_diameter){
            counter ++;
        }else if(new_diameter > diameter){
            diameter = new_diameter;
            counter = 0;
        }
    }

    delete [] distance_array;
    return diameter;
}