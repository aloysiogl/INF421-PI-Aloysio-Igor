//
// Created by igor & aloysio on 01/02/20.
//

#include <iostream>
#include "Tree.h"

using namespace std;

int main() {
    freopen("../tests/centers.0.in", "r", stdin);

    int numNodes, numEdges;
    vector<Node *> nodes;
    vector<Edge *> edges;

    cin >> numNodes;
    numEdges = numNodes - 1;

    // Allocating space for nodes
    nodes.assign((unsigned long) numNodes, nullptr);
    for (int i = 0; i < numNodes; i++) {
        nodes[i] = new Node();
        nodes[i]->id = i;
    }

    // Reading edges
    for (int i = 0; i < numEdges; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edges.push_back(new Edge(i, nodes[x], nodes[y]));
        nodes[x]->edges.push_back(edges.back());
        nodes[y]->edges.push_back(edges.back());
    }

    // Reading nodes
    for (int i = 0; i < numNodes; i++) {
        int x;
        cin >> x;
        nodes[i]->weight = x;
    }

    // Solving problem
    Tree t(nodes, edges);
    time_t t1 = clock();
    cout << t.sNaive() << endl;
    cout << "Time taken: " << (double) (clock() - t1) / CLOCKS_PER_SEC << " s" << endl;

//    // Clearing memory
//    for (auto e : edges)
//        delete e;
//    for (auto n : edges)
//        delete n;

    return 0;
}
