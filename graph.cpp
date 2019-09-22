/*
 * Filename: graph.cpp
 * Description: Implements a graph class for a clustering variant
 *		of Kruskal's MST algorithm.
 *              
 */

#define NUM_BITS 24

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include "graph.hpp"

using namespace std;

/*
 * Constructor of the graph
 */ 
Graph::Graph(void) {}

/*
 * Load the graph from a list of its edges and edge costs
 *
 * filename - input filename
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool Graph::loadFromFile(const char* filename) {

	// used for parsing input file
	string line;

	// input file stream
	ifstream * in = new ifstream(filename);

	// Raise an error if file can't be read and exit
	if (in->eof()) {
		cerr << "Failed to read " << filename << "!\n";
		delete in;
		return false;
	}	

	// discard the first line
	getline(*in, line);

	// read in each vertex label
	while (getline(*in, line)) {

		// remove spaces
		string::iterator end_pos = remove(line.begin(), line.end(), ' ');
		line.erase(end_pos, line.end());

		// construct bitset from string
		bitset<NUM_BITS> current(line);	

		// search for vertex in vertex map. If vertex not found,
		// create new Vertex, set its parent to itself, and
		// input the vector into both the vertex map and the 
		// vertex vector.
		Vertex* currentVertex = vertex_map[current];
		if (currentVertex == nullptr) {
			currentVertex = new Vertex(current);
			currentVertex->parent = currentVertex;
			vertex_map[current] = currentVertex;
			vertex_vector.push_back(currentVertex);
		}
	}	
		
	// no memory leaks here
	delete in;

	return true;

}

/*
 * Finds the representative of the connected component that the vertex n
 * is in and implements path compression. Path compression makes all the
 * vertices on a path from n to its parent, the direct children of the 
 * parent.
 *                          
 * n - Vertex* pointer representing vertex
 *                                    
 * returns a Vertex* pointer pointing to the representative of
 * the connected component that the vertex is in
 */

Vertex* Graph::find( Vertex* n ) { 

	if (n != n->parent) {
		n->parent = find(n->parent); 
	}                             
	return n->parent; 

} 

/*
 * Merges the connected components that the vertices u and v are in 
 *           
 * u -- Vertex* pointer representing a vertex
 * v -- Vertex* pointer representing a vertex in a different
 *      connected component than u
 *                               
 * Possibly changes the parent of u or v and may also change the
 * rank of u or v.     
 *                                              
 */

void Graph::merge(Vertex* u, Vertex* v) { 

	Vertex* uParent = find(u); 
	Vertex* vParent = find(v); 

	/* if two sets are unioned and have different ranks, the resulting set's 
	 * rank is the larger of the two. Attach the shorter tree to the root of 
	 * the taller tree. Thus, the resulting tree is no taller than the 
	 * original trees.
	 */  
	if (uParent->rank > vParent->rank) { 
		vParent->parent = uParent; 
	}    
	else { 
		uParent->parent = vParent; 
	}

	/* If two sets are unioned and have the same rank, the resulting set's 
	 * rank is one larger; When we attach the tree to the other tree, the
	 * resulting tree is taller by one node
	 */  
	if (uParent->rank == vParent->rank) { 
		++vParent->rank; 
	}
} 

/*
 * Clustering Variant of Kruskal's MST Algorithm
 * Returns the maximum number of clusters with distance
 * at least 3 between the clusters.
 *            
 */

unsigned int Graph::cluster() {

	// used to count number of edges in current MST
	unsigned int treeEdges = 0;

	// used to iterate over vertex_vector
	vector<Vertex*>::iterator it;

	// used to check if a vertex is in the vertex_map
	bitset<NUM_BITS> current;

	// Add edges of weight 1 to the MST. Iterate over the
	// vertices in the graph. Set current to be a copy of 
	// the iterator's name. For i = 0 to NUM_BITS-1, flip the 
	// value of current at the ith position, and check if the 
	// resulting vertex is in the graph. If the resulting vertex
	// is in the graph, check if it is in the same component as
	// the iterator. If not, then merge the two vertices and 
	// increment the tree edges.
	for(it = vertex_vector.begin(); it != vertex_vector.end(); ++it) {
		for( unsigned int i = 0; i < NUM_BITS; ++i ) {
			current = (*it)->name;
			current.flip(i);
			Vertex* currentVertex = vertex_map[current];
			if(currentVertex != nullptr) {
				Vertex* currentParent = find(currentVertex);
				Vertex* itParent = find(*it);
				if( currentParent != itParent ){
					merge(currentVertex, *it);
					++treeEdges;
				}
			}
		}
	}

	// Add edges of weight 2 to the MST. Iterate over the vertices in
	// the graph. Set current to be a copy of the iterator's name. For
	// i = 0 to NUM_BITS-2 and for j = i+1 to NUM_BITS-1, flip the values
	// of current at the ith and jth positions. Check if the resulting
	// vertex is in the graph. If the resulting vertex is in the graph,
	// check if it is in the same component as the iterator. If not, then
	// merge the two vertices and increment the tree edges.
	for(it = vertex_vector.begin(); it != vertex_vector.end(); ++it) {
		for(unsigned int i = 0; i < NUM_BITS - 1; ++i) {
			for(unsigned int j = i + 1; j < NUM_BITS; ++j) {
				current = (*it)->name;
				current.flip(i);
				current.flip(j);
				Vertex* currentVertex = vertex_map[current];
				if(currentVertex != nullptr) {
					Vertex* currentParent = find(currentVertex);
					Vertex* itParent = find(*it);
					if( currentParent != itParent ){
						merge(currentVertex, *it);
						++treeEdges;
					}
				}
			}
		}
	}

	// return the number of components
	return vertex_vector.size() - treeEdges;
}    


/*
 * Destructor: Iterate through the vertex vector and delete all vertices
 */

Graph::~Graph() {

	// used to iterate through the vertex vector
	vector<Vertex*>::iterator it;

	for ( it = vertex_vector.begin(); it != vertex_vector.end(); ++it ){
		delete *it;
	}

}
