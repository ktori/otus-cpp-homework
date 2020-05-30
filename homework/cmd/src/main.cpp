//
// Created by victoria on 30.05.20.
//

#include "block_reader.hpp"
#include "command_block.hpp"

#include <iostream>
#include <charconv>
#include <cstring>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <N>\n";

		return 1;
	}

	std::string command_count_str{ argv[1] };
	int command_count;

	if (auto[p, ec] = std::from_chars(command_count_str.data(),
			command_count_str.data() + command_count_str.size(),
			command_count); ec != std::errc())
	{
		std::cerr << "Unable to parse command line argument: " << command_count_str << "\n";

		return 1;
	}

	if (command_count <= 0)
	{
		std::cerr << "Block size must be > 0\n";

		return 1;
	}

	bulk::BlockReader reader{ std::cin, static_cast<size_t>(command_count) };

	while (auto block = reader.read_block())
	{
		std::cout << "bulk: " << *block << "\n";
	}

	return 0;
}