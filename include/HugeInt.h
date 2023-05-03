//
// Created by hattonjd on 5/3/2023.
//

#ifndef HUGEINT_HUGEINT_H
#define HUGEINT_HUGEINT_H


#include <vector>
#include <iostream>

class HugeInt {
private:
    std::vector<unsigned int> digits;
    const static unsigned int BASE = 10; // The base of the number system
public:
    HugeInt() : digits(1, 0) {} // Default constructor
    HugeInt(const HugeInt& other) = default; // Copy constructor
    explicit HugeInt(unsigned long long value); // Constructor from unsigned long long value
    explicit HugeInt(const std::string& str); // Constructor from string representation
    HugeInt& operator=(const HugeInt& other) = default; // Assignment operator
    HugeInt operator+(const HugeInt& other) const; // Addition operator
    HugeInt operator-(const HugeInt& other) const; // Subtraction operator
    HugeInt operator*(const HugeInt& other) const; // Multiplication operator
    HugeInt operator/(const HugeInt& other) const; // Division operator
    bool operator==(const HugeInt& other) const; // Equality operator
    bool operator!=(const HugeInt& other) const; // Inequality operator
    bool operator<(const HugeInt& other) const; // Less-than operator
    bool operator>(const HugeInt& other) const; // Greater-than operator
    bool operator<=(const HugeInt& other) const; // Less-than or equal-to operator
    bool operator>=(const HugeInt& other) const; // Greater-than or equal-to operator
    friend std::ostream& operator<<(std::ostream& os, const HugeInt& hugeint); // Output stream operator
private:
    void trim(); // Remove leading zeroes from the internal digits vector
};


#endif //HUGEINT_HUGEINT_H
