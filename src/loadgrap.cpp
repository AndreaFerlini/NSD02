//
// Created by Andrea Ferlini on 26/09/2017.
//

#include "loadgrap.h"

int loadAdjListContiguous(string filename, bool debug){
    fstream graph;
    NodeDegree nodesDegree;
    unsigned int tot_degree = 0;
    unsigned int cursor = 0;

    // Compute the degree of the graph
    graphDegree(filename, nodesDegree);

    
    // Sum the degree of every node 
    for (unsigned int i=0; i < nodesDegree.graph_size; i++){
        tot_degree += nodesDegree.degree_array[i];
    }

    unsigned int* neighbours_list = new unsigned int[tot_degree];   // List of neighbours in a compact way

    // Contains the index of the neighbours_list where the list of neighbours (of the i node) starts
    unsigned int* list_beginning = new unsigned int[nodesDegree.graph_size]();  

    // Initialize list_beginning to point at the beginning of their list
    for (unsigned int node_idx=0; node_idx < nodesDegree.graph_size; node_idx++){
        list_beginning[node_idx] = cursor;
        cursor += nodesDegree.degree_array[node_idx];
    }

    if(debug) cout << time(nullptr) <<  "[Compact Adjacency List] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << time(nullptr) << "[Compact Adjacency List] Succeed! Building Adjacency List..." << endl;

        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;

            if(node)
                neighbours_list[list_beginning[node-1]] = neighbour;
                list_beginning[node-1]++;  // Increase the cursor by one so the next time i will write the next neighbour in the correct position

            if(neighbour)
                neighbours_list[list_beginning[neighbour-1]] = node;
                list_beginning[neighbour-1]++;// Increase the cursor by one so the next time i will write the next neighbour in the correct position
        }

        // reset to the original beginning position (going backwards of a nr of steps equal to the degree of the node)
        for (unsigned int node_idx=0; node_idx < nodesDegree.graph_size; node_idx++){
            list_beginning[node_idx] -= nodesDegree.degree_array[node_idx];
        }

        if(debug) cout << time(nullptr) << "[Compact Adjacency List]  Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug) {
            cout << "  Node\t\tNeighbours" << endl;
            cout << "  ----------------------------" << endl;
            for (unsigned int node = 0; node < nodesDegree.graph_size; node++) {
                cout << node + 1 << " -> ";
                for (unsigned int neigh_index = 0; neigh_index<nodesDegree.degree_array[node]; neigh_index++) {
                    cout << neighbours_list[list_beginning[node]+neigh_index] << " ";
                }
                cout << endl;
            }
        }
        graph.close();
    }else{
        cout << "[Compact Adjacency List] Error! Unable to open the file " << filename << endl;
        return -1;
    }

    delete[] list_beginning;
    delete[] neighbours_list;

    return 0;
}

// Calculate the number of nodes and edges
int graphSize(string filename, unsigned int &num_nodes, unsigned int &num_edges, bool debug){
    if (debug) cout << time(nullptr) << "[Graph graph_size] Begin..." << endl;
    
    fstream graph;
    num_nodes = 0;
    num_edges = 0;
    
    if(debug) cout << time(nullptr) <<  "[Graph graph_size] Opening the file..." << endl;
    graph.open(filename, ios::in);
    
    if (graph.is_open()){

        if(debug) cout << time(nullptr) <<  "[Graph graph_size] Succeed! Counting..." << endl;

        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            num_edges++;
            if (node > num_nodes){
                num_nodes = node;
            }
            if (neighbour > num_nodes){
                num_nodes = neighbour;
            }
        }

        if(debug) cout << time(nullptr) << "[Graph graph_size] Done!" << endl;
        graph.close();
    }else{
        cout << "[Graph graph_size] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}

// Calculate the degree of each node
// This function build an degree_array in which stores the number of neighbours per node. At index 0 there is the first node (ID=1)
int graphDegree(string filename, NodeDegree& nodesDegree, bool debug){
    if (debug) cout << time(nullptr) << "[Graph Degree] Begin..." << endl;
    
    unsigned int num_edges;
    int node, neighbour;
    fstream graph;
    
    // Compute the size of the graph
    if (graphSize(filename, nodesDegree.graph_size, num_edges, debug))
        return -1;

    nodesDegree.degree_array = new int[nodesDegree.graph_size]();
    
    if (debug) cout << time(nullptr) << "[Graph Degree] Opening the file..." << endl;
    graph.open(filename, ios::in);

    if (graph.is_open()){
        
        if(debug) cout << time(nullptr) << "[Graph Degree] Succeed! Counting neigbours..." << endl;
        
        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            
            // Increase the degree of the node
            if (node)
                nodesDegree.degree_array[node-1]++;
            // Increase the degree of the neighbour
            if (neighbour)
                nodesDegree.degree_array[neighbour-1]++;
        }
        /// DEBUG
        if (debug){
            cout << time(nullptr) << "[Graph Degree] Finished! Output:" << endl;
            cout << "  ID\tDegree" << endl;
            cout << "  ---------------------------" << endl;
            nodesDegree.print();
        }
        graph.close();
    }else{
        cout << time(nullptr) << "[Graph Degree] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}