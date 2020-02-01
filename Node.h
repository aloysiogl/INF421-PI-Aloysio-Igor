//
// Created by igor & aloysio on 01/02/20.
//

class Edge;

#ifndef INF421_PI_ALOYSIO_IGOR_NODE_H
#define INF421_PI_ALOYSIO_IGOR_NODE_H

#include <vector>

/*
 * Stores nodes from the tree, with weights and a list of edges.
 */
struct Node {
    int weight;
    std::vector<Edge*> edges;
};

#endif //INF421_PI_ALOYSIO_IGOR_NODE_H
