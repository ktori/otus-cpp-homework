//
// Created by victoria on 31.05.20.
//

#include "block_printer.hpp"

void bulk::BlockPrinter::update(const std::vector<std::string>& data)
{
	if (data.empty())
		return;

	stream << "bulk: ";

	stream << data.at(0);

	for (auto i = 1; i < data.size(); ++i)
		stream << ", " << data.at(i);

	stream << "\n";
	stream.flush();
}

bulk::BlockPrinter::BlockPrinter(std::ostream& stream) : stream(stream)
{
}

std::shared_ptr<bulk::BlockPrinter> bulk::BlockPrinter::create(std::ostream& stream)
{
	return std::shared_ptr<BlockPrinter>(new BlockPrinter(stream));
}

