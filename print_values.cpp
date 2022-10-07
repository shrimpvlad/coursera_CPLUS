#include "test_runner.h"

#include <iostream>
#include <vector>
#include <iomanip>
// using namespace std;

// #define PRINT_VALUES(out, x, y) { \
//   out << (x) << endl; \
//   out << (y) << endl; \
// }

// #include <iostream>
// #include <iomanip>

#define PRINT_VALUES(out, x, y) out << (x) << endl \
                                    << (y) << endl

int main()
{
  int32_t a = 1, b = 2;
  int32_t c = 3, d = 4;
  bool flag = false;
  if (flag)
    PRINT_VALUES(std::cout, a, b);
  else
  {
    PRINT_VALUES(std::cout, c, d);
    int a1 = -3, a2 = -4;
    PRINT_VALUES(std::cout, a1, a2);
  }
}