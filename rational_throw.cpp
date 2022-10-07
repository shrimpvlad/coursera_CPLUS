#include <iostream>
#include <exception>
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
        if (denominator == 0)
        {
            throw invalid_argument("zero denominator");
        }
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

const Rational operator/(const Rational &r1, const Rational &r2)
{
    int n = 0, d = 1;
    n = r1.Numerator() * r2.Denominator();
    d = r1.Denominator() * r2.Numerator();
    if (d == 0)
        throw domain_error("zero denominator");
    return Rational(n, d);
}

int main()
{
    try
    {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    }
    catch (invalid_argument &)
    {
    }

    try
    {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    }
    catch (domain_error &)
    {
    }

    cout << "OK" << endl;
    return 0;
}
