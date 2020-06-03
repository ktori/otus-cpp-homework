//
// Created by victoria on 03.06.20.
//

#include "block_file_printer.hpp"

#include <chrono>
#include <fstream>

void bulk::BlockFilePrinter::update(const std::vector<std::string>& data)
{
	if (data.empty())
		return;

	auto seconds =
		std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	auto filename = "bulk" + std::to_string(seconds) + ".log";

	std::ofstream log_file{ filename, std::ios::out };

	log_file << "bulk: ";

	log_file << data.at(0);

	for (auto i = 1; i < data.size(); ++i)
		log_file << ", " << data.at(i);

	log_file << "\n";
}

std::shared_ptr<bulk::BlockFilePrinter> bulk::BlockFilePrinter::create()
{
	return std::shared_ptr<BlockFilePrinter>(new BlockFilePrinter);
}
