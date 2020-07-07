/*
 * Created by victoria on 07.07.2020.
 */

#pragma once

#include <boost/filesystem/path.hpp>

namespace bayan
{

struct options
{
	std::vector<boost::filesystem::path> include{};
	std::vector<boost::filesystem::path> exclude{};
	size_t depth{};
	size_t minimum_size{};
	std::vector<std::string> name_masks{};
	size_t block_size{};
	std::string algorithm{};
};

options parse_options(int argc, const char **argv);

}