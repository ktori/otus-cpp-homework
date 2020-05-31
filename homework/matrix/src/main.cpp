//
// Created by victoria on 30.05.20.
//

#include "matrix.hpp"

#include <cassert>
#include <iostream>

int main()
{
	matrix::matrix<int, 0> mx{};

	for (int i = 0; i < 10; ++i)
	{
		mx[i][i] = i;
		mx[i][9 - i] = 9 - i;
	}

	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 8; ++j)
		{
			std::cout << int(mx[i][j]) << ' ';
		}
		std::cout << '\n';
	}

	std::cout << "Size: " << mx.size() << '\n';

	for (const auto& i : mx)
	{
		size_t a, b;
		int v;
		std::tie(a, b, v) = i;

		std::cout << '[' << a << "][" << b << "] = " << v << '\n';
	}

	return 0;
}