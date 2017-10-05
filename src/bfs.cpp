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
    unsigned int component_size = 0;

    //auto *parent_array = new unsigned int [adjGraph.num_vertices];
    auto *bfs = new unsigned int [adjGraph.num_vertices];

    // Mark all the nodes as not visited (the first element of visited (visited[0]) counts the visited nodes
    auto* visited = new bool [adjGraph.num_vertices]();

//    if (debug){
//        for (unsigned int i=0; i < adjGraph.num_vertices; i++){
//            cout << visited[i] << endl;
//            // visited[i] = false;
//        }
//    }

    // Mark the source as visited and push it @ the end of the fifo
    visited[source-1] = true;
    fifo.push_back(source-1);

    if (debug){
        cout << "[BFS Tree] - parsing the fifo ..." << "size of the fifo " << fifo.size() << endl;
    }
    if (debug)
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
                visited[target_neighbour-1] = true;
                //parent_array[target_neighbour-1] = output_node+1;
                distance_array[target_neighbour-1] = distance_array[output_node]+1;
            }
        }
        //cout << endl;
    }
    component_size = bfs_index;

    if (debug){
        for (unsigned int  x = 0;  x < adjGraph.num_vertices; ++ x) {
            //cout << "Node " << x+1 << " has parent " << parent_array[x] << " and distance " << distance_array[x] << endl;
        }
    }
    if (debug){
        for (bfs_index=0; bfs_index<component_size; bfs_index++){
            cout << bfs[bfs_index]+1 << " (" << distance_array[bfs[bfs_index]] << ")"<<endl;
        }
        cout << "The size of the connected component is: " << component_size << endl;
    }




    delete [] visited;
    //delete [] parent_array;
    delete [] bfs;
    return 0;
}

