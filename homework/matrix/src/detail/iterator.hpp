//
// Created by victoria on 31.05.20.
//

#pragma once

#include <utility>
#include <cstddef>
#include <tuple>

namespace matrix::detail
{

	template<typename MapKeyT, typename ValueT, typename MapIterT, typename IterValueT, size_t dimension>
	struct iterator
	{
		explicit iterator(MapIterT it) : it{ it }
		{
		}

		iterator operator++()
		{
			++it;
			return *this;
		}
		bool operator!=(const iterator& other) const
		{
			return it != other.it;
		}
		IterValueT operator*() const
		{
			return make_result(it->first, it->second, std::make_index_sequence<dimension>{});
		}

	private:
		template<size_t... Is>
		static constexpr IterValueT
		make_result(MapKeyT key, ValueT value, std::index_sequence<Is...>)
		{
			return std::make_tuple(std::get<Is>(key)..., value);
		}

		MapIterT it;
	};

}