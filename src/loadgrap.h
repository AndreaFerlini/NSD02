//
// Created by Andrea Ferlini on 26/09/2017.
//

#ifndef PRACTICAL2_LOADGRAP_H
#define PRACTICAL2_LOADGRAP_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <list>

using namespace std;

/// DATA STRUCTURES
struct GraphDegree{
    int* degree_array;          // degree of every node
    unsigned int graph_size;    // number of nodes in the graph

    /// DEFAULT CONSTRUCTOR
    GraphDegree(){
        degree_array = nullptr;
        graph_size = 0;
    }

    /// CONSTRUCTOR
    GraphDegree(unsigned int numNodes){
        degree_array = new int[numNodes](); // with () it's initialized with all 0s
        graph_size = numNodes;
    }

    /// COPY CONSTRUCTOR
    /// To allow -> a = b with NodeDegree a,b;
    GraphDegree(const GraphDegree &obj){
        graph_size = obj.graph_size;
        degree_array = new int[obj.graph_size]; // with () it's initialized with all 0s
        for (unsigned int i=0; i<graph_size; i++){
            degree_array[i] = obj.degree_array[i];
        }
    }

    /// DISTRUCTOR
    ~GraphDegree(){
        if (degree_array != nullptr){
            delete[] degree_array;
        }
    }

    /// PRINT METHOD
    void print(){
        for (unsigned int i=0; i<graph_size; i++){
            cout << "  " << i+1 << " " << degree_array[i] << endl;
        }
    }

};

struct AdjacencyList{
    unsigned int* neighbours_list;
    unsigned int* list_beginning;
    unsigned int size_neighbour_list;
    unsigned int vertices;

    GraphDegree adjNodesDegree;


    /// DEFAULT CONSTRUCTOR
    AdjacencyList(){
        neighbours_list = nullptr;
        list_beginning = nullptr;
        size_neighbour_list = 0;
        vertices = 0;
    }

    /// CONSTRUCTOR
    AdjacencyList(unsigned int sum_degree, unsigned int num_nodes){
        size_neighbour_list = sum_degree;
        vertices = num_nodes;
        neighbours_list = new unsigned int [sum_degree]();
        list_beginning = new unsigned int [num_nodes]();

    }

    /// COPY CONSTRUCTOR
    /// To allow -> a = b with NodeDegree a,b;
    AdjacencyList(const AdjacencyList &obj){
        vertices = obj.vertices;
        size_neighbour_list= obj.size_neighbour_list;
        neighbours_list = new unsigned int[size_neighbour_list]; // with () it's initialized with all 0s
        list_beginning = new unsigned int[vertices]; // with () it's initialized with all 0s

        for (unsigned int i=0; i < size_neighbour_list; i++){
            neighbours_list[i] = obj.neighbours_list[i];
        }

        for (unsigned int i=0; i < vertices; i++) {
            list_beginning[i] = obj.list_beginning[i];
        }
    }

    /// DISTRUCTOR
    ~AdjacencyList(){
        if (neighbours_list != nullptr){
            delete[] neighbours_list;
        }
        if (list_beginning != nullptr){
            delete[] list_beginning;
        }
    }

    /// PRINT METHOD
    void print(bool debug = false){

        if (debug){
            cout << "[myAdj.print]" << endl;
        }

        cout << "  Node\t\tNeighbours" << endl;
        cout << "  ----------------------------" << endl;
        for (unsigned int node = 0; node < vertices; node++) {
            cout << node + 1 << " -> ";
            for (unsigned int neigh_index = 0; neigh_index < adjNodesDegree.degree_array[node]; neigh_index++) {
                cout << neighbours_list[list_beginning[node] + neigh_index] << " ";
            }
            cout << endl << endl ;
        }
    }
};
/// FUNCTIONS

int loadAdjListContiguous (string filename, AdjacencyList& myList, bool debug=false);
int graphDegree (string filename, GraphDegree& nodeArray, bool debug=false);
int BFS(unsigned int source, AdjacencyList &myList, bool debug=false);

#endif //PRACTICAL2_LOADGRAP_H
