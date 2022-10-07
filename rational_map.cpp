#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <iomanip>
#include <numeric>
using namespace std;

class Rational
{
public:
    Rational()
    {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator)
    {
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
        num = numerator / gcd(numerator, denominator);
        den = denominator / gcd(numerator, denominator);
    }

    int Numerator() const
    {
        return num;
    }

    int Denominator() const
    {
        return den;
    }

private:
    int num;
    int den;
};

const bool operator==(const Rational &r1, const Rational &r2)
{
    return (r1.Numerator() == r2.Numerator() && r1.Denominator() == r2.Denominator());
}

const bool operator<(const Rational &r1, const Rational &r2)
{
    int a, b;
    a = r1.Numerator() * r2.Denominator();
    b = r2.Numerator() * r1.Denominator();
    return a < b;
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

int main()
{
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3)
        {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs)
        {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}})
        {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2)
        {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