unsigned int estimateDiameter(AdjacencyList &adjGraph, unsigned int source,  int convergence_th, bool debug){

    unsigned int diameter=0;
    unsigned int new_diameter=0;
//    unsigned int source_new_bfs=0;

    //unsigned int *distance_array = nullptr;
    auto *distance_array = new unsigned int [adjGraph.num_vertices]();

    int counter = 0;

    if (!source){
        srand ((unsigned int)time(nullptr));
        source = rand() % adjGraph.num_vertices + 1;
    }


    if (debug)
        cout << "[estimateDiameter] - first bfs: " << endl;

    executeBFS(source, adjGraph, distance_array, debug);

    if (distance_array == nullptr) {
        cout << "[estimateDiameter] - ERROR in loading distance array" << endl;
        return 0;
    }

    for (unsigned int i=0; i < adjGraph.num_vertices; i ++){
        if (distance_array[i]>=diameter){
            diameter = distance_array[i];
            source = i+1;
        }
    }

    while (counter < convergence_th){

        if (debug)
            cout << "[estimateDiameter] - Dimeter duplicate #" << counter << endl;

        // reset distance array
        for (unsigned int i=0; i < adjGraph.num_vertices; i ++){
            distance_array[i]=0;
        }

        if (debug)
            cout << "[estimateDiameter] - diameter: " << diameter << endl;

        executeBFS(source, adjGraph, distance_array, debug);
        for (unsigned int i=0; i < adjGraph.num_vertices; i ++){
            if (distance_array[i]>=new_diameter){
                new_diameter = distance_array[i];
                source = i+1;
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



int printConnectedGraph(AdjacencyList &adjGraph, bool debug){
    bool* visited;
    unsigned int n_visited=0;

    unsigned int source=1;
    unsigned int component_counter=1;

    list <unsigned int> fifo;
    unsigned int it=0;
    unsigned int output_node=0;
    unsigned int target_neighbour=0;
    unsigned int bfs_index = 0;
    unsigned int component_size = 0;


    //auto *parent_array = new unsigned int [adjGraph.num_vertices];
    unsigned int *bfs = new unsigned int [adjGraph.num_vertices];


    // Mark all the nodes as not visited (the first element of visited (visited[0]) counts the visited nodes
    visited = new bool [adjGraph.num_vertices]();

    do{
        bfs_index=0;
        cout << endl << "Connected Component #" << component_counter << endl;
        cout << "------------------------------------" << endl;


        // Mark the source as visited and push it @ the end of the fifo
        visited[source-1] = true;
        n_visited++;
        fifo.push_back(source-1);

        if (debug){
            cout << "[BFS Tree] - parsing the fifo ..." << "size of the fifo " << fifo.size() << endl;
        }
        cout << "Printing the BFS starting from " << source << endl;
        while (!fifo.empty()){
            output_node = fifo.front();

            fifo.pop_front();

            bfs[bfs_index] = output_node;
            bfs_index++;

            if (debug)
                cout << "[BFS Tree] - iterating " << output_node+1 << "'s neighbours ..." << endl;

            for (it = adjGraph.getFirstNeighbourId(output_node); it < (adjGraph.getLastNeighbourId(output_node)); it++) {

                target_neighbour = adjGraph.neighbours_list[it];

                if (!visited[target_neighbour-1]) {
                    if (debug)
                        cout << "[BFS Tree creation] - neighbour #" << it << ": " << target_neighbour << endl;

                    fifo.push_back(target_neighbour - 1);
                    visited[target_neighbour-1] = true;
                    n_visited++;

                }
            }
            //cout << endl;
        }
        component_size = bfs_index;
        component_counter++;

        for (bfs_index=0; bfs_index<component_size; bfs_index++){
            cout << bfs[bfs_index]+1 <<endl;
        }
        cout << "The size of the connected component is: " << component_size << endl;

        // find the next source (first non visited vertex)
        source=1;
        while (visited[source-1]) {
            source++; // find the next one not visited;
        }

    } while (n_visited<adjGraph.num_vertices);  // cycle until all the nodes will be visited

    delete[] bfs;
    delete[] visited;
}


int estimateAccurateDiameter(AdjacencyList &adjGraph, int convergence_th, bool debug){
    bool* visited;
    unsigned int n_visited=0;
    auto *distance_array = new unsigned int [adjGraph.num_vertices]();
    unsigned int source=1;
    unsigned int component_counter=1;
//    AdjacencyList conn_comp;

    list <unsigned int> fifo;
    unsigned int it=0;
    unsigned int output_node=0;
    unsigned int target_neighbour=0;
    unsigned int bfs_index = 0;
    unsigned int component_size = 0;

    //auto *parent_array = new unsigned int [adjGraph.num_vertices];
    unsigned int *bfs = new unsigned int [adjGraph.num_vertices];

    unsigned int diameter=0;
    unsigned int new_diameter;


    // Mark all the nodes as not visited (the first element of visited (visited[0]) counts the visited nodes
    visited = new bool [adjGraph.num_vertices]();

//    // file to save subgrapf of connected component
//    fstream cc_file;
//    string cc_filename = "cc_temp.graph";
//    bool first_line=true;


    do{

        bfs_index=0;
        if (debug) {
            cout << endl << "Connected Component #" << component_counter << endl;
            cout << "------------------------------------" << endl;
        }

        // Mark the source as visited and push it @ the end of the fifo
        visited[source-1] = true;
        n_visited++;
        fifo.push_back(source-1);

        if (debug){
            cout << "[BFS Tree] - parsing the fifo ..." << "size of the fifo " << fifo.size() << endl;
            cout << "Printing the BFS starting from " << source << endl;
        }
//        if (debug)
//            cout << "-] Open file to werite cc" << endl;
//        cc_file.open(cc_filename, ios::out);
//        first_line=true;

        while (!fifo.empty()){
            output_node = fifo.front();
            fifo.pop_front();

            bfs[bfs_index] = output_node;
            bfs_index++;

            if (debug)
                cout << "[BFS Tree] - iterating " << output_node+1 << "'s neighbours ..." << endl;

            for (it = adjGraph.getFirstNeighbourId(output_node); it < (adjGraph.getLastNeighbourId(output_node)); it++) {

//                // write the neignbours in the file
//                if (!first_line){
//                    cc_file << endl;
//                } else {
//                    first_line = false;
//                }

//                cc_file << output_node+1 << " " << target_neighbour+1;

                target_neighbour = adjGraph.neighbours_list[it];

                if (!visited[target_neighbour-1]) {
                    if (debug)
                        cout << "[BFS Tree creation] - neighbour #" << it << ": " << target_neighbour << endl;

                    fifo.push_back(target_neighbour - 1);
                    visited[target_neighbour-1] = true;
                    n_visited++;


                }



            }
            //cout << endl;
        }
        component_size = bfs_index;
        component_counter++;

//        cc_file.close();

//        if (component_size>1){
//            loadAdjListContiguous(cc_filename, conn_comp, false, debug);
//            // conn_comp.print(debug);
//            new_diameter = estimateDiameter(conn_comp,2,debug);
//            if (new_diameter > diameter){
//                diameter = new_diameter;
//            }
//        }

        new_diameter = estimateDiameter(adjGraph,source,convergence_th,debug);
        if (new_diameter > diameter){
            diameter = new_diameter;
        }

        if (debug){
            for (bfs_index=0; bfs_index<component_size; bfs_index++){
                cout << bfs[bfs_index]+1 <<endl;
            }
        }
        if (debug)
            cout << "Connected component size: " << component_size << "  diameter: " << new_diameter << endl;

        // find the next source (first non visited vertex)
        source=1;
        while (visited[source-1]) {
            source++; // find the next one not visited;
        }

    } while (n_visited<adjGraph.num_vertices);  // cycle until all the nodes will be visited

    if (debug)
        cout << "Graph diameter: " << diameter << endl;


    delete[] distance_array;
    delete[] bfs;
    delete[] visited;

    cout << "   Connected components: " << component_counter << endl;

    return diameter;

}

