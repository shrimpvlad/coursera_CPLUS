#include "test_runner.h"
#include "profile.h"
#include <array>
#include <iostream>
#include <iterator>
#include <utility>
#include <random>
#include <unordered_map>
using namespace std;

struct pair_hash
{
    size_t operator() (const pair<int, int> &pair) const {
        size_t h1 = hash<int>{}(pair.first);
        size_t h2 = hash<int>{}(pair.second);
        return h1^h2;
    }
};

int MAX_NUMBER = 1000;

int main() {
    vector<pair<int,int>> vec;
    for (int x = 0; x < MAX_NUMBER; ++x)
    {
        for (int y = 0; y < MAX_NUMBER; ++y)
        {
            vec.push_back({x^y, (x + y)*37});
        }
    }
    {
        LOG_DURATION("Unordered map");
        long long max = 0;
        unordered_map<pair<int,int>, int, pair_hash> um;
        for (auto v: vec)
        {
            um[v]++;
            if (um[v]>max)
                max = um[v];
        }
        cout<<"max = "<<max<<endl;
    }
    {
        LOG_DURATION("Map");
        long long max = 0;
        map<pair<int,int>, int> m;
        for (auto v: vec)
        {
            m[v]++;
            if (m[v]>max)
                max = m[v];
        }
        cout<<"max = "<<max<<endl;
    }
    return 0;
}
