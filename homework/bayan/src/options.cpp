/*
 * Created by victoria on 07.07.2020.
 */

#include "options.hpp"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <charconv>

size_t
get_size_factor(char suffix)
{
	switch (suffix)
	{
		case 'k':
		case 'K':
			return 1024;
		case 'm':
		case 'M':
			return 1024 * 1024;
		case 'g':
		case 'G':
			return 1024 * 1024 * 1024;
		default:
			throw std::runtime_error("unexpected suffix");
	}
}

size_t
parse_size(std::string_view size_str)
{
	if (size_str.empty())
		throw std::runtime_error("empty string passed to parse_size");

	size_t byte_count{};

	auto [p, ec] = std::from_chars(size_str.data(), size_str.data() + size_str.size(), byte_count);

	if (p == size_str.data() + size_str.size())
		return byte_count;

	if (p == size_str.data() + size_str.size() - 1)
		return byte_count * get_size_factor(size_str[size_str.size() - 1]);

	throw std::runtime_error("could not parse size");
}

bayan::options
bayan::parse_options(int argc, const char **argv)
{
	bayan::options result{};

	namespace po = boost::program_options;

	po::options_description desc{ "Options" };
	desc.add_options()("include,i", po::value<std::vector<std::string>>()->multitoken(), "Paths to include")(
	  "exclude,x", po::value<std::vector<std::string>>()->multitoken(), "Paths to exclude")("depth,d", po::value<int>()->default_value(0), "Depth")(
	  "minimum-size,m", po::value<std::string>()->default_value("1"), "Minimum file size, for example 4K")(
	  "name", po::value<std::vector<std::string>>()->multitoken(), "Filename mask")(
	  "block-size,b", po::value<std::string>()->default_value("8K"), "Block size")(
	  "algorithm,a", po::value<std::string>()->default_value("md5"), "Hashing algorithm");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("include"))
		for (const auto &s : vm["include"].as<std::vector<std::string>>())
			result.include.emplace_back(s);

	if (vm.count("exclude"))
		for (const auto &s : vm["exclude"].as<std::vector<std::string>>())
			result.exclude.emplace_back(s);

	if (vm.count("name"))
		for (const auto &s : vm["name"].as<std::vector<std::string>>())
			result.name_masks.emplace_back(s);

	result.minimum_size = parse_size(vm["minimum-size"].as<std::string>());
	result.block_size = parse_size(vm["block-size"].as<std::string>());
	result.algorithm = vm["algorithm"].as<std::string>();

	return result;
}
