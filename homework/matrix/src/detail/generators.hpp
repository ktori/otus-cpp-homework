//
// Created by victoria on 30.05.20.
//

#pragma once

#include <cstddef>
#include <utility>

namespace matrix::detail
{

	template<typename T, size_t N>
	class generate_matrix_key_type
	{
		template<typename = std::make_index_sequence<N>>
		struct impl;

		template<size_t... Is>
		struct impl<std::index_sequence<Is...>>
		{
			template<size_t>
			using wrap = T;

			using type = std::tuple<wrap<Is>...>;
		};

	public:
		using type = typename impl<>::type;
	};

	template<typename T, typename V, size_t N>
	class generate_matrix_iterator_value_type
	{
		template<typename = std::make_index_sequence<N>>
		struct impl;

		template<size_t... Is>
		struct impl<std::index_sequence<Is...>>
		{
			template<size_t>
			using wrap = T;

			using type = std::tuple<wrap<Is>..., V>;
		};

	public:
		using type = typename impl<>::type;
	};

}
