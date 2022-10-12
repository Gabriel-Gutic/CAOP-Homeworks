#include <iostream>
#include <regex>
#include <array>
#include <sstream>
#include <cmath>


#define EXPONENT_SIZE 8
#define MANTISSA_SIZE 23
#define SIZE EXPONENT_SIZE + MANTISSA_SIZE + 1


static std::stringstream output;


void Wait()
{
	std::cout << "Press enter key to continue..." << std::endl;
	std::cin.get();
	system("CLS");
	std::cout << output.str();
}


struct Float
{
	char Sign;
	std::array<char, EXPONENT_SIZE> Exponent;
	std::array<char, MANTISSA_SIZE> Mantissa;

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
		for (uint32_t i = 0; i < EXPONENT_SIZE; i++)
			ss << Exponent[i];
		ss << " | ";
		for (uint32_t i = 0; i < MANTISSA_SIZE; i++)
			ss << Mantissa[i];
		return ss.str();
	}

	friend std::ostream& operator<<(std::ostream& os, const Float& f)
	{
		os << f.ToString();
		return os;
	}

	std::array<char, 1 + EXPONENT_SIZE + MANTISSA_SIZE> ToArray() const
	{
		std::array<char, 1 + EXPONENT_SIZE + MANTISSA_SIZE> arr;
		uint32_t i = 0;
		for (; i < MANTISSA_SIZE; i++)
			arr[i] = Mantissa[MANTISSA_SIZE - i - 1];
		for (; i < MANTISSA_SIZE + EXPONENT_SIZE; i++)
			arr[i] = Exponent[MANTISSA_SIZE + EXPONENT_SIZE - i - 1];
		arr[i] = Sign;
		return arr;
	}
};


std::string ConvertTo16(int index, const std::array<char, 1 + EXPONENT_SIZE + MANTISSA_SIZE>& arr)
{
	std::string result = "  ";
	for (int i = index; i < index + 8; i += 4)
	{
		int p = 1;
		int el = 0;
		for (int j = 0; j < 4; j++)
		{
			el += (arr[i + j] - '0') * p;
			p *= 2;
		}
		result[!((i - index) / 4)] = (el <= 9) ? (el + '0') : (el + 'A' - 10);
	}
	return result;
}

std::string HexToBin(const char c)
{
	switch (c)
	{
	case '0':
		return "0000";
	case '1':
		return "0001";
	case '2':
		return "0010";
	case '3':
		return "0011";
	case '4':
		return "0100";
	case '5':
		return "0101";
	case '6':
		return "0110";
	case '7':
		return "0111";
	case '8':
		return "1000";
	case '9':
		return "1001";
	case 'A':
		return "1010";
	case 'B':
		return "1011";
	case 'C':
		return "1100";
	case 'D':
		return "1101";
	case 'E':
		return "1110";
	case 'F':
		return "1111";
	}
	return "0000";
}

std::string HexToBinary(const std::string& hex)
{
	std::string result = "";

	for (int i = hex.size() - 2; i >= 0; i -= 3)
	{
		std::string s1 = HexToBin(hex[i]), s2 = HexToBin(hex[i + 1]);
		result += s1;
		result += s2;
		result += " ";
	}

	return result;
}

