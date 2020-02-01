//
// Created by igor & aloysio on 01/02/20.
//

#include "Arrow.h"
#include "Edge.h"

Arrow::Arrow(Edge* edge, Direction dir, Node* node){
    this->dir = dir;
    this->node = node;
    this->edge = edge;
}
