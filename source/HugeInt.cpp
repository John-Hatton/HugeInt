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
    for (int i = str.size() - 1; i >= 0; i--) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            digits.push_back(c - '0');
        } else {
            throw std::invalid_argument("Invalid character in string representation");
        }
    }
    trim();
}

// Addition operator
HugeInt HugeInt::operator+(const HugeInt& other) const {
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
    HugeInt result;
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



void HugeInt::trim() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}
