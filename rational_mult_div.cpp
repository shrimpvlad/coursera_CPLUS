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

const Rational operator*(const Rational &r1, const Rational &r2)
{
    int n = 0, d = 1;
    n = r1.Numerator() * r2.Numerator();
    d = r1.Denominator() * r2.Denominator();
    return Rational(n, d);
}
const Rational operator/(const Rational &r1, const Rational &r2)
{
    int n = 0, d = 1;
    n = r1.Numerator() * r2.Denominator();
    d = r1.Denominator() * r2.Numerator();
    return Rational(n, d);
}

int main()
{
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal)
        {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal)
        {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
