#pragma once

#include <istream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
using namespace std;

namespace Ini
{

using Section = unordered_map<string, string>;

class Document {
public:
  Section& AddSection(string name);
  const Section& GetSection(const string& name) const;
  size_t SectionCount() const;

private:
  unordered_map<string, Section> sections;
};

Document Load(istream& input);

}
