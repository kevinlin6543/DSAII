#include "graph.h"

using namespace std;


graph::graph()
{

}

void graph::insert(string id, string destID, int cost)
{
  if (!tableID.contains(id))
  {
    tableID.insert(id);
    vertex temp;
    temp.id = id;
    vertices.push_back(temp*);
  }
  else
    *temp = getPointer(id);

  edge e;
  if (!tableID.contains(destID))
  {
    vertex dest;
    dest.id = destID;
    e.dest = *dest;
  }
  else
    e.dest = *p1;
  e.cost = cost;

  temp->next.push_back(e);

}
