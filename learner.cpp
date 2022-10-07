// #include <algorithm>
// #include <string>
// #include <set>
// #include <vector>
// #include <iostream>
// #include <sstream>

// using namespace std;

// class Learner
// {
// private:
//   set<string> dict;

// public:
//   int Learn(const vector<string> &words)
//   {
//     set<string> word(words.begin(), words.end());
//     int count = dict.size();
//     for (auto i : word)
//       dict.insert(i);
//     return dict.size() - count;
//   }

//   vector<string> KnownWords()
//   {
//     vector<string> v(dict.begin(), dict.end());
//     return v;
//   }
// };

// int main()
// {
//   Learner learner;
//   string line;
//   while (getline(cin, line))
//   {
//     vector<string> words;
//     stringstream ss(line);
//     string word;
//     while (ss >> word)
//     {
//       words.push_back(word);
//     }
//     cout << learner.Learn(words) << "\n";
//   }
//   cout << "=== known words ===\n";
//   for (auto word : learner.KnownWords())
//   {
//     cout << word << "\n";
//   }
// }
#include <set>
#include <string>
#include <vector>

using namespace std;

class Learner
{
private:
  set<string> dict;

public:
  int Learn(const vector<string> &words)
  {
    int newWords = 0;
    for (const auto &word : words)
    {
      if (dict.find(word) == dict.end())
      {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() const
  {
    return {dict.begin(), dict.end()};
  }
};