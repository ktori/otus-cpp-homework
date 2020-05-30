//
// Created by victoria on 30.05.20.
//

#include <gtest/gtest.h>

#include "../src/matrix.hpp"

TEST(matrix_two_d, default_get)
{
	matrix::matrix<int, 1234> mx{};

	ASSERT_EQ(mx[12][34], 1234);
}

TEST(matrix_two_d, insert_and_get)
{
	matrix::matrix<int, -1> mx{};
	mx[1][2] = 100;

	ASSERT_EQ(mx[1][2], 100);
	ASSERT_EQ(mx.size(), 1);
}

TEST(matrix_two_d, insert_default)
{
	matrix::matrix<int, -1> mx{};
	mx[1][2] = 100;

	ASSERT_EQ(mx.size(), 1);

	mx[1][2] = -1;

	ASSERT_EQ(mx.size(), 0);
}

TEST(matrix_char_3d, default_get)
{
	matrix::matrix<char, ' ', 3> mx{};

	ASSERT_EQ(mx[1][2][3], ' ');
}

TEST(matrix_char_3d, insert_and_get)
{
	matrix::matrix<char, ' ', 3> mx{};
	mx[1][2][3] = 'a';
	ASSERT_EQ(mx[1][2][3], 'a');
	ASSERT_EQ(mx.size(), 1);
}

TEST(matrix_char_3d, insert_default)
{
	matrix::matrix<char, ' ', 3> mx{};
	mx[1][2][3] = 'a';

	ASSERT_EQ(mx.size(), 1);

	mx[1][2][3] = ' ';

	ASSERT_EQ(mx.size(), 0);
}

TEST(matrix, operator_assign)
{
	matrix::matrix<int, -1> mx{};

	((mx[100][100] = 314) = 0) = 217;

	ASSERT_EQ(int(mx[100][100]), 217);
}