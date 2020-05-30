//
// Created by victoria on 30.05.20.
//

#include "command_block.hpp"

std::ostream& bulk::operator<<(std::ostream& stream, const bulk::CommandBlock& block)
{
	if (block.commands.empty())
		return stream;

	stream << block.commands.at(0);

	for (auto i = 1; i < block.commands.size(); ++i)
		stream << ", " << block.commands.at(i);

	return stream;
}