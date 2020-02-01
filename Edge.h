//
// Created by igor & aloysio on 01/02/20.
//

#ifndef INF421_PI_ALOYSIO_IGOR_EDGE_H
#define INF421_PI_ALOYSIO_IGOR_EDGE_H

#include "Arrow.h"

class Edge {
public:
    Edge(int id, Node* n1, Node* n2);

    ~Edge();

    int id;
    Arrow *fwd, *bck;
};

#endif //INF421_PI_ALOYSIO_IGOR_EDGE_H
