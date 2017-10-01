//
// Created by luca on 28/09/17.
//

#include <cmath>
#include "dijkstra.h"


/*
for each vertex v in Gw do
dist[v] ← INFINITY
        dist[s] = 0
while Gw not empty do
u ← vertex in Gw with min dist[u]
for each neighbor v of u do
alt ← dist[u] + wu,v
if alt < dist[v] then . Found a shorter path to v
dist[v] ← alt
        prev[v] ← u
        output u
        remove u from Gw*/


int executeDijkstra(unsigned int source, AdjacencyList &adjGraph, bool debug){



    if (source){
        source--; // adjust the source id to the array index (start from 0)

        fstream graphStream;

        if (!adjGraph.num_vertices){
            cout << time(nullptr) <<  "[Dijkstra] List is void. Aborting..." << endl;
            return -1;
        }

        auto* dist = new unsigned[adjGraph.num_vertices]();
        auto* marked = new bool[adjGraph.num_vertices]();  // mark already visited nodes;
        auto* parent = new unsigned[adjGraph.num_vertices](); // contain the previous visitated vertex
        unsigned nodes_to_visit = adjGraph.num_vertices;

        // initialize vertex dist
        for (unsigned int vertex=0; vertex<adjGraph.num_vertices; vertex++){
            dist[vertex]=0b11111111111111111111111111111111;
        }


        dist[source]=0;

        unsigned min_dist;
        unsigned closest_vertex; // store the id of the vertex with the less
        unsigned int alt_path;   // variable to probe alternative paths for the neighbours of the closest vertex (contains the distance through that path)
        unsigned int neigh_id;   // contains the id of the current neighbour of the closest vertex

        // cycle over all the nodes in the graph until all has been marked
        while (nodes_to_visit){

            min_dist = 0b11111111111111111111111111111111; // reset to search another minimum
            closest_vertex = source;

            // find the non marked vertex with the minimum distance (from source)
            for (unsigned int index=0; index<adjGraph.num_vertices; index++) {
                if (!marked[index] && dist[index] < min_dist) {
                    min_dist = dist[index];
                    closest_vertex = index;
                }
            }

            // cycle on the neighbours of the closest neighbour and update distance
            for (unsigned int n_index = adjGraph.getFirstNeighbourId(closest_vertex); n_index<adjGraph.getLastNeighbourId(closest_vertex); n_index++){
                neigh_id = adjGraph.neighbours_list[n_index];
                if (!marked[neigh_id]){
                    alt_path = min_dist + adjGraph.weights_list[n_index];
                    if (alt_path < dist[neigh_id]){
                        dist[neigh_id] = alt_path;
                        parent[neigh_id] = closest_vertex;
                    }
                }
            }


            cout << closest_vertex;
            marked[closest_vertex]=true;    // mark the closest neighbour from the list, so next time it will be skipped
            nodes_to_visit--;               // decrease the number of nodes to visit


            cout << endl;
            if (debug){
                for (unsigned int index=0; index<adjGraph.num_vertices; index++) {
                    cout << marked[index] << " ";
                }

                cout << endl;
            }

        }
    }






    return 0;
}

