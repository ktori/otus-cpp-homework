//
// Created by victoria on 30.05.20.
//

#include "line_reader.hpp"
#include "block_reader.hpp"
#include "block_printer.hpp"

#include <iostream>
#include <charconv>
#include <cstring>
#include <limits>

size_t parse_block_size(int argc, char** argv)
{
	auto error = std::numeric_limits<size_t>::max();

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <N>\n";

		return error;
	}

	std::string block_size_str{ argv[1] };
	size_t block_size;

	if (auto[p, ec] = std::from_chars(block_size_str.data(),
			block_size_str.data() + block_size_str.size(),
			block_size); ec != std::errc())
	{
		std::cerr << "Unable to parse command line argument: " << block_size_str << "\n";

		return error;
	}

	return block_size;
}

int main(int argc, char** argv)
{
	auto block_size = parse_block_size(argc, argv);

	if (block_size == std::numeric_limits<size_t>::max())
		return 1;

	bulk::LineReader line_reader{ std::cin };
	auto block_reader = bulk::BlockReader::create(block_size);
	auto printer = bulk::BlockPrinter::create(std::cout);

	line_reader.add_subscriber(block_reader);
	block_reader->add_subscriber(printer);

	while (line_reader.read_line());

	block_reader->flush();

	return 0;
}