// Listing 29-5. Adding the Ability to Initialize a rational Object
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "test.hpp"
#include <ios>
#include <istream>
#include <sstream>
#include <ostream>

/// Compute the greatest common divisor of two integers, using Euclid’s algorithm.
int gcd(int n, int m)
{
    n = std::abs(n);
    while (m != 0) {
        int tmp(n % m);
        n = m;
        m = tmp;
    }
    return n;
}

/// Represent a rational number.
struct rational
{
    float as_float()
    {
        return static_cast<float>(numerator) / denominator;
    }

    double as_double()
    {
        return numerator / static_cast<double>(denominator);
    }

    long double as_long_double()
    {
        return static_cast<long double>(numerator) /
               static_cast<long double>(denominator);
    }
    /// Construct a rational object, given a numerator and a denominator.
    /// Always reduce to normal form.
    /// @param num numerator
    /// @param den denominator
    /// @pre denominator > 0
    rational(int num, int den)
            : numerator{num}, denominator{den}
    {
        reduce();
    }

    /// Construct a rational object, given a numerator.
    /// No need to reduce to normal form because denominator is always 1.
    /// @param num numerator
    rational(int num)
            : numerator{num}, denominator{1}
    {}

    rational(float num) : rational(static_cast<int>(num*10000), 10000){}

    rational() : numerator{0}, denominator{1}
    {}
    /// Assign a numerator and a denominator, then reduce to normal form.
    /// @param num numerator
    /// @param den denominator
    /// @pre denominator > 0
    void assign(int num, int den)
    {
        numerator = num;
        denominator = den;
        reduce();
    }

    /// Reduce the numerator and denominator by their GCD.
    void reduce()
    {
        assert(denominator != 0);
        if (denominator < 0)
        {
            denominator = -denominator;
            numerator = -numerator;
        }
        int div{gcd(numerator, denominator)};
        numerator = numerator / div;
        denominator = denominator / div;
    }

    rational& operator=(rational const& that){
        this->numerator = that.numerator;
        this->denominator = that.denominator;
        reduce();
        return *this;
    }

    rational& operator=(int num){
        this->numerator = num;
        this->denominator = 1;
        return *this;
    }
    // Default copy constructor
    rational(rational const&) = default;

    int numerator;     ///< numerator gets the sign of the rational value
    int denominator;   ///< denominator is always positive
};

/// Compare two rational numbers for equality
/// @pre @p a and @p b are reduced to normal form
bool operator==(rational const& a, rational const& b){
    return a.numerator == b.numerator and a.denominator == b.denominator;
}

///compare two rational number for inequality
/// @pre @p a and @p b are reduced to normal form
inline bool operator!=(rational const& a, rational const& b){
    return not (a==b);
}

/// compare two rational numbers for less-than
bool operator<(rational const& a, rational const& b){
    return a.numerator * b.numerator < b.numerator * a.denominator;
}

/// Compare two rational numbers for less-than-or-equal
inline bool operator<=(rational const& a, rational const& b){
    return not (b<a);
}

/// Compare two rational numbers for greater than
inline bool operator>(rational const& a, rational const&  b){
    return b < a;
}

/// Compare two rational number for >=
inline bool operator>=(rational const& a, rational const& b){
    return not (b>a);
}

rational operator+(rational const& lhs, rational const& rhs){
    return rational{lhs.numerator * rhs.denominator +rhs.numerator * lhs.denominator,
                lhs.denominator * rhs.denominator};
}

rational operator-(rational const& r){
    return rational{-r.numerator, r.denominator};
}

rational operator-(rational const& rhs, rational const& lhs){
    return {lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator,
    lhs.denominator * rhs.denominator};
}

rational operator*(rational const& lhs, rational const& rhs){
    return rational{lhs.numerator*rhs.numerator, lhs.denominator * rhs.denominator};
}

rational operator/(rational const& lhs, rational const& rhs){
    return rational{lhs.numerator * rhs.denominator, lhs.denominator* rhs.numerator};
}

rational absval(rational const& r) {
    return rational{std::abs(r.numerator), r.denominator};
}

rational operator*(rational const& rat, int mult)
{
    return rational{rat.numerator * mult, rat.denominator};
}

inline rational operator*(int mult, rational const& rat)
{
    return rat * mult;
}

//////////////////////////////////////////////////////////////////////
/// Input/Output operators
///Input operator for rational
std::istream& operator>>(std::istream& in, rational& rat)
{
    int n{0}, d{0};
    char sep{'\0'};
    if (not (in >> n >> sep))
        // Error reading the numerator or the separator character.
        in.setstate(std::cin.failbit);
    else if (sep != '/')
    {
        // Read numerator successfully, but it is not followed by /.
        // Push sep back into the input stream, so the next input operation
        // will read it.
        in.unget();
        rat.assign(n, 1);
    }
    else if (in >> d)
        // Successfully read numerator, separator, and denominator.
        rat.assign(n, d);
    else
        // Error reading denominator.
        in.setstate(std::cin.failbit);

    return in;
}
/// Ouput operator for rational
std::ostream& operator<<(std::ostream& out, rational const& rat)
{
    std::ostringstream tmp{""};
    tmp << rat.numerator;
    if (rat.denominator != 1)
        tmp << '/' << rat.denominator;
    out << tmp.str();

    return out;
}

/// Tests for failbit only
bool iofailure(std::istream& in)
{
    return in.fail() and not in.bad();
}


int main()
{
    rational r{0};

    while (std::cin)
    {
        if (std::cin >> r)
            // Read succeeded, so no failure state is set in the stream.
            std::cout << r << '\n';
        else if (iofailure(std::cin))
        {
            // Only failbit is set, meaning invalid input. Clear the state,
            // and then skip the rest of the input line.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    }

    if (std::cin.bad())
        std::cerr << "Unrecoverable input failure\n";
}
