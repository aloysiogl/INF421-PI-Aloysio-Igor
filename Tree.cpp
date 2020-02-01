//
// Created by igor on 01/02/20.
//

#include <iostream>
#include <limits.h>
#include "Tree.h"

using namespace std;

Tree::Tree(vector<Node *> &ns, vector<Edge *> &es) : nodes(ns), edges(es) {
    numNodes = nodes.size();
    numEdges = edges.size();

    // Initializing tables with -1 which means not yet
    // calculated value
    for (Edge *e : edges) {
        sumNodes[e->fwd] = -1;
        sumNodes[e->bck] = -1;
        tNodes[e->fwd] = -1;
        tNodes[e->bck] = -1;

        bestAnswerSubtree[e->fwd] = -1;
        bestAnswerSubtree[e->bck] = -1;
        depthInPath[e->fwd] = -1;
        depthInPath[e->bck] = -1;
    }
}

int Tree::s() {
    int ans = INT_MAX;
    for (Edge *e : edges)
        ans = min(ans, tCenterDir(e->fwd) + tCenterDir(e->bck));
    return ans;
}

int Tree::sNaive() {
    // Calculates distance from every node to every other node.
    //unordered_map<pair<Node*, Node*>, int> dist;
    return -1;
}

int Tree::sumDir(Arrow *arrow) {
    // Check if the value has already been calculated
    if (sumNodes[arrow] >= 0) {
        return sumNodes[arrow];
    } else {
        preprocess(arrow);
    }

    return sumNodes[arrow];
}

int Tree::tDir(Arrow *arrow) {
    if (tNodes[arrow] >= 0)
        return tNodes[arrow];
    else preprocess(arrow);

    return tNodes[arrow];
}

void Tree::preprocess(Arrow *arrow) {
    // Initalizing values (in the beggining there
    // are no soons connected)
    Node *currentNode = arrow->node;

    sumNodes[arrow] = currentNode->weight;
    tNodes[arrow] = 0;

    for (Edge *edge: currentNode->edges) {
        // Getting next node
        Arrow *nextArrow = edge->fwd;
        if (nextArrow->node == currentNode)
            nextArrow = edge->bck;

        sumNodes[arrow] += sumDir(nextArrow);
        tNodes[arrow] += sumDir(nextArrow) + tDir(nextArrow);
    }
}

int Tree::tCenterDir(Arrow *arrow) {
    return -1;
}
