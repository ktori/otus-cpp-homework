//
// Created by victoria on 31.05.20.
//

/**
 * @file
 * @brief Contains print_ip function
 */

#pragma once

#include "is_stl_container_like.hpp"
#include "is_string.hpp"
#include "is_uniform_tuple.hpp"
#include "static_for.hpp"

#include <type_traits>
#include <iostream>
#include <utility>

template<typename T>
struct false_type_with_t : std::false_type
{
};

/**
 * Print an IP to stream
 * @tparam T
 * @param stream Stream to write to
 * @param data IP address
 */
template<typename T>
void print_ip(const T& data, std::ostream& stream = std::cout)
{
	if constexpr (std::is_integral_v<T>)
	{
		constexpr auto mask = static_cast<T>(0xFF);
		constexpr auto byte_count = sizeof(T);
		auto offset = (byte_count - 1) * 8u;
		stream << (unsigned((data >> offset) & mask) & 0xFFu);
		for (auto i = 1; i < byte_count; ++i)
		{
			offset -= 8;
			stream << '.' << (unsigned(data >> offset & mask) & 0xFFu);
		}
	}
	else if constexpr (is_string_v<T> or is_c_string_v<T>)
	{
		stream << data;
	}
	else if constexpr (is_stl_container_like_v<T>)
	{
		auto it = data.begin();
		auto end = data.end();

		stream << *(it++);

		while (it != end)
		{
			stream << '.' << *(it++);
		}
	}
	else if constexpr (is_uniform_tuple_v<T>)
	{
		static_for(data, [&](auto i, auto p) constexpr {
			if constexpr (i == 0)
			{
				stream << p;
			}
			else
			{
				stream << '.' << p;
			}
		});
	}
	else
	{
		static_assert(false_type_with_t<T>::value, "Unsupported type");
	}
}
