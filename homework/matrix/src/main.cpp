//
// Created by victoria on 30.05.20.
//

#include "matrix.hpp"

#include <cassert>
#include <iostream>

int main()
{
	matrix<int, -1, 3> mx{};
	assert(mx.size() == 0);

	auto a = mx[0][0][0];
	assert(a == -1);
	assert(mx.size() == 0);

	mx[100][100][100] = 314;
	assert(mx[100][100][100] == 314);
	assert(mx.size() == 1);

//	mx[100][100][100] = -1;
//	assert(mx[100][100][100] == -1);
//	assert(mx.size() == 0);

	for (auto i : mx)
	{
		size_t x, y, z;
		int v;
		std::tie(x, y, z, v) = i;

		std::cout << x << y << z << v;
	}

	return 0;
}