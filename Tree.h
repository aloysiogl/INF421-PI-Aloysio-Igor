//
// Created by igor & aloysio on 01/02/20.
//

#ifndef INF421_PI_ALOYSIO_IGOR_TREE_H
#define INF421_PI_ALOYSIO_IGOR_TREE_H

#include <unordered_map>
#include <vector>
#include "Edge.h"

struct hash {
    std::size_t operator()(const Arrow* arrow) const {
        if (arrow == nullptr)
            return 0;
        return (size_t) arrow->edge->id;
    }
};

class Tree {
public:
    /**
     * Default constructor.
     * @param ns: Vector of pre-initializednodes, should already have
     * parameter edges correctly assigned.
     * @param es: Vector of pre-initialized edges.
     */
    Tree(std::vector<Node*> &ns, std::vector<Edge*> &es);

    /**
     * Calculates the value of the expression S by cutting the tree
     * in every possible edge and getting the values of T for the
     * centers of the two slices of tree. O(n)
     * @return: Value of S.
     */
    int s();

    /**
     * Naively calculates the value of the expression S in O(n^3), by
     * first calculating every distance from two nodes, then choosing
     * every possible two candidates center and calculating possible S.
     * @return: Value of S.
     */
    int sNaive();

    void printTree();

private:
    int numNodes, numEdges;

    // Tree structure variables
    std::vector<Node*> &nodes;
    std::vector<Edge*> &edges;

    // Variables associated with sum
    // precalculations
    std::unordered_map<Arrow*, int, hash> sumNodes;
    std::unordered_map<Arrow*, int, hash> tNodes;
    std::unordered_map<Arrow*, Arrow*, hash> path;

    // Variables associated with search
    // for the best single center in a
    // subtree
    std::unordered_map<Arrow*, int, hash> bestAnswerSubtree;
    std::unordered_map<Arrow*, Arrow*, hash> parentInPath;
    std::unordered_map<Arrow*, int, hash> distanceToCenterInPath;
    std::unordered_map<Arrow*, Arrow*, hash> centerArrow;

    /**
     * Return sum of all nodes that follow an Arrow in its
     * direction.
     * @param arrow:
     * @return: Sum of nodes.
     */
    int sumArrow(Arrow *arrow);

    /**
     * T(x, e) = sum for all node v in a set V { w(v) * dist(v, x) }
     * V = all v different from x and in a subtree given by direction.
     * Return the value of the expression T(x, e) for the
     * Node pointed by the Arrow.
     * @param arrow:
     * @return: Value for T.
     */
    int tArrow(Arrow *arrow);

    /**
     * Calculates the value of the matrixes sumNodes and tNodes for a
     * given Arrow.
     * @param arrow:
     */
    void preprocess(Arrow* arrow);

    /**
     * T(x, e) = sum for all node v in a set V { w(v) * dist(v, x) }
     * V = all v different from x and in a subtree given by direction.
     * Calculates the value of T(x, e) for the best single node center in
     * the tree defined by an Arrow.
     * @param arrow:
     * @return: Value for T.
     */
    int tCenterArrow(Arrow *arrow);

    void printTreeRecursion(Arrow* root,  int depth);

    std::string getEdgeInfo(Edge* edge);

};

#endif //INF421_PI_ALOYSIO_IGOR_TREE_H
