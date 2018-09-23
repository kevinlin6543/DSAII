#include "hash.h"

using namespace std;

hashTable::hashTable(int size)
{
  filled = 0;
  capacity = getPrime(size*2);
  data.resize(capacity);
}

int hashTable::insert(const std::string &key, void *pv /*= NULL*/)
{
  int i = hash(key) % capacity;
  if (contains(key))
    return 1;
  while (data[i].isOccupied)
  {
    i++;
    if (i >= capacity) // Loops the index back to zero for collisions
      i = 0;
  }
  filled++;
  if (filled >= capacity/2) // Checks to see if rehash is needed
    rehash();
  data[i].key = key;
  data[i].pv = pv;
  data[i].isDeleted = false;
  data[i].isOccupied = true;
}

bool hashTable::contains(const std::string &key)
{
  if (findPos(key) >= 0)
    return 1;
  else
    return 0;
}

void *hashTable::getPointer(const std::string &key, bool *b /*= NULL*/)
{
  int i = this->findPos(key);
  if (i != -1)
  {
    if (b != nullptr)
      *b = true;
    return data[i].pv;
  }
  else
  {
    if (b != nullptr)
      *b = false;
    return nullptr;
  }
}

int hashTable::setPointer(const std::string &key, void *py)
{
  int i = this -> findPos(key);
  if (i != -1)
  {
    data[i].pv =py;
    return 0;
  }
  else
    return 1;
}

bool hashTable::remove(const std::string &key)
{
 int i = findPos(key);
 if (i >= 0)
 {
   data[i].isDeleted = 1; // Lazy Deletion for collisions
   data[i].isOccupied = 0;
   return true;
 }
 return false;
}

unsigned int hashTable::hash(const std::string &key)
{
  // DEK hash function
  unsigned int l = key.length();
  unsigned int hash = l;
  for (int i = 0; i < l; i++)
    hash = ((hash << 5) ^ (hash >> 27)) ^ (key[i]);
  return hash;
}

int hashTable::findPos(const std::string &key)
{
  int i = hash(key) % capacity;
  while(data[i].isOccupied || data[i].isDeleted)
  {
    if (data[i].key.compare(key) == 0)
      return i;
    i++;
    if (i >= capacity) // Loops the index back to zero when reaching capacity
      i = 0;
  }
  return -1;
}

bool hashTable::rehash()
{
  vector<hashItem> temp = data; // Creates Duplicate placeholder vector
  int cap = capacity;
  capacity = getPrime(cap * 2);
  filled = 0;
  int i;

  for(i = 0; i < cap; i++) // resets the data in the vector
  {
    data[i].isOccupied = false;
    data[i].isDeleted = true;
  }

  data.resize(capacity);
  for(i = 0; i < cap; i++)
  {
    if(!temp[i].isDeleted && temp[i].isOccupied)
      insert(temp[i].key, temp[i].pv);
  }

}

unsigned int hashTable::getPrime(int size)
{
  unsigned int primes[] = {977, 1973, 3907, 7817, 15629, 31253, 62501, 125003, 250007, 500009, 1000003, 2000003, 4000023, 8000009, 16000057, 32000011, 64000031, 128000003, 256000001};
  int j = 0;
  while (primes[j] < size && j < primes.size())
    j++;
  return primes[j];
}
