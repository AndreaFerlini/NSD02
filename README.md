--------------------
NSD: Practical 2
--------------------

Authors:
- ANDREA FERLINI
- LUCA DE MORI

Content:

This repository contains the code to solve the exercises of Practical2 (NSD-TME, M2 UPMC).

Fall Semester 2017/18


1. FOLDER STRUCTURE

The main directory contains the following folders:
	
	a. /src   	: Contains all the functions
	b. /graphs 	: Where to put graph files. It contains the script to skip comments and blank lines
	

2. CODE STRUCTURE

	2.1 FILE ARTICULATION

	The code is structured in 3 files containing the required functions.

		a. loadgrph.cpp contains functions to compute the statistics of the graph:

			graphSize 	 -> computes the number of nodes
			graphDegree  -> counts the degree of each node
			loadAdjListContiguous -> Loads the graph as adjacency list with contiguous storage
			

		b. bfs.cpp contains the functions to store the graph in memory

			executeBFS 			-> visits the graph using a BFS algorithm and print the visited vertices.
									It also fills an array with the distance of the vertices from the source.
			extimateDiameter 	-> Iteratively visit the graph using a BFS starting from the furthest node
			printConnectedGraph -> Print all the connected elements of the graph using BFS multiple times
									untill all the vertices are visited.

			extimateAccurateDiameter -> runs "extimateDiameter" whith a source inside every connected component of the graph

		c. dijkstra.cpp

			executeDijkstra -> calculate the shortest path in a weighted graph using Dijkstra algorithm.


	In loadgraph.h two structures are defined. In particular:

		GraphDegree 	-> Stores the array for the degree of each node
		AdjacencyList   -> Stores the graph using the contiguous storage.

	

3. USAGE
	
	3.1 GRAPH FILE FORMAT

	- Our program works with graphs stored in a file as a list of edges identified by its vertex (node) id separaded by a space:

		x y

	where x and y are positive integers greater than 1.

	- For weighted graphs we use the following format:

		x y w

	where x y and w are positive integers greater than 1 separated by a space.

	3.2 LAUNCH THE PROGRAM

	The file main.cpp contains already the code to run some calculations.

	Follow the steps:
		a. Uncomment the required section:
		b. Edit the variable "filename" with the path to the graph file;
		c. Compile everything in the folder:
			g++ <program_name> main.cpp loadgraph.cpp loadgraph.h bfs.cpp bfs.h dijkstra.cpp dijkstra.h dijkstra.cpp dijkstra.h
		d. Run ./program_name
