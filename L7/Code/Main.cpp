#include "ISQRT.h"
#include "Timer.h"

#include <iostream>
#include <sstream>
#include <array>
#include <cmath>


void Wait()
{
	std::cout << "Press ENTER to continue..." << std::endl;
	std::cin.get();
}

void Refresh(const std::stringstream& output)
{
	system("CLS");
	std::cout << output.str();
}

struct Float
{
	char Sign;
	std::array<char, 8> Exponent;
	std::array<char, 23> Mantissa;

	Float()
		:Sign('0')
	{
		for (uint32_t i = 0; i < Exponent.size(); i++)
			Exponent[i] = '0';
		for (uint32_t i = 0; i < Mantissa.size(); i++)
			Mantissa[i] = '0';
	}

	std::string ToString() const
	{
		std::stringstream ss;
		ss << Sign << " | ";
		for (uint32_t i = 0; i < 8; i++)
			ss << Exponent[i];
		ss << " | ";
		for (uint32_t i = 0; i < 23; i++)
			ss << Mantissa[i];
		return ss.str();
	}

	friend std::ostream& operator<<(std::ostream& os, const Float& f)
	{
		os << f.ToString();
		return os;
	}

	std::array<char, 32> ToArray() const
	{
		std::array<char, 32> arr;
		uint32_t i = 0;
		for (; i < 23; i++)
			arr[i] = Mantissa[23 - i - 1];
		for (; i < 23 + 8; i++)
			arr[i] = Exponent[23 + 8 - i - 1];
		arr[i] = Sign;
		return arr;
	}
};

Float Create(float f)
{
	Float F;

	F.Sign = (f >= 0 ? '0' : '1');

	float abs_f = abs(f);
	uint32_t int_f = static_cast<uint32_t>(abs_f);
	float frac_f = abs_f - int_f;

	int nr = int_f > 0 ? static_cast<int>(log2(int_f)) : 0;
	int i = nr - 1;
	bool nonzeroFounded = false;
	while (int_f > 1)
	{
		nonzeroFounded = true;
		F.Mantissa[i--] = int_f % 2 + '0';
		int_f /= 2;
	}

	int negativePower = 0;

	for (i = nr; i < F.Mantissa.size();)
	{
		frac_f *= 2;
		if (frac_f >= 1)
		{
			if (!nonzeroFounded)
			{
				negativePower++;
				nonzeroFounded = true;
			}
			else
			{
				F.Mantissa[i++] = '1';
			}
			frac_f--;
		}
		else
		{
			if (nonzeroFounded)
				F.Mantissa[i++] = '0';
			else
			{
				negativePower++;
			}
		}
		if (static_cast<int>(frac_f) == frac_f)
			break;
	}

	nr -= negativePower;

	int power_add = pow(2, 7) - 1;
	int power = nr + power_add;
	std::array<char, 8> digits;
	for (char& c : digits)
		c = '0';
	i = 8;
	while (power)
	{
		digits[--i] = power % 2 + '0';
		power /= 2;
	}
	for (i = 0; i < 8; i++)
		F.Exponent[i] = digits[i];

	return F;
}

void Calculate()
{
	std::stringstream output;

	float x;
	std::cout << "Numarul: ";
	std::cin >> x;
	std::cin.get();

	output << "x = " << x << std::endl;

	int y = *(int*)&x;

	Float f = Create(x);
	output << f << std::endl;

	Refresh(output);
	Wait();

	output << "x 'interpretat' ca int este y = " << y << std::endl;
	Refresh(output);
	Wait();
	output << "y >> 1 == " << (y >> 1) << std::endl;
	Refresh(output);
	Wait();
	output << "1597463007 - (y >> 1) == " << (1597463007 - (y >> 1)) << std::endl;
	y = (1597463007 - (y >> 1));
	Refresh(output);
	Wait();

	float z = *(float*)&y;

	output << "y 'interpretat' ca float este z = " << z << std::endl;
	Refresh(output);
	Wait();

	output << "1 / sqrt(x) = z * (1.5f - (0.5f * x * z * z))" << std::endl;
	Refresh(output);
	Wait();
	output << "1 / sqrt(" << x << ") = " << (z * (1.5f - (0.5f * x * z * z))) << std::endl;
	Refresh(output);
	Wait();
}

void Compare()
{
	int n;
	std::cout << "Cati radicali se vor calcula? " << std::endl;
	std::cout << "Raspuns: "; std::cin >> n; std::cin.get();

	Timer t;
	float x;

	t.Start();

	for (int i = 1; i <= n; i++)
	{
		x = ISQRT::Func1(static_cast<float>(i));
	}

	std::cout << "Functia sqrt: " << t.MillisecondsToString(6) << std::endl;
	std::cout << "1 / sqrt(" << n << ") = " << x << std::endl;
	t.Start();

	for (int i = 1; i <= n; i++)
	{
		x = ISQRT::Func2(static_cast<float>(i));
	}

	std::cout << "Functia pow(x, -1/2): " << t.MillisecondsToString(6) << std::endl;
	std::cout << "1 / sqrt(" << n << ") = " << x << std::endl;

	t.Start();

	for (int i = 1; i <= n; i++)
	{
		x = ISQRT::Func3(static_cast<float>(i));
	}

	std::cout << "Functia 'magica': " << t.MillisecondsToString(6) << std::endl;
	std::cout << "1 / sqrt(" << n << ") = " << x << std::endl;

	Wait();
}

int main()
{
	int command = 0;
	do
	{
		system("CLS");
		std::cout << "0 -> EXIT" << std::endl;
		std::cout << "1 -> Calcul" << std::endl;
		std::cout << "2 -> Comparare" << std::endl;
		std::cout << "Comanda: "; std::cin >> command;
		std::cin.get();

		if (command == 1)
		{
			Calculate();
		}
		else if (command == 2)
		{
			Compare();
		}
	} while (command);

	return 0;
}