#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
using namespace std;

class Stats
{
public:
  Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int> &GetMethodStats() const;
  const map<string_view, int> &GetUriStats() const;

private:
  map<string_view, int> method_map;
  map<string_view, int> uri_map;
};

HttpRequest ParseRequest(string_view line);
