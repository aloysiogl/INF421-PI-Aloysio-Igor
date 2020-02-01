#include <iostream>
#include "Tree.h"

using namespace std;

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
