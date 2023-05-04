//
// Created by hattonjd on 5/3/2023.
//

#ifndef HUGEINT_HUGEINT_H
#define HUGEINT_HUGEINT_H


#include <vector>
#include <iostream>

class HugeInt {
private:
    bool negative = false;
    std::vector<unsigned int> digits;
    const static unsigned int BASE = 10; // The base of the number system
public:
    HugeInt() : digits(1, 0) {} // Default constructor
    HugeInt(const HugeInt& other) = default; // Copy constructor
    ~HugeInt() = default;
    void resetDigits();
    void setValue(int num); // Change Value of HugeInt
    void setValue(const std::string& str);
    explicit HugeInt(unsigned long long value); // Constructor from unsigned long long value
    explicit HugeInt(const std::string& str); // Constructor from string representation
    HugeInt& operator=(const HugeInt& other) = default; // Default Assignment operator
    HugeInt operator+(const HugeInt& other) const; // Addition operator
    HugeInt operator-(const HugeInt& other) const; // Subtraction operator
    HugeInt operator*(const HugeInt& other) const; // Multiplication operator
    HugeInt operator/(const HugeInt& other) const; // Division operator
    HugeInt operator^(const HugeInt& other) const; // Exponent operator
    HugeInt operator%(const HugeInt& other) const; // Modulus operator
    HugeInt operator-() const; // Unary negative operator
    bool operator==(const HugeInt& other) const; // Equality operator
    bool operator!=(const HugeInt& other) const; // Inequality operator
    bool operator<(const HugeInt& other) const; // Less-than operator
    bool operator>(const HugeInt& other) const; // Greater-than operator
    bool operator<=(const HugeInt& other) const; // Less-than or equal-to operator
    bool operator>=(const HugeInt& other) const; // Greater-than or equal-to operator
    HugeInt& operator+=(const HugeInt& other); // AddSub To operator
    HugeInt& operator-=(const HugeInt& other); // Subtract From operator
    HugeInt& operator*=(const HugeInt& other); // Multiply By operator
    HugeInt& operator/=(const HugeInt& other); // Divide By operator
    HugeInt& operator^=(const HugeInt& other); // Power Of operator
    HugeInt& operator%=(const HugeInt& other); // Modulus With operator
    friend std::ostream& operator<<(std::ostream& os, const HugeInt& hugeint); // Output stream operator
private:
    void trim(); // Remove leading zeroes from the internal digits vector
};


#endif //HUGEINT_HUGEINT_H
