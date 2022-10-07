#include <iostream>

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

const Rational operator+(const Rational &r1, const Rational &r2)
{
    int n = 0, d = 1;
    n = r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator();
    d = r1.Denominator() * r2.Denominator();
    return Rational(n, d);
}

const Rational operator-(const Rational &r1, const Rational &r2)
{
    int n = 0, d = 1;
    n = r1.Numerator() * r2.Denominator() - r2.Numerator() * r1.Denominator();
    d = r1.Denominator() * r2.Denominator();
    return Rational(n, d);
}

int main()
{
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal)
        {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal)
        {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal)
        {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
