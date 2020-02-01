#include <iostream>
#include <vector>
#include <limits.h>
#include <unordered_map>

using namespace std;

struct Node;

/*
 * Edges direactions.
 */
enum Direction { FWD, BCK };

// ------------------------------------------------------ //

/*
 * A directed edge.
 */
class Arrow {
public:
  Arrow(Direction dir, Node* node){
    this->dir = dir;
    this->node = node;
  }

  Direction dir;
  Node* node;
};

// ------------------------------------------------------ //

class Edge {
public:
  Edge(int id, Node* n1, Node* n2) {
    this->id = id;
    fwd = new Arrow(FWD, n1);
    bck = new Arrow(BCK, n2);
  }

  ~Edge() {
    delete fwd;
    delete bck;
  }

  int id;
  Arrow *fwd, *bck;
};

// ------------------------------------------------------ //

/*
 * Stores nodes from the tree, with weights and a list of edges.
 */
struct Node {
  int weight;
  vector<Edge*> edges;
};

// ------------------------------------------------------ //

class Tree {
public:
  Tree(vector<Node*> &ns, vector<Edge*> &es) : nodes(ns), edges(es) {
    numNodes = nodes.size();
    numEdges = edges.size();

    // Initializing tables with -1 which means not yet
    // calculated value
    for (Edge* e : edges) {
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

  /*
   * Calculates the value of the expression S by cutting the tree
   * in every possible edge and getting the values of T for the
   * centers of the two slices of tree. O(n)
   */
  int s() {
    int ans = INT_MAX;
    for (Edge* e : edges)
      ans = min(ans, tCenterDir(e->fwd) + tCenterDir(e->bck));
    return ans;
  }

  /*
   * Naively calculates the value of the expression S in O(n^3), by
   * first calculating every distance from two nodes, then choosing
   * every possible two candidates center and calculating possible S.
   */
  int sNaive() {
    // Calculates distance from every node to every other node.
    //unordered_map<pair<Node*, Node*>, int> dist;
    return -1;
  }

private:
  int numNodes, numEdges;

  // Tree structure variables
  vector<Node*> &nodes;
  vector<Edge*> &edges;

  // Variables associated with sum
  // precalculations
  unordered_map<Arrow*, int> sumNodes;
  unordered_map<Arrow*, int> tNodes;
  unordered_map<Arrow*, Arrow*> path;

  // Variables associated with search
  // for the best single center in a
  // subtree
  unordered_map<Arrow*, int> bestAnswerSubtree;
  unordered_map<Arrow*, Arrow*> parentInPath;
  unordered_map<Arrow*, int> depthInPath;
  unordered_map<Arrow*, Arrow*> positionInPath;

  /*
   * Return sum of all nodes that follow an Arrow in its
   * direction.
   */
  int sumDir(Arrow* arrow) {
    // Check if the value has already been calculated
    if (sumNodes[arrow] >= 0) {
      return sumNodes[arrow];
    }
    else {
      preprocess(arrow);
    }

    return sumNodes[arrow];
  }

  /*
   * T(x, e) = sum for all node v in a set V { w(v) * dist(v, x) }
   * V = all v different from x and in a subtree given by direction.
   * Return the value of the expression T(x, e) for the
   * Node pointed by the Arrow.
   */
  int tDir(Arrow* arrow) {
    if (tNodes[arrow] >= 0)
      return tNodes[arrow];
    else preprocess(arrow);

    return tNodes[arrow];
  }

  /*
   * Calculates the value of the matrixes sumNodes and tNodes for a
   * given Arrow.
   */
  void preprocess(Arrow* arrow) {
    // Initalizing values (in the beggining there
    // are no soons connected)
    Node* currentNode = arrow->node;

    sumNodes[arrow] = currentNode->weight;
    tNodes[arrow] = 0;

    for (Edge* edge: currentNode->edges){
      // Getting next node
      Arrow* nextArrow = edge->fwd;
      if (nextArrow->node == currentNode)
        nextArrow = edge->bck;

      sumNodes[arrow] += sumDir(nextArrow);
      tNodes[arrow] += sumDir(nextArrow) + tDir(nextArrow);
    }
  }

  /*
   * T(x, e) = sum for all node v in a set V { w(v) * dist(v, x) }
   * V = all v different from x and in a subtree given by direction.
   * Calculates the value of T(x, e) for the best single node center in
   * the tree defined by an Arrow.
   */
  int tCenterDir(Arrow* arrow) {
    return -1;
  }
};

// ------------------------------------------------------ //

int main() {
  int numNodes, numEdges;
  vector<Node*> nodes;
  vector<Edge*> edges;

  cin >> numNodes;
  numEdges = numNodes - 1;

  // Allocating space for nodes
  for (int i = 0; i < numNodes; i++)
    nodes.push_back(new Node());

  // Reading edges
  for (int i = 0; i < numEdges; i++) {
    int x, y;
    cin >> x >> y;
    x--; y--;
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
  cout << t.s() << endl;

  return 0;
 
  // Clearing memory
  for (auto e : edges)
    delete e;
  for (auto n : edges)
    delete n;

  return 0;
}
