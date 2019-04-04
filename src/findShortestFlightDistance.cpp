/*
 * CSE100 Project 3 Task 3 - findShortestFlightDistance.cpp
 * Author: Zhaopu Wang and Yanxun Li
 * Date: 03/12/2019
 * This is the main function of finding the shortest flight distance.
 */

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "Graph.hpp"

using namespace std;

/*
 * print error message
 */
void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
         << " friendship_pairs_file k_value output_file"
         << endl;
    exit(-1);
}

/*
 * The main function loads the graph from a graph input file,
 * find the shortest flight distance from one city to another
 * and output the list to an output file.
 * Param: argc - 4 if valid, argv - the array of args
 * Return: 0 if successful, 1 if error
 */
int main(int argc, char* argv[]) {
    if (argc != 4) {
        usage(argv[0]);
    }

    char* graph_filename = argv[1];
    char* pairs_filename = argv[2];
    char* output_filename = argv[3];

    ifstream infile;
    ofstream outfile;
    infile.open(pairs_filename);
    outfile.open(output_filename);

    cout << "Loading " << graph_filename << "...\n";
    Graph g;
    g.loadFromFile(graph_filename);

    while (infile) {
        // read a pair of cities from the input file:
        string s;
        if (!getline(infile, s)) break;

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string s;
            if (!getline(ss, s, ' ')) break;
            record.push_back(s);
        }

        if (record.size() != 2) {
            continue;
        }

        cout << "Computing the shortest flight distance from "
            << record[0] << " to " << record[1] << " ...\n";

        // find the shortest path:
        Node* from = g.getNode(record[0]);
        Node* to = g.getNode(record[1]);

        if (!g.findShortestPath(from, to)) {
            outfile << "\n";
            continue;
        }

        Node* curr = to;
        stack<string> stk;
        stk.push(curr->airport);
        while (curr->prev != "") {
            curr = g.getNode(curr->prev);
            stk.push(curr->airport);
        }

        // retrieve the path and write it to the output file:
        while (true) {
            outfile << stk.top();
            stk.pop();
            if (stk.empty()) {
                break;
            }
            outfile << " -> ";
        }

        if (infile)
            outfile << "     " << to->dist << "\n";
    }

    if (!infile.eof()) {
        return 1;
    }

    infile.close();
    outfile.close();
    return 0;
}
