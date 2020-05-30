//
// Created by victoria on 30.05.20.
//

#pragma once

#include <utility>
#include <vector>
#include <string>
#include <ostream>

namespace bulk
{

	class CommandBlock
	{
	public:
		explicit CommandBlock(std::vector<std::string> commands) : commands(std::move(commands))
		{
		}

		friend std::ostream& operator<<(std::ostream& stream, const CommandBlock& block);
	private:
		std::vector<std::string> commands{};
	};

}