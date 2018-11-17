#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <iostream>

class graph {


  graph();


  void insert(string id, string destID = NULL, int cost);


  void findShortest();









  private:
  class edge {
  public:
    vertex *dest;
    int cost;
  };

  class vertex {
  public:
    bool known;
    std::string id;

    //std::list<edge> next;
    heap costPath;
  };

  std::list<*vertex> vertices;
  hash tableID;
}
