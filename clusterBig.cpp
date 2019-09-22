/* Filename: clusterBig.cpp
 * Description: The command line program clusterBig.cpp takes in one parameter,
 *		an input filename. The input file specified by the input 
 *		filename should contain a list of binary vectors of length 24.
 *		Using the Hamming distance as a metric, the program will cluster
 *		the vectors until the distance between the clusters is at least
 *		three. The program will output the number of clusters.
 *              
 */

#include<bitset>
#include<iostream>
#include<unordered_map>
#include<vector>
#include "graph.hpp"

#define NUM_BITS 24
#define IN_IDX 1
#define EXPECTED_ARGS 2

int main(int argc, char** argv) {

	if(argc != EXPECTED_ARGS ){
		cout << "This program expects 2 arguments!" << endl;
		return(-1);
	}

	// create a new instance of Graph
	Graph* G = new Graph();

	// read input file and create vertex map and edge priority queue
	G->loadFromFile(argv[IN_IDX]);

	// run the clustering variant of Kruskal's MST algorithm
	unsigned int clusterNum = G->cluster();

	// Return the number of clusters
	cout << "Number Clusters: " << clusterNum << endl;

	// no memory leaks here
	delete G;

}


