#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

string a, b, ab, file;

int main()
{
  program dynamic;
  dynamic.start();
  std::ifstream infile(file);
  while (infile >> a && infile >> b && infile >> ab)
  {
    int countA, countB;
    std::vector<bool> arr[a.length()][b.length()];
    for(int i = 0; i < ab.length() || countA < a.length() || countB < b.length();i++)
    {
        if (ab[i] == a[countA] && arr[countA+1][countB])
        {
          countA++;
          arr[countA][countB] = 1;
        }
        else if (ab[i] == b[countB] && arr[countA][countB+1] != 1)
        {
          countB++;
          arr[countA][countB] = 1;
        }
        else
        {
          i--;
        }
    }

  }
  return 0;
}
