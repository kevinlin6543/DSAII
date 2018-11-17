#include "heap.h"

using namespace std;
// Constructor for Heap using a set capacity. A hashTable is formed with twice the
// size in order to reduce the likelihood of a rehash
heap::heap(int capacity)
{
  size = 0;
  hashT = new hashTable(capacity * 2);
  data.resize(capacity + 1);
  this->cap = capacity;
}

// Insert takes the new data passed in and places it at the end of the data vector
// and percolates up
int heap::insert(const std::string &id, int key, void *pv)
{
  if (size >= cap)
    return 1;
  if (hashT->contains(id))
    return 2;
  size++;
  data[size].key = key;
  data[size].id = id;
  data[size].pv = pv;
  hashT->insert(id, &data[size]);
  percolateUp(size);
  return 0;
}

// Changes the key of an existing data member and adjusts the heap
int heap::setKey(const std::string &id, int key)
{
  if(hashT->contains(id))
  {
  node *temp = (node *)(hashT -> getPointer(id));
  int tmp = temp -> key;
  temp -> key = key;
  int p = temp - &data[0];
  hashT->setPointer(data[p].id, &data[p]);

  if (key > tmp)
    percolateDown(p);
  if (tmp > key)
    percolateUp(p);

    return 0;
  }
  else
    return 1;
}

// Removes the smallest key which should be at position one of the vector
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
  if(size == 0)
    return 1;
  if(pId != nullptr)
    *pId = data[1].id;
  if(pKey != nullptr)
    *pKey = data[1].key;
  if(ppData != nullptr)
    *(void **)ppData = data[1].pv;
  hashT->remove(data[1].id);
  data[1] = data[size];
  size-=1;
  percolateDown(1);
  return 0;
}

// Looks for a string id in the heap and removes the data member while placing the key
// value in a provided pointer.
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
  if(hashT->contains(id))
  {
    node *temp = (node *)(hashT->getPointer(id));
    int i = temp - &data[0];

    if(pKey != nullptr)
      *pKey = temp->key;
    if(ppData != nullptr)
      *(void **)ppData = temp -> pv;

    hashT->remove(id);
    int o = temp -> key;
    data[i] = data[size--];
    int n = data[i].key;


    if (n < o)
      percolateUp(i);
    if (o < n)
      percolateDown(i);
    return 0;
  }
  else
    return 1;
}

// Private function used to move a node up to the proper position if the key value is
// less than the parent
void heap::percolateUp(int i)
{
  node temp = data[i];
  while (i > 1  && temp.key < data[i/2].key)
  {
    data[i] = data[i/2];
    hashT->setPointer(data[i].id, &data[i]);
    i /= 2;
  }
  data[i] = temp;
  hashT-> setPointer(data[i].id, &data[i]);
}

// Private function used to move a data member down if the key is greater than the
// child node
void heap::percolateDown(int i)
{
  node temp = data[i];
  int c = 0;
  int l, r;
  while ( (2*i) <= size)
  {
    l = 2*i;
    r = l + 1;
    if (l < size && data[r].key < data[l].key )
      c = r;
    else
      c = l;

    if (data[c].key < temp.key)
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
