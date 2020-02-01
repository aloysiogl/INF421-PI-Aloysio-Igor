//
// Created by igor & aloysio on 01/02/20.
//

#include <iostream>
#include <limits.h>
#include "Tree.h"

using namespace std;

Tree::Tree(vector<Node *> &ns, vector<Edge *> &es) : nodes(ns), edges(es) {
    numNodes = (int) nodes.size();
    numEdges = (int) edges.size();

    // Initializing tables with -1 which means not yet
    // calculated value
    for (Edge *e : edges) {
        sumNodes[e->fwd] = -1;
        sumNodes[e->bck] = -1;
        tNodes[e->fwd] = -1;
        tNodes[e->bck] = -1;

        bestAnswerSubtree[e->fwd] = -1;
        bestAnswerSubtree[e->bck] = -1;
        distanceToCenterInPath[e->fwd] = -1;
        distanceToCenterInPath[e->bck] = -1;
    }
}

int Tree::s() {
    int ans = INT_MAX;
    for (Edge *e : edges)
        ans = min(ans, tArrow(e->fwd) + tArrow(e->bck));
    for (Edge *e : edges)
        ans = min(ans, tCenterArrow(e->fwd) + tCenterArrow(e->bck));

    return ans;
}

int Tree::sNaive() {
    // Calculates distance from every node to every other node using Floyd-Warshall's
    // algorithm.
    vector<vector<int> > dist((unsigned long) numNodes, vector<int>(numNodes, INT_MAX));
    for (int i = 0; i < numNodes; i++)
        dist[i][i] = 0;
    for (Edge *e : edges) {
        dist[e->fwd->node->id][e->bck->node->id] = 1;
        dist[e->bck->node->id][e->fwd->node->id] = 1;
    }

    for (int k = 0; k < numNodes; k++)
        for (int i = 0; i < numNodes; i++)
            for (int j = 0; j < numNodes; j++) {
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }

    // Using these distances to calculate S
    int minS = INT_MAX;
    for (Node *x : nodes)
        for (Node *y : nodes) {
            int s = 0;
            for (Node *v : nodes)
                s += v->weight * min(dist[x->id][v->id], dist[y->id][v->id]);
            minS = min(minS, s);
        }

    return minS;
}

int Tree::sumArrow(Arrow *arrow) {
    // Check if the value has already been calculated
    if (sumNodes[arrow] >= 0) {
        return sumNodes[arrow];
    } else {
        preprocess(arrow);
    }

    return sumNodes[arrow];
}

int Tree::tArrow(Arrow *arrow) {
    if (tNodes[arrow] >= 0)
        return tNodes[arrow];
    else preprocess(arrow);

    return tNodes[arrow];
}

void Tree::preprocess(Arrow *arrow) {
    // Initializing values (in the beginning there
    // are no sons connected)
    Node *currentNode = arrow->node;

    sumNodes[arrow] = currentNode->weight;
    tNodes[arrow] = 0;

    for (Edge *edge: currentNode->edges) {
        // Its not possible to return
        if (edge == arrow->edge)
            continue;

        // Getting next node
        Arrow *nextArrow = edge->fwd;
        if (nextArrow->node == currentNode)
            nextArrow = edge->bck;

        sumNodes[arrow] += sumArrow(nextArrow);
        tNodes[arrow] += sumArrow(nextArrow) + tArrow(nextArrow);

        // Getting next arrow in the path where the center could be
        if (path[arrow] == nullptr || sumArrow(path[nextArrow]) > sumArrow(path[arrow]))
            path[arrow] = nextArrow;
    }
}

void Tree::printTree() {
    Edge *rootEdge = edges[0];

    printTreeRecursion(rootEdge->bck, 0);
    printTreeRecursion(rootEdge->fwd, 0);
}

std::string Tree::getEdgeInfo(Edge *edge) {
    Arrow *fwd = edge->fwd;
    Arrow *bck = edge->bck;

    string soma = "(soma FWD = " + to_string(sumArrow(fwd)) + " soma BCK = " + to_string(sumArrow(bck)) + ")";
    string t = "(t FWD = " + to_string(tArrow(fwd)) + " t BCK = " + to_string(tArrow(bck)) + ")";
    string pat;
    if (path[fwd] != nullptr && path[bck] != nullptr)
        pat = "(path FWD = " + to_string(path[fwd]->edge->id) + " path BCK = " + to_string(path[bck]->edge->id) + ")";
    else if (path[fwd] != nullptr)
        pat = "(path FWD = " + to_string(path[fwd]->edge->id) + ")";
    else if (path[bck] != nullptr)
        pat = "(path BCK = " + to_string(path[bck]->edge->id) + ")";
    else pat = "nullptr";

    string centerArro = "(edge = " + to_string(edge->id) + " sum_back = " + to_string(tCenterArrow(edge->bck)) +
                        " sum_fwd = " + to_string(tCenterArrow(edge->fwd)) + ")";

    return centerArro;
}

void Tree::printTreeRecursion(Arrow *root, int depth) {
    Node *currentNode = root->node;

    for (int i = 0; i < depth; ++i) std::cout << " ";

    std::cout << getEdgeInfo(root->edge) << std::endl;

    for (Edge *edge: currentNode->edges) {
        if (edge == root->edge)
            continue;

        Arrow *nextArrow = edge->fwd;
        if (nextArrow->node == currentNode)
            nextArrow = edge->bck;

        printTreeRecursion(nextArrow, depth + 1);

    }
}

int Tree::tCenterArrow(Arrow *arrow) {
    if (bestAnswerSubtree[arrow] >= 0)
        return bestAnswerSubtree[arrow];

    if (path[arrow] == nullptr) {
        centerArrow[arrow] = arrow;
        bestAnswerSubtree[arrow] = 0;
        distanceToCenterInPath[arrow] = 0;
        return 0;
    }

    int tCenterPath = tCenterArrow(path[arrow]);
    parentInPath[path[arrow]] = arrow;
    distanceToCenterInPath[arrow] = distanceToCenterInPath[path[arrow]] + 1;


    Arrow *currentCenterArrow = centerArrow[path[arrow]];

    // Calculating current value for the T expression
    int tWithoutPath = tArrow(arrow) - tArrow(path[arrow]) - sumArrow(path[arrow]);
    int sumWithoutPath = sumArrow(arrow) - sumArrow(path[arrow]);

    int tValue = tWithoutPath + sumWithoutPath * distanceToCenterInPath[arrow] + tCenterPath;\

    while (sumArrow(arrow) > 2 * sumArrow(currentCenterArrow)) {
        tValue += sumArrow(currentCenterArrow);
        tValue -= (sumArrow(arrow) - sumArrow(currentCenterArrow));
        currentCenterArrow = parentInPath[currentCenterArrow];
        distanceToCenterInPath[arrow]--;
    }

    centerArrow[arrow] = currentCenterArrow;
    bestAnswerSubtree[arrow] = tValue;
    return tValue;
}
