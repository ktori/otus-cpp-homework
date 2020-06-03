//
// Created by victoria on 31.05.20.
//

#include "line_reader.hpp"

bulk::LineReader::LineReader(std::istream& stream) : stream(stream)
{
}

bool bulk::LineReader::read_line()
{
	if (!stream)
		return false;

	std::string line;
	auto result = bool(std::getline(stream, line));
	if (result)
		emit(line);

	return result;
}

