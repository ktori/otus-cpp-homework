//
// Created by victoria on 18.05.20
//

/**
 * @file
 * @brief Entry point of the application
 */

#include "print_ip.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <string>

int main(int argc, char** argv)
{
	using std::literals::string_literals::operator ""s;

	print_ip(char(-1));

	std::cout << '\n';
	print_ip(short(0));

	std::cout << '\n';
	print_ip(long(8875824491850138409));

	std::cout << '\n';
	print_ip("string"s);

	std::cout << '\n';
	print_ip(std::vector{ 127, 0, 0, 1 });

	std::cout << '\n';
	print_ip(std::list{ 12, 34, 56, 78 });

	std::cout << '\n';
	print_ip(std::make_tuple(98, 76, 54, 32, 10));

//	std::cout << "\nprint_ip(std::tuple (won't compile)): ";
//	print_ip(std::make_tuple('a', 123));

	return 0;
}