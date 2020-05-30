//
// Created by victoria on 30.05.20.
//

#include "block_reader.hpp"

std::unique_ptr<bulk::CommandBlock> bulk::BlockReader::read_block()
{
	if (!stream)
		return nullptr;

	std::vector<std::string> commands{};
	commands.reserve(block_size);
	size_t depth = 0;

	std::string s;
	while (std::getline(stream, s))
	{
		if (s == "{")
		{
			depth++;
			continue;
		}
		if (s == "}")
		{
			if (!depth || !--depth)
				break;
			continue;
		}
		commands.push_back(std::move(s));
		if (depth == 0 && commands.size() >= block_size)
			break;
	}

	if (depth == 0)
		return std::make_unique<CommandBlock>(commands);

	return nullptr;
}
