#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin <= 2)
        return;
    vector<typename RandomIt::value_type> vec;
    move(range_begin, range_end, back_inserter(vec));
    size_t chunk = (range_end - range_begin)/3;
    MergeSort(range_begin, range_begin+chunk);
    MergeSort(range_begin + chunk, range_begin + 2*chunk);
    MergeSort(range_begin + 2*chunk, range_end);
    vector<typename RandomIt::value_type> tmp;
    merge(make_move_iterator(range_begin), make_move_iterator(range_begin + chunk), make_move_iterator(range_begin + chunk), make_move_iterator(range_begin + 2*chunk), back_inserter(tmp));
    merge(make_move_iterator(tmp.begin()), make_move_iterator(tmp.end()), make_move_iterator(range_begin + 2*chunk), make_move_iterator(range_end), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
