#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

struct Node;

/*
 * Edges direactions
 */
enum Direction {FWD, BCK};

// ------------------------------------------------------ //

class Edge {
public:
  Edge(int id, Node* n1, Node* n2) {
    this->id = id;
    fwd = n1;
    bck = n2;
  }

  int id;
  Node *fwd, *bck;
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
  Tree(vector<Node*> ns, vector<Edge*> es) : nodes(ns), edges(es) {
    numNodes = nodes.size();
    numEdges = edges.size();

    sumNodes.assign(numEdges, vector<int>(2, -1));
    tNodes.assign(numEdges, vector<int>(2, -1));
    path.assign(numEdges, vector<Edge*>(2, nullptr));
    
    bestAnswerSubtree.assign(numEdges, vector<int>(2, -1));
    parentInPath.assign(numEdges, vector<Node*>(2, nullptr));
    depthInPath.assign(numEdges, vector<int>(2, -1));
    positionInPath.assign(numEdges, vector<Node*>(2, nullptr));
  }
  
  /*
   * Calculates the value of the expression S by cutting the tree 
   * in every possible edge and getting the values of T for the 
   * centers of the two slices of tree.
   */
  int s() {
    int ans = INT_MAX;
    for (auto e : edges)
      ans = min(ans, tCenterDir(e, FWD) + tCenterDir(e, BCK));
    return ans;
  }

private:
  int numNodes, numEdges;
                    
  // Tree structure variables
  vector<Node*> &nodes;
  vector<Edge*> &edges;

  // Variables associated with sum
  // precalculations
  vector<vector<int>> sumNodes;
  vector<vector<int>> tNodes;
  vector<vector<Edge*>> path;

  // Variables associated with search 
  // for the best single center in a 
  // subtree
  vector<vector<int>> bestAnswerSubtree;
  vector<vector<Node*>> parentInPath;
  vector<vector<int>> depthInPath;
  vector<vector<Node*>> positionInPath;
  

  /*
   * Return sum of all nodes in a specific direction.
   */
  int sumDir(Edge* edge, Direction dir) {
    return -1;
  }

  /*
   * T(x, e) = sum for all node v in a set V { w(v) * dist(v, x) }
   * V = all v different from x and in a subtree given by direction.
   * Return the value of the expression T(x, e) for the 
   * node pointed by the edge in a specific direction
   */
  int tDir(Edge* edge, Direction dir) {
    return -1;
  }

  /*
   * T(x, e) = sum for all node v in a set V { w(v) * dist(v, x) }
   * V = all v different from x and in a subtree given by direction.
   * Calculates the value of T(x, e) for the best single node center in the tree
   * defined by one edge and one direction.
   */
  int tCenterDir(Edge* edge, Direction dir) {
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
  
  // Clearing memory
  for (auto e : edges)
    delete e;
  for (auto n : edges)
    delete n;
    
  return 0;
}

