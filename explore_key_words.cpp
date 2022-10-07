#include "test_runner.h"
#include "profile.h"

#include <set>
// #include "explore_key_words.h"
// #include "paginator.h"
#include <functional>
#include <future>
#include <sstream>

using namespace std;

struct Stats
{
  map<string, int> word_frequences;

  void operator+=(const Stats &other)
  {
    for (auto &[key, value] : other.word_frequences)
    {
      word_frequences[key] += value;
    }
  }
};
// asa     ggggggg  ffdsg
Stats Split(const set<string> &key_words, const string &line)
{
  string_view line_view = line;
  Stats result;
  size_t pos = line_view.find_first_not_of(' ');
  line_view.remove_prefix(pos);
  while (pos != line_view.npos)
  {
    pos = line_view.find_first_of(' ');
    auto key = string(line_view.substr(0, pos));
    if (key_words.count(key) > 0)
    {
      ++result.word_frequences[move(key)];
    }
    if (pos == line_view.npos)
      break;
    line_view.remove_prefix(pos);
    pos = line_view.find_first_not_of(' ');
    line_view.remove_prefix(pos);
  }
  return result;
}
Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input)
{
  Stats res;
  string line;
  while (getline(input, line))
  {
    res += Split(key_words, line);
  }
  return res;
}
Stats ExploreKeyWords(const set<string> &key_words, istream &input)
{
  Stats res;
  vector<future<Stats> > futures;
  string line;
  vector<stringstream> data(4);
  size_t i = 0;
  while (getline(input, line))
  {
    data[i % 4] << line << '\n';
    ++i;
  }
  for (auto &d : data)
  {
    futures.push_back(async(
        [&]
        {
          return ExploreKeyWordsSingleThread(key_words, d);
        }));
  }
  for (auto &f : futures)
    res += f.get();
  return res;
}

void TestBasic()
{
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
      {"yangle", 6},
      {"rocks", 2},
      {"sucks", 1}};
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
