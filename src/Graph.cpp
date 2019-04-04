/*
 * CSE100 Project 3 Task 3 - Graph.cpp
 * Author: Zhaopu Wang and Yanxun Li
 * Date: 03/12/2019
 * This is the definition of Graph class
 */

#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <queue>

using namespace std;

/*
 * Graph class constructor
 */
Graph::Graph(void)
    : nodes(0) {}

/*
 * Graph class destructor
 */
Graph::~Graph(void) {
    for (auto itr : nodes) {
        delete itr.second;
    }
}

/*
 * Add a node and its neighbor to the graph and add a connection between
 * the two nodes by putting the neighbor in the node's adjacency list
 * with a distance value.
 * Param: a pair of airports where the first one points to the second one,
 *        and distance from the first one to the second one.
 * Return: -
 */ 
void Graph::addNode(string airport, string neighbor, double distance) {
    auto itr = nodes.find(airport);
    auto neighborItr = nodes.find(neighbor);

    if (itr == nodes.end()) {
        Node* newAirport = new Node(airport);
        newAirport->addAdj(neighbor, distance);
        nodes.insert(make_pair(airport, newAirport));
    }
    else {
        itr->second->addAdj(neighbor, distance);
    }

    if (neighborItr == nodes.end()) {
        Node* newNeighbor = new Node(neighbor);
        nodes.insert(make_pair(neighbor, newNeighbor));
    }
}  

/*
 * Get the node with given airport
 * Param: airport of the node
 * Return: pointer to the node
 */
Node* Graph::getNode(string airport) {
    if (nodes.find(airport) == nodes.end())
        return nullptr;
    return nodes[airport];
}

/*
 * Read an inputfile to create a graph
 * Param: the input filename
 * Return: true if successed, false if failed
 */
bool Graph::loadFromFile(const char* in_filename) {
    ifstream infile(in_filename);

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        istringstream ss(s);
        vector<string> record;

        // read first, second and eighth fields only
        for (int i = 0; getline(ss, s, '\t'); i++) {
            if (i == 0 || i == 1 || i == 7) {
                record.push_back(s);
            }
        }

        if (record.size() != 3) {
            continue;
        }

        addNode(record[0], record[1], stod(record[2]));
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    infile.close();
    return true;
}

/*
 * Find the shortest path between two nodes
 * by implementing dijkstra's algorithm
 * Param: the starting node and ending node
 * Return: true if successed, false if invalid input or failed to find
 */
bool Graph::findShortestPath(Node* from, Node* to) {
    if (!from || !to) {
        return false;
    }

    priority_queue<Node*, vector<Node*>, NodePtrComp> pq;

    // initialize
    for (auto nodePair : nodes) {
        nodePair.second->dist = INF_DIST;
        nodePair.second->prev = "";
        nodePair.second->done = false;
    }

    // traverse
    from->dist = 0;
    pq.push(from);
    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();
        if (curr == to) {
            return true;
        }
        if (!curr->done) {
            curr->done = true;
            for (auto neighbor : curr->adj) {
                double distThruCurr = curr->dist + neighbor.second;
                Node* neighborNode = nodes[neighbor.first];
                if (distThruCurr < neighborNode->dist) {
                    neighborNode->prev = curr->airport;
                    neighborNode->dist = distThruCurr;
                    pq.push(neighborNode);
                }
            }
        }
    }
    return false;
}
