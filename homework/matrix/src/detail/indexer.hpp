//
// Created by victoria on 30.05.20.
//

#pragma once

#include <cstddef>
#include <array>
#include <tuple>

namespace matrix::detail
{

	template<typename matrix, size_t dimension, typename index_type, typename key_type, typename value_type, size_t D>
	struct indexer
	{
		constexpr static size_t data_size = dimension - D;

		indexer(matrix& mx, std::array<index_type, data_size - 1> array, index_type index) : data{},
																							 mx{ mx }
		{
			std::copy(array.begin(), array.end(), data.begin());
			data[data_size - 1] = index;
		}

		indexer<matrix, dimension, index_type, key_type, value_type, D - 1> operator[](index_type i)
		{
			return indexer<matrix, dimension, index_type, key_type, value_type, D - 1>(mx, data, i);
		}

	private:
		std::array<index_type, data_size> data{};
		matrix& mx;
	};

	template<typename matrix, size_t dimension, typename index_type, typename key_type, typename value_type, size_t D>
	struct const_indexer
	{
		constexpr static size_t data_size = dimension - D;

		const_indexer(const matrix& mx, std::array<index_type, data_size - 1> array, index_type index) : data{},
																										 mx{ mx }
		{
			std::copy(array.begin(), array.end(), data.begin());
			data[data_size - 1] = index;
		}

		const_indexer<matrix, dimension, index_type, key_type, value_type, D - 1> operator[](index_type i)
		{
			return const_indexer<matrix, dimension, index_type, key_type, value_type, D - 1>(mx, data, i);
		}

	private:
		std::array<index_type, data_size> data{};
		const matrix& mx;
	};

	template<typename matrix, size_t dimension, typename index_type, typename key_type, typename value_type>
	struct indexer<matrix, dimension, index_type, key_type, value_type, 0>
	{
		template<size_t... Is>
		static constexpr key_type
		make_key(std::array<index_type, dimension - 1> array, index_type index, std::index_sequence<Is...>)
		{
			return std::make_tuple(array[Is]..., index);
		}

		indexer(matrix& mx, std::array<index_type, dimension - 1> array, index_type index) :
			key{ make_key(array, index, std::make_index_sequence<dimension - 1>{}) }, mx{ mx }
		{
		}

		explicit operator value_type() const
		{
			return mx.get(key);
		}

		indexer& operator=(const value_type& value)
		{
			mx.set(key, value);
			return *this;
		}

		bool operator==(const value_type& value) const
		{
			return mx.get(key) == value;
		}

	private:
		key_type key;
		matrix& mx;
	};

	template<typename matrix, size_t dimension, typename index_type, typename key_type, typename value_type>
	struct const_indexer<matrix, dimension, index_type, key_type, value_type, 0>
	{
		template<size_t... Is>
		static constexpr key_type
		make_key(std::array<index_type, dimension - 1> array, index_type index, std::index_sequence<Is...>)
		{
			return std::make_tuple(array[Is]..., index);
		}

		const_indexer(const matrix& mx, std::array<index_type, dimension - 1> array, index_type index) :
			key{ make_key(array, index, std::make_index_sequence<dimension - 1>{}) }, mx{ mx }
		{
		}

		explicit operator value_type() const
		{
			return mx.get(key);
		}

		bool operator==(const value_type& value) const
		{
			return mx.get(key) == value;
		}

	private:
		key_type key;
		const matrix& mx;
	};

}