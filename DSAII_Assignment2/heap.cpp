#include "heap.h"

using namespace std;

heap::heap(int capacity)
{
  size = 0;
  hashT = new hashTable(capacity * 2);
  data.resize(capacity + 1);
  this->cap = capacity;
}

int heap::insert(const std::string &id, int key, void *pv)
{
  if (size >= cap)
    return 1;
  if (hashT->contains(id))
    return 2;


  node *temp;
  temp->key = key;
  temp->id = id;
  temp->pv = pv;
  size++;
  hashT->insert(id, &data[size]);
  data[size] = *temp;

  percolateUp(size);


  return 0;
}

int heap::setKey(const std::string &id, int key)
{
  std::cerr << "Reaches setkey" << '\n';
  if(!(hashT->contains(id)))
    return 1;
  node *temp = (node *)hashT -> getPointer(id);
  int tmp = temp -> key;
  temp -> key = key;
  int p = getPos(temp);
  std::cerr << "got to set pointer" << '\n';
  hashT->setPointer(data[p].id, &data[p]);

  if (key > tmp)
    percolateDown(p);
  if (tmp > key)
    percolateUp(p);

  return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
  if(size == 0)
    return 1;
  hashT->remove(data[1].id);
  if(pId != nullptr)
    *pId = data[1].id;
  if(pKey != nullptr)
    *pKey = data[1].key;
  if(ppData != nullptr)
    *(void **)ppData = data[1].pv;
  size--;
  data[1] = data[size];
  percolateDown(1);
  return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
  if(!(hashT->contains(id)))
    return 1;
  node *temp = (node *)hashT->getPointer(id);
  int o =temp -> key;
  int i = temp - &data[0];
  if(pKey != nullptr)
    *pKey = o;
  if(ppData != nullptr)
    *(void **)ppData = temp -> pv;

  hashT->remove(id);
  data[i] = data[size--];
  int n = data[i].key;

  if (n > o)
    percolateDown(i);
  if (o > n)
    percolateUp(i);
  return 0;
}

int heap::getPos(node *n)
{
  return (n-&data[0]);
}
void heap::percolateUp(int i)
{
  node temp = data[i];
  int p = i/2;
  while (i > 1  && data[p].key > temp.key)
  {
    //int p = getParent(data[i]);
    data[i] = data[p];
    hashT->setPointer(data[i].id, &data[i]);
    i = p;
    p = i/2;
  }
  data[i] = temp;
}

void heap::percolateDown(int i)
{
  node temp = data[i];
  int c = 0;
  while ( (c = 2*i) <= size)
  {
    if (c < size && data[c].key > data[c+1].key)
      ++c;
    if (temp.key > data[c].key)
    {
      data[i] = data[c];
      hashT->setPointer(data[i].id, &data[i]);
    }
    else
      break;
    i = c;
  }
  data[i] = temp;
  hashT->setPointer(data[i].id, &data[i]);
}
