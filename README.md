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
	
	a. /code   	: Contains all the functions
	b. /graphs 	: Where to put graph files. It contains the script to skip comments and blank lines
	c. /plot	: Contains the scripts to plot the degree distribution with gnuplot

2. CODE STRUCTURE

	2.1 FILE ARTICULATION

	The code provides two files containing the required functions.

		a. graphstats.cpp contains functions to compute the statistics of the graph:

			graphSize 	 -> computes the number of nodes
			graphDegree  -> counts the degree of each node
			graphStats 	 -> provide the overall statistics (size, degree, min, max and avg degree, density)
			cleaningData -> remove self-loops and duplicated edges in the file
			degreeDistribution -> writes a file containing the points of the degree distributon histogram

		b. storegraph.cpp contains the functions to store the graph in memory

			loadAdjList  -> Loads the graph as adjacency list
			loadAdjListCompact	-> Loads the graph as adjacency list with contiguous storage
			loadAdjMat 	 -> Load the graph as adjacency matrix
			loadEdgeList -> load the grapg as list of edges

	In graphstats.h two structures are defined. In particular:

		nDegree -> Store the array for the degree of each node
		gStats  -> Store the graph statistics

	Note: storegraph.h includes graphstats.h in order to use some functioncs


3. USAGE
	
	3.1 GRAPH FILE FORMAT

	Our program works with graphs stored in a file as a list of edges identified by its vertex (node) id separaded by a space

		x y

	where x and y are positive integers greater than 1.

	3.2 LAUNCH THE PROGRAM

	The file main.cpp contains already the code to run some calculations.

	Follow the steps:
		a. Uncomment the required section:
		b. Edit the variable "filename" with the path to the graph file;
		c. Edit the variable "outputFile" with the path to the file where to save the degree distribution; 
		  	the program will automatically generate also the .eps (vector image) file with the plot.
		d. Compile everything in the folder:
			g++ <program_name> main.cpp graphstats.cpp graphstats.h storegaph.cpp storegaph.h
		e. Run ./program_name
