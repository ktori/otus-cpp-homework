//
// Created by victoria on 30.05.20.
//

#include "block_reader.hpp"

bulk::BlockReader::BlockReader(size_t block_size) : block_size(block_size)
{
	stored_commands.reserve(block_size);
}

std::shared_ptr<bulk::BlockReader> bulk::BlockReader::create(size_t block_size)
{
	return std::shared_ptr<BlockReader>(new bulk::BlockReader(block_size));
}

void bulk::BlockReader::update(const std::string& data)
{
	if (data == "{")
	{
		depth++;
		return;
	}
	if (data == "}")
	{
		if (!depth || !--depth)
			flush();
		return;
	}

	stored_commands.push_back(data);

	if (!depth && stored_commands.size() >= block_size)
		flush();
}

void bulk::BlockReader::flush()
{
	if (depth || stored_commands.empty())
		return;

	emit(stored_commands);
	stored_commands.clear();
}
