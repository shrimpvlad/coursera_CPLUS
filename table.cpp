#include "test_runner.h"
#include <vector>
// #include 
using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table
{
public:
  Table(size_t row, size_t col)
  {
    Resize(row, col);
  }
  void Resize(size_t rows, size_t columns)
  {
    matr.resize(rows);
    for (auto &item : matr)
    {
      item.resize(columns);
    }
  }
  const vector<T> &operator[](size_t idx) const
  {
    return matr[idx];
  }
  vector<T> &operator[](size_t idx)
  {
    return matr[idx];
  }
  pair<size_t, size_t> Size() const
  {
    if (!matr.empty() && !matr[0].empty())
    {
      return {matr.size(), matr[0].size()};
    }

    return {0, 0};
  }

private:
  vector<vector<T> > matr;
};

void
TestTable()
{
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
