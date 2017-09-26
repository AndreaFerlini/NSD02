//
// Created by Andrea Ferlini on 26/09/2017.
//

#ifndef PRACTICAL2_LOADGRAP_H
#define PRACTICAL2_LOADGRAP_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

/// DATA STRUCTURES
struct NodeDegree{
    int* degree_array;          // degree of every node
    unsigned int graph_size;    // number of nodes in the graph

    /// DEFAULT CONSTRUCTOR
    NodeDegree(){
        degree_array = nullptr;
        graph_size = 0;
    }

    /// CONSTRUCTOR
    NodeDegree(unsigned int numNodes){
        degree_array = new int[numNodes](); // with () it's initialized with all 0s
        graph_size = numNodes;
    }

    /// COPY CONSTRUCTOR
    /// To allow -> a = b with NodeDegree a,b;
    NodeDegree(const NodeDegree &obj){
        graph_size = obj.graph_size;
        degree_array = new int[obj.graph_size]; // with () it's initialized with all 0s
        for (unsigned int i=0; i<graph_size; i++){
            degree_array[i] = obj.degree_array[i];
        }
    }

    /// DISTRUCTOR
    ~NodeDegree(){
        if (degree_array != nullptr){
            delete[] degree_array;
        }
    }

    /// PRINT THE STRUCTURE
    void print(){
        for (unsigned int i=0; i<graph_size; i++){
            cout << "  " << i+1 << " " << degree_array[i] << endl;
        }
    }

};

/// FUNCTIONS

int loadAdjListContiguous (string filename, bool debug="false");
int graphDegree (string filename, NodeDegree& nodeArray, bool debug="false");

#endif //PRACTICAL2_LOADGRAP_H
