//
// Created by Andrea Ferlini on 28/09/2017.
//

#include "bfs.h"


// BFS from a given source
int printBFS(unsigned int source, AdjacencyList &adjGraph, bool debug){

    list <unsigned int> fifo;
    //list <unsigned int>::iterator itr;
    unsigned int it=0;
    unsigned int output_node=0;
    unsigned int target_neighbour=0;

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

//        cout << "BFS";
        cout << output_node+1 << " ";

        if (debug)
            cout << endl << "[BFS Tree] - iterating " << output_node+1 << "'s neighbours ..." << endl;


        for (it = adjGraph.list_beginning[output_node]; it < (adjGraph.list_beginning[output_node] + adjGraph.adjNodesDegree.degree_array[output_node]); it++) {

            target_neighbour = adjGraph.neighbours_list[it];

            if (!visited[target_neighbour-1]) {
                if (debug)
                    cout << "[BFS Tree creation] - neighbour #" << it << ": " << target_neighbour << endl;

                fifo.push_back(target_neighbour - 1);
                visited[target_neighbour - 1] = true;
            }
        }

        cout << endl;

    }
    delete [] visited;
    return 0;
}