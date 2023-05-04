//
// Created by hattonjd on 5/3/2023.
//

#include <HugeInt.h>

// Constructor from unsigned long long value
HugeInt::HugeInt(unsigned long long value) {
    while (value > 0) {
        digits.push_back(value % BASE);
        value /= BASE;
    }
    if (digits.empty()) {
        digits.push_back(0);
    }
}

// Constructor from string representation
HugeInt::HugeInt(const std::string& str) {
    int start = 0;
    if (str[0] == '-') {
        negative = true;
        start = 1;
    }
    for (int i = str.size() - 1; i >= start; i--) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            digits.push_back(c - '0');
        } else {
            throw std::invalid_argument("Invalid character in string representation");
        }
    }
    trim();
}

void HugeInt::resetDigits()
{
    digits.clear();
}

void HugeInt::setValue(int num) {
    // Convert the integer to a string
    std::string numStr = std::to_string(num);

    // Clear the existing digits
    digits.clear();

    // Add the new digits to the vector
    for (int i = numStr.size() - 1; i >= 0; i--) {
        digits.push_back(numStr[i] - '0');
    }

    // Remove any leading zeroes
    trim();

    // Set the sign
    negative = (num < 0);
}

void HugeInt::setValue(const std::string& str) {
    // Clear the existing digits
    digits.clear();

    // Add the new digits to the vector
    for (int i = str.size() - 1; i >= 0; i--) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            digits.push_back(c - '0');
        } else if (i == 0 && c == '-') {
            negative = true;
        } else {
            throw std::invalid_argument("Invalid character in string representation");
        }
    }

    // Remove any leading zeroes
    trim();
}


// Addition operator
HugeInt HugeInt::operator+(const HugeInt& other) const {
    if (negative && other.negative) { // both numbers are negative
        HugeInt result = -((-(*this)) + (-other));
        return result;
    } else if (negative && !other.negative) { // this number is negative
        return other - (-(*this));
    } else if (!negative && other.negative) { // other number is negative
        return (*this) - (-other);
    }
    HugeInt result;
    unsigned int carry = 0;
    unsigned int size = std::max(digits.size(), other.digits.size());
    for (unsigned int i = 0; i < size; i++) {
        unsigned int sum = carry;
        if (i < digits.size()) {
            sum += digits[i];
        }
        if (i < other.digits.size()) {
            sum += other.digits[i];
        }
        result.digits.push_back(sum % BASE);
        carry = sum / BASE;
    }
    if (carry > 0) {
        result.digits.push_back(carry);
    }
    return result;
}


