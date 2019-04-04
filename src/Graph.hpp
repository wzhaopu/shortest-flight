/*
 * CSE100 Project 3 Task 3 - Graph.hpp
 * Author: Zhaopu Wang and Yanxun Li
 * Date: 03/12/2019
 * This file is the header file of Graph class, including struct Node
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

#define INF_DIST INT_MAX // infinity distance

using namespace std;
struct Node{
    string airport;
    vector<pair<string, double>> adj;    // adjacency list with wieght
    double dist;
    string prev;
    bool done;

    /*
     * Node class constuctor
     */
    Node(string airport, double dist = INF_DIST, string prev = "",
        bool done = false)
        : airport(airport), dist(dist), prev(prev), done(done) {}

    /*
     * Add one airport to the adjacent list of anothor airport
     * Param: airport to be added and distance
     * Return: -
     */
    void addAdj(string neighbor, int distance) {
        adj.push_back(make_pair(neighbor, distance));
    }

    /*
     * Less than operator for Node class
     */
    bool operator<(const Node& other) {
        return dist > other.dist;
    }
};

/*
 * Comparison class used for qriority_queue
 */
class NodePtrComp {
public:
    bool operator()(Node*& lhs, Node*& rhs) const {
        return *lhs < *rhs;
    }
};

class Graph {
protected:
    unordered_map<string, Node*> nodes;

public:
    /*
     * Graph class constructor
     */
    Graph(void);

    /*
     * Graph class destructor
     */
    ~Graph(void);
	
    /*
     * Add a node and its neighbor to the graph and add a connection between
     * the two nodes by putting the neighbor in the node's adjacency list
     * with a distance value.
     * Param: a pair of airports where the first one points to the second one,
     *        and distance from the first one to the second one.
     * Return: -
     */
    void addNode(string airport, string neighbor, double distance);

    /*
     * Get the node with given airport
     * Param: airport of the node
     * Return: pointer to the node
     */
    Node* getNode(string airport);

    /*
     * Read an inputfile to create a graph.
     * Param: the input filename
     * Return: true if successed, false if failed
     */ 
    bool loadFromFile(const char* in_filename);
    
    /*
     * Find the shortest path between two nodes
     * by implementing dijkstra's algorithm
     * Param: the starting node and ending node
     * Return: true if successed, false if invalid input or failed to find
     */
    bool findShortestPath(Node* from, Node* to);
};

#endif  // GRAPH_HPP
