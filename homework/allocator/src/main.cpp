//
// Created by victoria on 18.05.20.
//

#include "edu_allocator.hpp"
#include "edu_container.hpp"

#include <map>
#include <iostream>

template<typename Map>
void work_on_map(Map& map, size_t count, std::ostream& stream)
{
	map[0] = 1;

	for (auto i = 1; i < count; ++i)
		map[i] = i * map[i - 1];

	for (const auto& entry : map)
		stream << entry.first << ' ' << entry.second << '\n';
}

template<typename InsertableIterable>
void work_on_container(InsertableIterable& ii, size_t count, std::ostream& stream)
{
	for (auto i = 0; i < count; ++i)
		ii.insert(i);

	for (auto i : ii)
		stream << i << '\n';
}

int main()
{
	std::map<int, int> first{};
	work_on_map(first, 10, std::cout);

	std::map<int, int, std::less<>, edu_allocator<std::pair<int, int>, 10>> second{};
	work_on_map(second, 10, std::cout);

	edu_container<int, 10> third{};
	work_on_container(third, 10, std::cout);

	edu_container<int, 10, edu_allocator<int, 10>> fourth{};
	work_on_container(fourth, 10, std::cout);

	return 0;
}