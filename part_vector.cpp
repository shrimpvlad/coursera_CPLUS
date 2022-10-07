#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    auto it = find_if(numbers.begin(), numbers.end(), [](const int &number){ return number<0; });
    if (it != numbers.end())
    {
        for (auto i = it-1; i >= numbers.begin(); --i)
        {
            cout<<*i<<" ";
        }
    }
    else
    {
        for (auto i = numbers.rbegin(); i!= numbers.rend(); ++i)
            cout<<*i<<" ";
    }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