// Subtraction operator
HugeInt HugeInt::operator-(const HugeInt& other) const {

    if (negative != other.negative) {
        return *this + (-other);
    } else if (negative) {
        return (-other) - (-*this);
    }

    HugeInt result;
    unsigned int borrow = 0;
    unsigned int size = digits.size();
    for (unsigned int i = 0; i < size; i++) {
        int difference = digits[i] - borrow;
        if (i < other.digits.size()) {
            if (negative && other.negative) {
                difference += other.digits[i];
            } else {
                difference -= other.digits[i];
            }
        }
        if (difference < 0) {
            difference += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(difference);
    }
    result.trim();
    return result;
}




// Multiplication operator
HugeInt HugeInt::operator*(const HugeInt& other) const {
    HugeInt result;
    result.digits.resize(digits.size() + other.digits.size(), 0);
    for (unsigned int i = 0; i < digits.size(); i++) {
        unsigned int carry = 0;
        for (unsigned int j = 0; j < other.digits.size(); j++) {
            unsigned long long product = static_cast<unsigned long long>(digits[i]) * other.digits[j] + carry + result.digits[i+j];
            result.digits[i+j] = product % BASE;
            carry = product / BASE;
        }
        result.digits[i+other.digits.size()] += carry;
    }
    result.trim();
    return result;
}

// Division operator
HugeInt HugeInt::operator/(const HugeInt& other) const {
    if (other == HugeInt(0)) {
        throw std::invalid_argument("Division by zero");
    }
    HugeInt quotient;
    HugeInt remainder;
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
        remainder = remainder * HugeInt(BASE) + HugeInt(digits[i]);
        unsigned int q = 0;
        unsigned int r = 0;
        unsigned int high = BASE - 1;
        while (r <= high) {
            unsigned int mid = (r + high) / 2;
            HugeInt t = other * HugeInt(mid);
            if (t <= remainder) {
                q = mid;
                r = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        quotient.digits.insert(quotient.digits.begin(), q);
        remainder = remainder - HugeInt(q) * other;
    }
    quotient.trim();
    return quotient;
}

// Equality operator
bool HugeInt::operator==(const HugeInt& other) const {
    return digits == other.digits;
}

// Inequality operator
bool HugeInt::operator!=(const HugeInt& other) const {
    return !(*this == other);
}

// Less-than operator
bool HugeInt::operator<(const HugeInt& other) const {
    if (digits.size() < other.digits.size()) {
        return true;
    } else if (digits.size() > other.digits.size()) {
        return false;
    } else {
        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
            if (digits[i] < other.digits[i]) {
                return true;
            } else if (digits[i] > other.digits[i]) {
                return false;
            }
        }
        return false;
    }
}

HugeInt HugeInt::operator-() const {
    HugeInt result(*this);
    result.negative = !negative;
    return result;
}


// Greater-than operator
bool HugeInt::operator>(const HugeInt& other) const {
    return other < *this;
}

// Less-than or equal-to operator
bool HugeInt::operator<=(const HugeInt& other) const {
    return !(other < *this);
}

bool HugeInt::operator>=(const HugeInt& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const HugeInt& hugeint) {
    for (int i = hugeint.digits.size() - 1; i >= 0; i--) {
        os << hugeint.digits[i];
    }
    return os;
}

HugeInt& HugeInt::operator+=(const HugeInt &other) {
    unsigned int carry = 0;
    unsigned int size = std::max(digits.size(), other.digits.size());
    for (unsigned int i = 0; i < size; i++) {
        unsigned int sum = carry;
        if (i < digits.size()) {
            sum += digits[i];
        }
        if (i < other.digits.size()) {
            sum += other.digits[i];
        }
        if (i < digits.size()) {
            digits[i] = sum % BASE;
        } else {
            digits.push_back(sum % BASE);
        }
        carry = sum / BASE;
    }
    if (carry > 0) {
        digits.push_back(carry);
    }
    return *this;
}

HugeInt& HugeInt::operator-=(const HugeInt& other) {
    unsigned int borrow = 0;
    unsigned int size = digits.size();
    for (unsigned int i = 0; i < size; i++) {
        int difference = digits[i] - borrow;
        if (i < other.digits.size()) {
            difference -= other.digits[i];
        }
        if (difference < 0) {
            difference += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        digits[i] = difference;
    }
    trim();
    return *this;
}

HugeInt& HugeInt::operator*=(const HugeInt& other) {
    *this = *this * other;
    return *this;
}

HugeInt& HugeInt::operator/=(const HugeInt& other) {
    if (other == HugeInt(0)) {
        throw std::invalid_argument("Division by zero");
    }
    HugeInt quotient;
    HugeInt remainder;
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
        remainder = remainder * HugeInt(BASE) + HugeInt(digits[i]);
        unsigned int q = 0;
        unsigned int r = 0;
        unsigned int high = BASE - 1;
        while (r <= high) {
            unsigned int mid = (r + high) / 2;
            HugeInt t = other * HugeInt(mid);
            if (t <= remainder) {
                q = mid;
                r = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        quotient.digits.insert(quotient.digits.begin(), q);
        remainder = remainder - HugeInt(q) * other;
    }
    quotient.trim();
    digits = quotient.digits;
    return *this;
}

HugeInt HugeInt::operator^(const HugeInt &other) const {
    HugeInt result = HugeInt(1);
    HugeInt base = *this;
    HugeInt exponent = other;
    while (exponent > HugeInt(0)) {
        if (exponent % HugeInt(2) == HugeInt(1)) {
            result *= base;
        }
        base *= base;
        exponent /= HugeInt(2);
    }
    return result;
}

HugeInt& HugeInt::operator^=(const HugeInt& other) {
    *this = *this ^ other;
    return *this;
}

HugeInt HugeInt::operator%(const HugeInt& other) const {
    if (other == HugeInt(0)) {
        throw std::invalid_argument("Modulus by zero");
    }
    HugeInt quotient;
    HugeInt remainder;
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
        remainder = remainder * HugeInt(BASE) + HugeInt(digits[i]);
        unsigned int q = 0;
        unsigned int r = 0;
        unsigned int high = BASE - 1;
        while (r <= high) {
            unsigned int mid = (r + high) / 2;
            HugeInt t = other * HugeInt(mid);
            if (t <= remainder) {
                q = mid;
                r = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        quotient.digits.insert(quotient.digits.begin(), q);
        remainder = remainder - HugeInt(q) * other;
    }
    remainder.trim();
    return remainder;
}


HugeInt& HugeInt::operator%=(const HugeInt& other) {
    if (other == HugeInt(0)) {
        throw std::invalid_argument("Modulus by zero");
    }
    HugeInt quotient;
    HugeInt remainder;
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
        remainder = remainder * HugeInt(BASE) + HugeInt(digits[i]);
        unsigned int q = 0;
        unsigned int r = 0;
        unsigned int high = BASE - 1;
        while (r <= high) {
            unsigned int mid = (r + high) / 2;
            HugeInt t = other * HugeInt(mid);
            if (t <= remainder) {
                q = mid;
                r = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        quotient.digits.insert(quotient.digits.begin(), q);
        remainder = remainder - HugeInt(q) * other;
    }
    remainder.trim();
    digits = remainder.digits;
    return *this;
}


void HugeInt::trim() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        negative = false;
    }
}


