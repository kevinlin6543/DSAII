#include "hash.h"

using namespace std;

int main()
{
  string dict, word, wordIn, buf, iname, oname;
  ifstream inFile, input;
  ofstream output;
  bool ignore, longOut;
  int lineNum = 0;
  int len;

  hashTable *dictionary = new hashTable(1973);

  std::cout << "Enter name of dictionary: ";
  getline(cin, dict);
  inFile.open(dict);
  if (!inFile)
  {
    std::cout << "Error: Unable to open file, " << dict << ", for reading." << '\n';
    return -1;
  }

  clock_t before = clock();
  while (inFile >> word) // Checks the file looking for one word in each line
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    dictionary->insert(word, NULL);
  }
  clock_t after = clock();
  std::cout << "Total time (in seconds) to load dictionary: " << (double)(after - before)/CLOCKS_PER_SEC << '\n';

  std::cout << "Enter name of input file: ";
  getline(cin, iname);
  input.open(iname);
  if (!input)
  {
    std::cout << "Error: Unable to open file, " << iname << ", for reading." << '\n';
    return -1;
  }

  std::cout << "Enter name of output file: ";
  getline(cin, oname);
  output.open(oname);
  if (!output)
  {
    std::cout << "Error: Unable to open file, " << oname << ", for writing." << '\n';
    return -1;
  }

  before = clock();
  while(getline(input, buf))
  {
    lineNum++;
    wordIn.clear();
    len = 0;
    longOut = false;
    ignore = false;

    for (int i = 0; i <= buf.size(); i++)
    {
      if (isalnum(buf[i]) || buf[i] == '\'' || buf[i] == '-')
      {
        if (isdigit(buf[i]))
          ignore = true; // Sets the ignore flag if there is a digit in the word
        if(++len <= 20)
          wordIn += buf[i];
        else
        {
          if(!longOut)
            {
              transform(wordIn.begin(), wordIn.end(), wordIn.begin(), ::tolower);
              output << "Long word at line " << lineNum << ", starts: " << wordIn << endl;
              longOut = true; //Prevents Duplicate long word outputs
            }
            ignore = true; // Set to ignore long words for hashtable check
        }
      }
      else
      {
        if (ignore) // Resets the booleans for supressing output and ignoring words
        {
          ignore = false;
          longOut = false;
        }
        else
        {
          transform(wordIn.begin(), wordIn.end(), wordIn.begin(), ::tolower);
          if(len > 0 && !(dictionary->contains(wordIn))) // Checks for the word and makes sure the word length is not zero
            output << "Unknown word at line " << lineNum << ": " << wordIn << endl;
        }
        len = 0;
        wordIn.clear(); // Resets the word being checked
      }
    }
  }
  after = clock();
  std::cout << "Total time (in seconds) to load dictionary: " << (double)(after - before)/CLOCKS_PER_SEC << '\n';
  return 0;
}
