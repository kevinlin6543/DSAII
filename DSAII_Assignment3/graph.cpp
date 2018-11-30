#include "graph.h"

using namespace std;


graph::graph()
{
  tableID = new hashTable(100000);
  cap = 0;
}

void graph::insert(string id, string destID, int cost)
{
  node *temp, *tempD;
  edge tempEdge;
  if (tableID->contains(id))
    temp = (node *) tableID->getPointer(id);
  else
  {
    temp = new node;
    cap++;
    temp -> id = id;
    temp -> known =false;
    temp -> dist = std::numeric_limits<int>::max();
    vertices.push_back(temp);
    tableID->insert(id, temp);
  }
  if (tableID->contains(destID))
    tempD = (node *) tableID->getPointer(destID);
  else
  {
    tempD = new node;
    cap++;
    tempD -> id = destID;
    tempD -> known =false;
    tempD -> dist = std::numeric_limits<int>::max();
    vertices.push_back(tempD);
    tableID->insert(destID, tempD);
  }
  tempEdge.cost = cost;
  tempEdge.dest = tempD;
  temp->adj.push_back(tempEdge);
}

int graph::dijkstra(std::string &startNode)
{
  node *temp;
  node *start = (node *) tableID -> getPointer(startNode);
  start->paths.push_back(startNode);
  start->dist = 0;
  heap edges(cap);
  edges.insert(startNode, start->dist, start);

  for (std::list<node *>::const_iterator it = vertices.begin(); it != vertices.end(); ++it)
  {
    if((*it)->id != startNode)
      edges.insert((*it)->id, (*it)->dist, *it);
  }
  for (int i = 0; i < cap; i++)
  {
    edges.deleteMin(nullptr, nullptr, &temp);
    for(std::list<edge>::const_iterator it = temp->adj.begin(); it != temp->adj.end() && temp->dist != std::numeric_limits<int>::max(); ++it)
    {
      int curDist = it->cost + temp->dist;
      if (!(it->dest->known) && (it->dest->dist) > curDist)
      {
        it->dest->paths.clear();
        it->dest->paths.insert(it->dest->paths.begin(), temp->paths.begin(), temp->paths.end());
        it->dest->paths.push_back(it->dest->id);

        it->dest->dist = (curDist);
        edges.setKey(it->dest->id, curDist);
      }
    }
    temp->known = true;
  }
  return 1;
}

void graph::outputGen(std::ofstream &outfile)
{
  for(std::list<node *>::const_iterator it = vertices.begin(); it != vertices.end(); ++it)
  {
    outfile << (*it)->id << ": ";
    if((*it) -> dist != std::numeric_limits<int>::max())
    {
      outfile << (*it)->dist << " [";
      for (std::list<std::string>::const_iterator i = (*it)->paths.begin(); i != (*it)->paths.end(); ++i)
      {
        outfile << (*i);
        if (std::next(i, 1) != (*it)->paths.end())
          outfile << ", ";
      }
      outfile << "]" << "\n";
    }
    else
      outfile << "NO PATH" << '\n';
  }
}

void graph::prompt()
{
  std::string graphFile, node1, node2, pathCost, startingNode, outputPath;
  std::cout << "Enter name of graph file: ";
  std::cin >> graphFile;
  std::ifstream graphInput (graphFile.c_str());

  if(graphInput.is_open())
  {
    while(graphInput >> node1 >> node2 >> pathCost)
      insert(node1, node2, stoi(pathCost));
    graphInput.close();
  }
  while(!tableID->contains(startingNode))
  {
    std::cout << "Enter a valid vertix ID for the starting vertex: ";
    std::cin >> startingNode;
  }

  clock_t begin = clock();
  dijkstra(startingNode);
  clock_t end = clock();
  double timeDif = ((double)(end-begin))/CLOCKS_PER_SEC;
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "Total time (in seconds) to apply dijkstra's algorithm: " << timeDif << '\n';
  std::cout << "Enter name of of output file: ";
  std::cin >> outputPath;

  std::ofstream outputFile(outputPath.c_str());
  outputGen(outputFile);
  outputFile.close();
}
