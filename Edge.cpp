//
// Created by igor & aloysio on 01/02/20.
//

#include "Edge.h"

Edge::Edge(int id, Node *n1, Node *n2) {
    this->id = id;
    fwd = new Arrow(FWD, n1);
    bck = new Arrow(BCK, n2);
}

Edge::~Edge() {
    delete fwd;
    delete bck;
}
