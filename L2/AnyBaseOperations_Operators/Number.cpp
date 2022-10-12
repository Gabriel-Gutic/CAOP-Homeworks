#include "Number.h"

#include <cmath>
#include <sstream>


Number::Number(const std::string& value, uint32_t newBase, uint32_t oldBase)
    :m_Base(newBase)
{
    ASSERT(2 <= newBase && newBase <= 36, "The base must be between 2 and 36!");
    ASSERT(Valid(value), "Invalid number format! Only digits and uppercase letters are allowed!");

    uint64_t number10 = 0;
    uint64_t power = 1;

    for (int i = value.size() - 1; i >= 0; i--)
    {
        if (value[i] == ' ')
            continue;
        int c = ToInt(value[i]);
        ASSERT(c < oldBase, "Invalid number " + value + " in base " + std::to_string(oldBase));
    
        number10 += (c * power);
        power *= oldBase;
    }
    
    m_Digits = ConvertFromBase10(number10, newBase);
}

Number::Number(const Number& other, uint32_t newBase)
    :m_Base(newBase)
{
    ASSERT(2 <= newBase && newBase <= 36, "The base must be between 2 and 36!");
    uint64_t number10 = 0;
    uint64_t power = 1;

    for (int i = 0; i < other.m_Digits.size(); i++)
    {
        int c = ToInt(other.m_Digits[i]);
    
        number10 += (c * power);
        power *= other.m_Base;
    }

    m_Digits = ConvertFromBase10(number10, newBase);
}

Number& Number::operator=(const Number& other)
{
    if (this == &other)
        return *this;
    m_Base = other.m_Base;
    m_Digits = other.m_Digits;
    return *this;
}

std::string Number::ToString() const
{
    std::stringstream ss;
    for (int i = m_Digits.size() - 1; i >= 0; i--)
        ss << m_Digits[i];
    ss << "_(" << m_Base << ")";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Number& n)
{
    os << n.ToString();
    return os;
}

uint32_t Number::GetNumberOfDigits() const
{
    return m_Digits.size();
}

char Number::operator[](size_t index) const
{
    return m_Digits[index];
}

std::vector<char> Number::ConvertFromBase10(uint64_t number10, uint32_t newBase)
{
    if (number10 == 0)
        return { '0' };
    std::vector<char> digits;
    int nrDigits = (int)(log(number10) / log(newBase)) + 1;
    digits.resize(nrDigits);
    uint32_t i = 0;
    while (number10 != 0)
    {
        int rest = number10 % newBase;
        digits[i++] = ToChar(rest);
        number10 /= newBase;
    }
    return digits;
}

int Number::ToInt(const char c)
{
    if (IsDigit(c))
        return c - '0';
    if (IsLetter(c))
        return c - 'A' + 10;
    return 0;
}

char Number::ToChar(const int n)
{
    if (0 <= n && n <= 9)
        return n + '0';
    if (10 <= n && n <= 35)
        return n - 10 + 'A';
    return 0;
}

bool Number::Valid(const std::string& value)
{
    if (value == "")
        return false;
    for (const char& c : value)
        if (c == ' ')
            continue;
        else if (!IsDigit(c) && !IsLetter(c))
            return false;
    return true;
}

bool Number::IsDigit(const char c)
{
    return '0' <= c && c <= '9';
}

bool Number::IsLetter(const char c)
{
    return 'A' <= c && c <= 'Z';
}

std::pair<Number, Number> Number::Divide(const Number& n1, const Number& n2)
{
    Number result = Number::GetNAN();
    Number aux1, aux2, aux = Number::GetNAN();
    if (n1.m_Base != n2.m_Base)
    {
        aux1 = Number(n1, 10);
        aux2 = Number(n2, 10);
    }
    else
    {
        aux1 = n1;
        aux2 = n2;
    }

    result.m_Base = n1.m_Base;        
    int i = aux1.GetNumberOfDigits() - 1;
    aux.m_Base = aux1.m_Base;
    aux.m_Digits.push_back(aux1[i--]);
    while (aux < aux2 && i >= 0)
    {
        aux.m_Digits.insert(aux.m_Digits.begin(), aux1[i--]);
    }

    do 
    {
        int n;
        Number product;
        for (n = aux.m_Base - 1; 
            n >= 0; n--)
        {
            product = Number(std::to_string(n), aux.m_Base, 10) * aux2;
            if (product <= aux)
            {
                aux -= product;
                break;
            }    
        }

        result.m_Digits.insert(result.m_Digits.begin(), Number::ToChar(n));
        if (i >= 0)
            aux.m_Digits.insert(aux.m_Digits.begin(), aux1[i]);
        i--;
    } while (i >= -1);

    if (aux.GetNumberOfDigits() == 0)
        aux.m_Digits.push_back('0');
    return { result, aux };
}

Number Number::GetNAN()
{
    Number n;
    n.m_Digits.clear();
    return n;
}

Number operator+(const Number& n1, const Number& n2)
{
    Number result = Number::GetNAN();
    Number aux1, aux2;
    if (n1.m_Base != n2.m_Base)
    {
        aux1 = Number(n1, 10);
        aux2 = Number(n2, 10);
        result.m_Base = 10;
    }
    else
    {
        aux1 = n1;
        aux2 = n2;
        result.m_Base = n1.m_Base;        
    }

    int last = 0;
    for (uint32_t i = 0; i < std::max(aux1.GetNumberOfDigits(), aux2.GetNumberOfDigits()); i++)
    {
        int left = i < aux1.GetNumberOfDigits() ? Number::ToInt(aux1[i]) : 0;
        int right = i < aux2.GetNumberOfDigits() ? Number::ToInt(aux2[i]) : 0;

        int sum = left + right + last;
        last = sum / result.m_Base;
        sum = sum % result.m_Base;
        result.m_Digits.push_back(Number::ToChar(sum));
    }
    if (last > 0)
        result.m_Digits.push_back(Number::ToChar(last));
    return result;
}

