//
// Created by victoria on 30.05.20.
//

#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include "command_block.hpp"

namespace bulk
{

	class BlockReader
	{
	public:
		explicit BlockReader(std::istream& stream, size_t block_size) : block_size(block_size), stream(stream)
		{
		}

		std::unique_ptr<CommandBlock> read_block();

		const size_t block_size;
	private:
		std::istream& stream;
	};

}