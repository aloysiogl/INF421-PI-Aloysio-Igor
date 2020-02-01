//
// Created by igor & aloysio on 01/02/20.
//

#ifndef INF421_PI_ALOYSIO_IGOR_ARROW_H
#define INF421_PI_ALOYSIO_IGOR_ARROW_H

#include "Node.h"

/*
 * Arrow direactions.
 */
enum Direction { FWD, BCK };

/*
 * A directed edge.
 */
class Arrow {
public:
    Arrow(Direction dir, Node* node);

    Direction dir;
    Node* node;
};

#endif //INF421_PI_ALOYSIO_IGOR_ARROW_H
