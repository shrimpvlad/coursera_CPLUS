#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s)
{
  os << "{";
  bool first = true;
  for (const auto &x : s)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
  os << "{";
  bool first = true;
  for (const auto &x : s)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
  os << "{";
  bool first = true;
  for (const auto &kv : m)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
  if (t != u)
  {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty())
    {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string &hint)
{
  AssertEqual(b, true, hint);
}

class TestRunner
{
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string &test_name)
  {
    try
    {
      func();
      cerr << test_name << " OK" << endl;
    }
    catch (exception &e)
    {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
    catch (...)
    {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner()
  {
    if (fail_count > 0)
    {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

// int gcd(int a, int b)
// {
//   return b ? gcd(b, a % b) : a;
// }

// class Rational
// {
// public:
//   // Вы можете вставлять сюда различные реализации,
//   // чтобы проверить, что ваши тесты пропускают корректный код
//   // и ловят некорректный

//   Rational()
//   {
//     numerat = 0;
//     denominat = 1;
//   }
//   Rational(int numerator, int denominator)
//   {
//     if (numerator == 0)
//     {
//       denominat = 1;
//       numerat = 0;
//     }
//     else if (numerator > 0 && denominator < 0)
//     {
//       numerat = -numerator;
//       denominat = -denominator;
//       // cout<<"numer = "<<numerat<<"denom = "<<denominat<<endl;
//       int g = gcd(-numerat, denominat);
//       numerat /= g;
//       denominat /= g;
//     }
//     else {
//       int g = gcd(numerator, denominator);
//       if (numerator < 0 && denominator > 0) {
//         if (g<0) {
//           numerat = - numerator / g;
//           denominat = - denominator / g;
//         }
//         else {
//           numerat = numerator / g;
//           denominat = denominator / g;
//         }
        
//       }
//       else if (numerator < 0 && denominator < 0)
//       {
//         if (g < 0)
//         {
//           numerat = numerator / g;
//           denominat = denominator / g;
//         }
//         else
//         {
//           numerat = -numerator / g;
//           denominat = -denominator / g;
//         }
//       }
//       else {
//         numerat = numerator / g;
//         denominat = denominator / g;
//       }
        
//       // cout << "numer = " << numerat << "denom = " << denominat << endl;
//     }
//   }
//   int Numerator() const
//   {
//     return numerat;
//   }

//   int Denominator() const
//   {
//     return denominat;
//   }

// private:
//   int numerat, denominat;
// };

void TestRationalDefaultConstructor()
{
  Rational rational;

  AssertEqual(rational.Numerator(), 0, "Check numerator");
  AssertEqual(rational.Denominator(), 1, "Check denominator");
}

void TestRationalConstructor()
{
  Rational rational(13, 12);
  AssertEqual(rational.Numerator(), 13, "No reducing");
  AssertEqual(rational.Denominator(), 12, "No reducing");

  rational = Rational(12, 4);
  AssertEqual(rational.Numerator(), 3, "3/1");
  AssertEqual(rational.Denominator(), 1, "3/1");

  rational = Rational(1, 1024);
  AssertEqual(rational.Numerator(), 1, "1/1024");
  AssertEqual(rational.Denominator(), 1024, "1/1024");

  rational = Rational(17, 289);
  AssertEqual(rational.Numerator(), 1, "1/17");
  AssertEqual(rational.Denominator(), 17, "1/17");

  rational = Rational(-3, 15);
  AssertEqual(rational.Numerator(), -1, "-1/5");
  AssertEqual(rational.Denominator(), 5, "-1/5");

  rational = Rational(2, -2);
  AssertEqual(rational.Numerator(), -1, "-1/1");
  AssertEqual(rational.Denominator(), 1, "-1/1");

  rational = Rational(-2, -3);
  AssertEqual(rational.Numerator(), 2, "2/3");
  AssertEqual(rational.Denominator(), 3, "2/3");

  rational = Rational(0, 10);
  AssertEqual(rational.Numerator(), 0, "0/1");
  AssertEqual(rational.Denominator(), 1, "0/1");

  rational = Rational(0, -1);
  AssertEqual(rational.Numerator(), 0, "0/1");
  AssertEqual(rational.Denominator(), 1, "0/1");
}

int main()
{
  TestRunner runner;
  runner.RunTest(TestRationalDefaultConstructor, "TestRationalDefaultConstructor");
  runner.RunTest(TestRationalConstructor, "TestRationalConstructor");
  return 0;
}
