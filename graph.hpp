/*
 * Filename: graph.hpp
 * Description: Implements a graph class for a clustering
 *		variant of Kruskal's MST algorithm.
 *		
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP
#define NUM_BITS 24

#include <bitset>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "vertex.hpp"

using namespace std;

/* 
 * Class name: Graph
 * Instance Variables: vertex_map (unordered map of vertex names and
 *				   corresponding vertex pointers for
 				   fast lookup)
 *                     vertex_vector (vector of vertex pointers for fast
 				      iteration)
 * Description: Implements a Graph class for a clustering variant of 
 *              Kruskal's MST algorithm.                   
 * Public Methods: constructor, destructor, loadfromFile, cluster, find, merge
 * Private Methods: None                    
*/

class Graph {

public:

    // Unordered map of vertex labels and corresponding vertex pointers
    unordered_map<bitset<NUM_BITS>,Vertex*> vertex_map;

    // Vector of Vertex Pointers
    vector<Vertex*> vertex_vector;

    /**
     * Constuctor of the graph
     */
    Graph(void);

    /*
     * Load the graph from a list of its edges and edge costs
     *
     * filename - input filename
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* filename);

    /* Destructor */
    ~Graph();

    /*
     * Clustering Variant of Kruskal's MST Algorithm
     * 
     * returns the maximum number of clusters with distance
     * between the clusters at least 3
     */ 
    unsigned int cluster();

    /*
     * Finds the representative of the connected component that the vertex n
     * is in and implements path compression. Path compression makes all the
     * actors on a path from n to its parent, the direct children of the 
     * parent.
     *
     * n - Vertex* pointer representing n
     *
     * returns a Vertex* pointer pointing to the representative of
     * the connected component that the vertex n is in
     */ 

    Vertex* find( Vertex* n );

    /*
     * Merges the connected components that the vertices u and v are in 
     *
     * u -- Vertex* pointer 
     * v -- Vertex* pointer representing a vertex in a different
     *      connected component than u
     *
     * Possibly changes the parent of u or v and may also change the
     * rank of u or v.     
     *
     */ 
    void merge(Vertex* u, Vertex* v); 

};


#endif // GRAPH_HPP
