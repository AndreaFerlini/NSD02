//
// Created by Andrea Ferlini on 26/09/2017.
//

#include "loadgrap.h"

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
int computeDegree(string filename, GraphDegree &nodesDegree, bool debug){
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

// Loading the adjacency list & store it in memory
int loadAdjListContiguous(string filename, AdjacencyList& myList, bool debug){
    fstream graph;
    unsigned int cursor = 0;

    // Compute the degree of the graph
    computeDegree(filename, myList.adjNodesDegree, debug);
    myList.vertices = myList.adjNodesDegree.graph_size;

    // Sum the degree of every node
    for (unsigned int i=0; i < myList.vertices; i++){
        myList.size_neighbour_list += myList.adjNodesDegree.degree_array[i];
    }

    myList.neighbours_list = new unsigned int[myList.size_neighbour_list];   // List of neighbours in a compact way

    // Contains the index of the neighbours_list where the list of neighbours (of the i node) starts
    myList.list_beginning = new unsigned int[myList.vertices]();

    // Initialize list_beginning to point at the beginning of their list
    for (unsigned int node_idx=0; node_idx < myList.vertices; node_idx++){
        myList.list_beginning[node_idx] = cursor;
        cursor += myList.adjNodesDegree.degree_array[node_idx];
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
                myList.neighbours_list[myList.list_beginning[node-1]] = neighbour;
            myList.list_beginning[node-1]++;    // Increase cursor to write the next neighbour in the correct location

            if(neighbour)
                myList.neighbours_list[myList.list_beginning[neighbour-1]] = node;
            myList.list_beginning[neighbour-1]++;   // Increase cursor to write the next neighbour in the correct location
        }

        // Reset beginning position (going backwards of a nr of steps equal to the degree of the node)
        for (unsigned int node_idx=0; node_idx < myList.vertices; node_idx++){
            myList.list_beginning[node_idx] -= myList.adjNodesDegree.degree_array[node_idx];
        }

        if(debug) cout << time(nullptr) << "[Compact Adjacency List]  Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug) {
            cout << "  Node\t\tNeighbours" << endl;
            cout << "  ----------------------------" << endl;
            for (unsigned int node = 0; node < myList.vertices; node++) {
                cout << node + 1 << " -> ";
                for (unsigned int neigh_index = 0; neigh_index < myList.adjNodesDegree.degree_array[node]; neigh_index++) {
                    cout << myList.neighbours_list[myList.list_beginning[node]+neigh_index] << " ";
                }
                cout << endl;
            }
        }
        graph.close();
    }else{
        cout << "[Compact Adjacency List] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    return 0;
}

// BFS from a given source
int BFS(unsigned int source, AdjacencyList &myList, bool debug){

    list <unsigned int> fifo;
    //list <unsigned int>::iterator itr;
    unsigned int it=0;
    unsigned int output_node=0;
    unsigned int target_neighbour=0;

    // Mark all the nodes as not visited
    bool *visited = new bool [myList.vertices]();

    if (debug){
        for (unsigned int i=0; i < myList.vertices; i++){
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


        for (it = myList.list_beginning[output_node]; it < (myList.list_beginning[output_node] + myList.adjNodesDegree.degree_array[output_node]); it++) {

            target_neighbour = myList.neighbours_list[it];

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
