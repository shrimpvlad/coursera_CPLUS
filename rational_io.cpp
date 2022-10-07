#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <numeric>
#include <iostream>
#include <sstream>
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

istream &operator>>(istream &stream, Rational &r)
{
    int p = 0, q = 0;
    char c;
    if (stream >> p && stream >> c && (c == '/') && stream >> q)
    {
        r = {p, q};
    }
    return stream;
}

ostream &operator<<(ostream &stream, const Rational &r)
{
    stream << r.Numerator() << "/" << r.Denominator();
    return stream;
}

// Реализуйте для класса Rational операторы << и >>

int main()
{
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4")
        {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal)
        {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct)
        {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct)
        {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}
