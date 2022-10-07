#include "stats.h"
#include "http_request.h"
#include <string_view>
#include <vector>
#include <map>
using namespace std;

Stats::Stats()
{
    method_map["GET"] = 0;
    method_map["POST"] = 0;
    method_map["PUT"] = 0;
    method_map["DELETE"] = 0;
    method_map["UNKNOWN"] = 0;

    uri_map["unknown"] = 0;
    uri_map["/"] = 0;
    uri_map["/order"] = 0;
    uri_map["/product"] = 0;
    uri_map["/basket"] = 0;
    uri_map["/help"] = 0;
}
void Stats::AddMethod(string_view method)
{
    if (method_map.count(method) > 0)
        method_map[method] += 1;
    else
        method_map["UNKNOWN"] += 1;
}
void Stats::AddUri(string_view method)
{
    if (uri_map.count(method) > 0)
        uri_map[method] += 1;
    else
        uri_map["unknown"] += 1;
}
const map<string_view, int> &Stats::GetMethodStats() const
{
    return method_map;
}
const map<string_view, int> &Stats::GetUriStats() const
{
    return uri_map;
}
HttpRequest ParseRequest(string_view line)
{
    auto pos = line.find_first_not_of(' ');
    line.remove_prefix(pos);

    pos = line.find(' ');
    const std::string_view method = std::string_view(line.data(), pos);
    line.remove_prefix(pos + 1);

    pos = line.find(' ');
    const std::string_view uri = std::string_view(line.data(), pos);
    line.remove_prefix(pos + 1);

    const std::string_view protocol = std::string_view(line.data());

    return {method, uri, protocol};
}