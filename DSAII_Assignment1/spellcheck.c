#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <fstream>

int main(int argc, char const *argv[]) {
  string dict;
  std::cout << "Enter name of dictionary: "
  getline(std::cin, dict);
  ifstream inFile;
  inFile.open(dict);
  hashTable dictionary = new hashTable;
  while (inFile >> word)
  {
    dictionary.insert(word);
  }



  return 0;
}