int main()
{

	float f;

	std::cout << "Float Number: "; std::cin >> f;
	std::cin.get();

	Float F;

	output << F << std::endl;
	std::cout << output.str();

	
	output << "sgn(" << f << ") = " << (f >= 0 ? "1" : "-1") << " => First digit is: " << (F.Sign = (f >= 0 ? '0' : '1')) << std::endl;
	output << F << std::endl;
	Wait();

	float abs_f = abs(f);
	uint32_t int_f = static_cast<uint32_t>(abs_f);
	float frac_f = abs_f - int_f;
	output << "[" << abs_f << "] = " << int_f << std::endl;
	output << "{" << abs_f << "} = " << frac_f << std::endl;
	Wait();
	
	int nr = int_f > 0 ? static_cast<int>(log2(int_f)) : 0;
	int i = nr - 1;
	while (int_f != 1)
	{
		output << int_f << " : 2 = " << int_f / 2 << " r " << int_f % 2 << std::endl;
		F.Mantissa[i--] = int_f % 2 + '0';
		int_f /= 2;
	}
	output << F << std::endl;
	Wait();
	
	for (i = nr; i < F.Mantissa.size(); i++)
	{
		output << frac_f << " * 2 = " << frac_f * 2 << std::endl;
		frac_f *= 2;
		if (frac_f >= 1)
		{
			F.Mantissa[i] = '1';
			frac_f--;
		}
		else F.Mantissa[i] = '0';

		if (static_cast<int>(frac_f) == frac_f)
			break;
	}
	output << F << std::endl;
	Wait();

	int power_add = pow(2, EXPONENT_SIZE - 1) - 1;
	int power = nr + power_add;
	output << nr << " + 127 = " << power << std::endl;
	std::array<char, EXPONENT_SIZE> digits;
	for (char& c : digits)
		c = '0';
	i = EXPONENT_SIZE;
	while (power)
	{
		digits[--i] = power % 2 + '0';
		power /= 2;
	}
	output << nr + 127 << "_(10) = ";
	for (i = 0; i < EXPONENT_SIZE; i++)
	{
		output << digits[i];
		F.Exponent[i] = digits[i];
	}
	output << "_(2)" << std::endl << F << std::endl;
	Wait();

	auto finalBits = F.ToArray();

	for (i = 0; i < finalBits.size(); i++)
	{
		output << finalBits[i];
		if (i % 8 == 7)
			output << ' ';
	}
	output << std::endl;

	std::string result = "";
	for (int i = 0; i < SIZE; i += 8)
	{
		result += ConvertTo16(i, finalBits);
		if (i + 8 < SIZE)
			result += " ";
	}
	output << "Final Result: " << result << std::endl;

	Wait();
	
	output << std::endl << "Reversed: " << std::endl;
	output << result << std::endl;
	std::string bits = HexToBinary(result);
	output << bits << std::endl;
	Wait();

	bits = std::regex_replace(bits, std::regex(" "), "");
	Float F1;
	F1.Sign = bits[0];
	i = 1;
	for (; i <= EXPONENT_SIZE; i++)
		F1.Exponent[i - 1] = bits[i];
	for (; i < SIZE; i++)
		F1.Mantissa[i - EXPONENT_SIZE - 1] = bits[i];

	output << F1 << std::endl;
	Wait();

	// Take the exponent
	int expo = 0;
	power = 1;
	for (uint32_t i = 0; i < EXPONENT_SIZE; i++)
	{
		expo += (F1.Exponent[EXPONENT_SIZE - i - 1] - '0') * power;
		power *= 2;
	}
	output << "Exponent: " << expo << std::endl << "Final Exponent: " 
		<< expo << " - " << power_add << " = ";
	expo -= power_add;
	output << expo << std::endl;
	Wait();

	// Take the mantissa
	float mantissa = 0;
	power = 2;
	output << "Mantissa = ";
	for (i = 0; i < MANTISSA_SIZE; i++)
	{
		output << "(" << (F1.Mantissa[i] - '0') << " * 1/(2^" << i + 1 << "))";
		mantissa += (F1.Mantissa[i] - '0') * (1.0f / power);
		power *= 2;
		if (i + 1 < MANTISSA_SIZE)
			output << " + ";
	}
	output << std::endl << "Mantissa: " << mantissa << std::endl;
	Wait();

	mantissa++;
	float f_result = mantissa * pow(2, expo);
	output << "Result: f = " << mantissa << " * 2^(" << expo << ") = " << f_result << std::endl;
	Wait();


	std::cin.get();
	return 0;
}