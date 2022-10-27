#include <iostream>
#include <fstream>

extern "C" int RectCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int* result);

struct Rect
{
	int x, y;
	int w, h;

	friend std::istream& operator>>(std::istream& is, Rect& rect)
	{
		std::cout << "Rect: " << std::endl;
		std::cout << "x = "; is >> rect.x;
		std::cout << "y = "; is >> rect.y;
		std::cout << "w = "; is >> rect.w;
		std::cout << "h = "; is >> rect.h;
		return is;
	}
};

int main()
{
	Rect r1, r2;

	std::cin >> r1 >> r2;

	int result = 3;

	RectCheck(r1.x, r1.y, r1.w, r1.h, r2.x, r2.y, r2.w, r2.h, &result);

	std::cout << "Result: " << std::endl;
	std::cout << "0 -> Niciunul nu e inclus in celalalt" << std::endl;
	std::cout << "1 -> Primul inclus in al doilea" << std::endl;
	std::cout << "2 -> Al doilea inclus in primul" << std::endl;
	std::cout << result << std::endl;

	return 0;
}