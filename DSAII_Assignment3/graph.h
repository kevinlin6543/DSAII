#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "heap.h"

class graph
{

  public:

  graph();

  // Handles inserting of nodes by taking the three arguements in a line and
  // using it to create a node and push the pointer to a vector along with
  // the associated edge
  void insert(std::string, std::string, int);

  // Applies dijkstra algorithm on the graph
  int dijkstra(std::string &startNode);

  // Writes to the output file from the paths vector of strings
  void outputGen(std::ofstream &outfile);

  // Handles asking for input files and output files names
  void prompt();

  private:
  int cap;
  class edge;
  class node;
  std::list<node*> vertices;
  hashTable *tableID; // hash table of ID names

  class node
  {
    public:
    bool known;
    int dist;
    std::string id;
    std::list<edge> adj;
    std::list<std::string> paths;
  };
  class edge
  {
    public:
    node *dest;
    int cost;
  };
};
#endif //_GRAPH_H
