#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

std::string a, b, ab, file;
int countA, countB, i;
std::vector< std::vector<bool> > arr(40, std::vector<bool> (40));

int main()
{
  std::cout << "Enter File Name: ";
  std::cin >> file;
  std::ifstream infile(file);
  while (infile >> a && infile >> b && infile >> ab)
  {
    //std::cout << "a = " << a << " | length = " << a.length() << '\n';
    //std::cout << "b = " << b << " | length = " << b.length() <<'\n';
    //std::cout << "ab = "<< ab << " | length = " << ab.length() <<'\n';
    i = 0;
    countA = 0;
    countB = 0;
    while(i < ab.length() && (countA < a.length() || countB < b.length()))
    {
      //std::cerr << i << '\n';
      //std::cerr << "count A = " << countA << '\n';
      //std::cerr << "count B = " << countB << '\n';
      if (i < 0)
        break;
      else if (ab[i] == a[countA] && !(arr[countA+1][countB]))
      {
        countA++;
        arr[countA][countB] = true;
      }
      else if (ab[i] == b[countB] && !(arr[countA][countB+1]))
      {
        countB++;
        arr[countA][countB] = true;
      }
      else
      {
        if (countA != 0 && arr[countA-1][countB])
          countA--;
        else if (countB != 0 && arr[countA][countB-1])
          countB--;
        else
          break;
        i--;
        continue;
      }
      i++;
    }
    /*for (int i = 0; i < arr.size(); i++)
    {
      for (int j = 0; j < arr[i].size(); j++)
      {
          std::cout << arr[i][j] << " ";
      }
      std::cout << '\n';
    }*/
    //std::cerr << arr[a.length()][b.length()]<< '\n';
    if(arr[a.length()][b.length()])
      std::cerr << "Merge Detected" << '\n';
    else
      std::cerr << "no merge" << '\n';
    fill(arr.begin(), arr.end(), std::vector<bool> (40, false));
  }

  return 0;
}
