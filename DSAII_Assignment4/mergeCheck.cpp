#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

std::string a, b, ab, input, output;
int countA, countB, i;
std::vector< std::vector<bool> > status(1001, std::vector<bool> (1001));

int main()
{
  std::cout << "Enter name of input file: ";
  std::cin >> input;
  std::cout << "Enter name of output file: ";
  std::cin >> output;
  std::ifstream infile(input);
  std::ofstream outfile(output);
  while (infile >> a && infile >> b && infile >> ab)
  {
    i = countA = countB = 0;
    if (a.length() + b.length() != ab.length())
      outfile << "*** NOT A MERGE ***" << '\n';
    else
    {
      while(i < ab.length() && (countA < a.length() || countB < b.length()))
      {
        if (i < 0)
          break;
        else if (ab[i] == a[countA] && !(status[countA+1][countB]))
        {
          countA++;
          status[countA][countB] = true;
        }
        else if (ab[i] == b[countB] && !(status[countA][countB+1]))
        {
          countB++;
          status[countA][countB] = true;
        }
        else
        {
          if (countA != 0 && status[countA-1][countB])
            countA--;
          else if (countB != 0 && status[countA][countB-1])
            countB--;
          else
            break;
          i--;
          continue;
        }
        i++;
      }
      if(status[a.length()][b.length()])
      {
        for (int j = ab.length()-1; j >= 0; j--)
        {
          if(status[countA-1][countB] || (countA == 1 && countB == 0))
          {
            ab[j] = toupper(ab[j]);
            countA--;
          }
          else if (countB != 0 && status[countA][countB-1])
            countB--;
          else
            break;
          }
          outfile << ab << '\n';
        }
      else
        outfile << "*** NOT A MERGE ***" << '\n';
      fill(status.begin(), status.end(), std::vector<bool> (1001, false));
    }
  }
  return 0;
}
