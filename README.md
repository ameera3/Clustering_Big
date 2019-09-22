# Clustering_Big

## Usage
To compile, type "make". To run the program, type "./clusterBig clustering_big.txt".

## Introduction
The command line program clusterBig.cpp takes in one parameter,
an input filename. The input file specified by the input 
filename should contain a list of binary vectors of length 24.
The input file format should be

[# of nodes] [# of bits for each node's label]

[first bit of node 1] ... [last bit of node 1]

[first bit of node 2] ... [last bit of node 2]

...

The binary vectors can be thought of as the vertices of a complete
graph. The cost of each edge is the Hamming distance between the
two endpoints. We use std::bitset to encode the binary vectors.

Using the Hamming distance as a metric, the program will cluster
the vectors until the distance between the clusters is at least
three. The program will output the number of clusters.

For fast lookup, we input the graph's vertices into a hashtable.
We iterate over the graph's vertices. For each vertex v, we use
the hashtable to check if any binary vector w at distance 1 from v lies in
the graph. If w is a vertex in the graph, we then check if w lies
in the same component as v. If not, then we merge v and w into the
same component. We increment the number of edges in our MST.

We iterate over the graph's vertices again and, for each vertex v,
do a similar check for binary vectors w at distance 2 from v. Finally, 
we output the number of components, which is 

(number of vertices) - (number of edges in the MST). 
