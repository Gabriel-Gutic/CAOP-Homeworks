#include "Number.h"


int main()
{
    Number n1 = Number("120", 2, 10);
    Number n2 = Number("11", 16, 10);

    std::cout << "Logical operators: " << std::endl;

    std::cout << n1 << " <= " << n2 << " => " << (n1 <= n2) << std::endl;
    std::cout << n1 << " < "  << n2 << " => " << (n1 <  n2) << std::endl;
    std::cout << n1 << " >= " << n2 << " => " << (n1 >= n2) << std::endl;
    std::cout << n1 << " > "  << n2 << " => " << (n1 >  n2) << std::endl;
    std::cout << n1 << " == " << n2 << " => " << (n1 == n2) << std::endl;
    std::cout << n1 << " != " << n2 << " => " << (n1 != n2) << std::endl;

    std::cout << std::endl << "Arithmetic operators: " << std::endl;

    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << std::endl;
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << std::endl;
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << std::endl;
    std::cout << n1 << " / " << n2 << " = " << n1 / n2 << std::endl;
    std::cout << n1 << " % " << n2 << " = " << n1 % n2 << std::endl;

    std::cout << std::endl;

    std::cout << n1 << " += " << n2 << "   =>   n1 = " << (n1 += n2) << std::endl;
    std::cout << n1 << " -= " << n2 << "   =>   n1 = " << (n1 -= n2) << std::endl;
    std::cout << n1 << " *= " << n2 << "   =>   n1 = " << (n1 *= n2) << std::endl;
    std::cout << n1 << " /= " << n2 << "   =>   n1 = " << (n1 /= n2) << std::endl;
    std::cout << n1 << " %= " << n2 << "   =>   n1 = " << (n1 %= n2) << std::endl;

    std::cout << std::endl;

    std::cout << "++n1   =>   n1 = " << ++n1 << std::endl;
    std::cout << "n1++   =>   n1 = " << n1++ << std::endl;
    std::cout << "--n1   =>   n1 = " << --n1 << std::endl;
    std::cout << "n1--   =>   n1 = " << n1-- << std::endl;

    std::cout << std::endl << "Conditional operator: " << std::endl;

    std::cout << "(n1 < n2) ? True : False   =>   " << (n1 < n2 ? "True" : "False") << std::endl;

    std::cout << std::endl << "New operator: ";
    Number* n = new Number("AB", 2, 16);
    std::cout << "*n = " << *n << " is dynamically allocated" << std::endl;
    std::cout << "Arrow operator: " << std::endl;
    std::cout << "n->ToString()   =>   " << n->ToString() << std::endl;
    delete n;

    std::cout << std::endl << "Assignment operator: " << std::endl;
    std::cout << "n1 = n2   =>   n1 = " << (n1 = n2) << std::endl;

    std::cout << std::endl;

    std::cout << "Bitwise Operators: " << std::endl;
    std::cout << "~7 = " << ~7 << std::endl;
    std::cout << "7 & 9 = " << (7 & 9) << std::endl;
    std::cout << "7 | 9 = " << (7 | 9) << std::endl;
    std::cout << "7 ^ 9 = " << (7 ^ 9) << std::endl;
    std::cout << "7 << 9 = " << (7 << 9) << std::endl;
    std::cout << "7 >> 9 = " << (7 >> 9) << std::endl;
    std::cout << std::endl;
    int x = 7, y = 9;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "x &= y   =>   x = " << (x &= y) << std::endl;
    std::cout << "x |= y   =>   x = " << (x |= y) << std::endl;
    std::cout << "x ^= y   =>   x = " << (x ^= y) << std::endl;
    std::cout << "x <<= y   =>   x = " << (x <<= y) << std::endl;
    std::cout << "x >>= y   =>   x = " << (x >>= y) << std::endl;

    std::cout << std::endl << "Logical operators: " << std::endl;
    std::cout << "(x < y) && (x % 2 == 0)   =>   " << ((x < y) && (x % 2 == 0)) << std::endl;
    std::cout << "(x < y) || (x % 2 == 0)   =>   " << ((x < y) || (x % 2 == 0)) << std::endl;
    std::cout << "!(x < y)   =>   " << !(x < y) << std::endl;

    return 0;
}