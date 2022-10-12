#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <vector>

#define ASSERT(expr, msg) if (!(expr)) \
{std::cout << "ERROR: " << msg << std::endl; exit(1); }


class Number
{
public:
    Number(const std::string& value = "0", uint32_t newBase = 2, uint32_t oldBase = 10);
    Number(const Number& other, uint32_t newBase);
    ~Number() = default;
    Number& operator=(const Number& other);

    std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const Number& n);

    uint32_t GetNumberOfDigits() const;
    char operator[](size_t index) const;

    friend Number operator+(const Number& n1, const Number& n2);
    Number& operator+=(const Number& other);
    Number& operator++();
    Number operator++(int);
    friend Number operator-(const Number& n1, const Number& n2);
    Number& operator-=(const Number& other);
    Number& operator--();
    Number operator--(int);
    friend Number operator*(const Number& n1, const Number& n2);
    Number& operator*=(const Number& other);
    friend Number operator/(const Number& n1, const Number& n2);
    Number& operator/=(const Number& other);
    friend Number operator%(const Number& n1, const Number& n2);
    Number& operator%=(const Number& other);

    friend bool operator<(const Number& n1, const Number& n2);
    friend bool operator<=(const Number& n1, const Number& n2);
    friend bool operator>(const Number& n1, const Number& n2);
    friend bool operator>=(const Number& n1, const Number& n2);
    friend bool operator==(const Number& n1, const Number& n2);
    friend bool operator!=(const Number& n1, const Number& n2);
private:
    static std::vector<char> ConvertFromBase10(uint64_t number10, uint32_t newBase);
    static int ToInt(const char c);
    static char ToChar(const int n);
    static bool Valid(const std::string& value);
    static bool IsDigit(const char c);
    static bool IsLetter(const char c);
public:
    // first -> ratio
    // second -> rest
    static std::pair<Number, Number> Divide(const Number& n1, const Number& n2);

    static Number GetNAN();
private:
    std::vector<char> m_Digits;
    uint32_t m_Base;
};

#include "Number.cpp"

#endif