Number& Number::operator+=(const Number& other)
{
    *this = *this + other;
    return *this;
}

Number& Number::operator++()
{
    *this += Number("1", m_Base, 10);
    return *this;
}

Number Number::operator++(int)
{
    Number copy = *this;
    ++*this;
    return copy;
}

Number operator-(const Number& n1, const Number& n2)
{
    ASSERT(n1 >= n2, "You can't subtract a bigger number from a smaller number!");

    Number result = Number::GetNAN();
    Number aux1, aux2;
    if (n1.m_Base != n2.m_Base)
    {
        aux1 = Number(n1, 10);
        aux2 = Number(n2, 10);
        result.m_Base = 10;
    }
    else
    {
        aux1 = n1;
        aux2 = n2;
        result.m_Base = n1.m_Base;        
    }

    int last = 0;
    for (uint32_t i = 0; i < std::max(aux1.GetNumberOfDigits(), aux2.GetNumberOfDigits()); i++)
    {
        int left = i < aux1.GetNumberOfDigits() ? Number::ToInt(aux1[i]) : 0;
        int right = i < aux2.GetNumberOfDigits() ? Number::ToInt(aux2[i]) : 0;

        int sum = left - right + last;
        if (sum < 0)
        {
            last = -1;
            sum += result.m_Base;
        }
        else last = 0;
        result.m_Digits.push_back(Number::ToChar(sum));
    }

    while (result.GetNumberOfDigits() > 0 && result.m_Digits.back() == '0')
    {
        result.m_Digits.pop_back();
    }

    return result;
}

Number& Number::operator-=(const Number& other)
{
    *this = *this - other;
    return *this;
}

Number& Number::operator--()
{
    *this -= Number("1", m_Base, 10);
    return *this;
}

Number Number::operator--(int)
{
    Number copy = *this;
    --*this;
    return copy;
}

Number operator*(const Number& n1, const Number& n2)
{
    Number result;
    Number aux1, aux2;
    if (n1.m_Base != n2.m_Base)
    {
        aux1 = Number(n1, 10);
        aux2 = Number(n2, 10);
        result.m_Base = 10;
    }
    else
    {
        aux1 = n1;
        aux2 = n2;
        result.m_Base = n1.m_Base;        
    }

    int last = 0;
    for (uint32_t i = 0; i < aux2.GetNumberOfDigits(); i++)
    {
        Number aux = Number::GetNAN();
        aux.m_Base = result.m_Base;
        for (uint32_t j = 0; j < i; j++)
        {
            aux.m_Digits.push_back('0');
        }

        for (uint32_t j = 0; j < aux1.GetNumberOfDigits(); j++)
        {
            int first = Number::ToInt(aux1[j]);
            int second = Number::ToInt(aux2[i]);

            uint64_t prod = static_cast<uint64_t>(first) *
                            static_cast<uint64_t>(second) +
                            last;
            
            last = prod / aux.m_Base;
            prod = prod % aux.m_Base;

            aux.m_Digits.push_back(Number::ToChar(prod));
        }

        if (last > 0)
            aux.m_Digits.push_back(Number::ToChar(last));

        result = result + aux;
    }
    return result;
}

Number& Number::operator*=(const Number& other)
{
    *this = *this * other;
    return *this;
}

Number operator/(const Number& n1, const Number& n2)
{
    return Number::Divide(n1, n2).first;
}

Number& Number::operator/=(const Number& other)
{
    *this = *this / other;
    return *this;
}

Number operator%(const Number& n1, const Number& n2)
{
    return Number::Divide(n1, n2).second;
}

Number& Number::operator%=(const Number& other)
{
    *this = *this % other;
    return *this;
}

bool operator<(const Number& n1, const Number& n2)
{
    Number aux1, aux2;
    if (n1.m_Base != n2.m_Base)
    {
        aux1 = Number(n1, 10);
        aux2 = Number(n2, 10);
    }
    else
    {
        aux1 = n1;
        aux2 = n2;
    }

    if (aux1.GetNumberOfDigits() < aux2.GetNumberOfDigits())
        return true;
    if (aux1.GetNumberOfDigits() > aux2.GetNumberOfDigits())
        return false;

    for (int i = aux1.GetNumberOfDigits() - 1; i >= 0; i--)
        if (aux1[i] > aux2[i])
            return false;
        else if (aux1[i] < aux2[i])
            return true;
    return false;
}

bool operator<=(const Number& n1, const Number& n2)
{
    return (n1 < n2) || (n1 == n2);
}

bool operator>(const Number& n1, const Number& n2)
{
    return !(n1 <= n2);
}

bool operator>=(const Number& n1, const Number& n2)
{
    return !(n1 < n2);
}

bool operator==(const Number& n1, const Number& n2)
{
    Number aux1, aux2;
    if (n1.m_Base != n2.m_Base)
    {
        aux1 = Number(n1, 10);
        aux2 = Number(n2, 10);
    }
    else
    {
        aux1 = n1;
        aux2 = n2;
    }

    if (aux1.GetNumberOfDigits() != aux2.GetNumberOfDigits())
        return false;
    for (uint32_t i = 0; i < aux1.GetNumberOfDigits(); i++)
        if (aux1[i] != aux2[i])
            return false;
    return true;
}

bool operator!=(const Number& n1, const Number& n2)
{
    return !(n1 == n2);
}
