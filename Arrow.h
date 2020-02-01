//
// Created by igor & aloysio on 01/02/20.
//

#ifndef INF421_PI_ALOYSIO_IGOR_ARROW_H
#define INF421_PI_ALOYSIO_IGOR_ARROW_H

#include "Node.h"

class Edge;

/*
 * Arrow direactions.
 */
enum Direction { FWD, BCK };

/**
 * A directed edge.
 */
class Arrow {
public:
    Arrow(Edge* edge, Direction dir, Node* node);

    Direction dir;
    Node* node;
    Edge* edge;
};

#endif //INF421_PI_ALOYSIO_IGOR_ARROW_H
