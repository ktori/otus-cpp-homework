//
// Created by victoria on 30.05.20.
//

#pragma once

#include "detail/generators.hpp"
#include "detail/indexer.hpp"

#include <cstddef>
#include <tuple>
#include <unordered_map>

namespace matrix
{

	/**
	 * N-dimensional sparse matrix class
	 * @tparam T type to be stored in the matrix
	 * @tparam Default default value to be used if element was not inserted
	 * @tparam N number of dimensions
	 */
	template<typename T, T Default, size_t N = 2>
	struct matrix
	{
		constexpr static size_t dimension = N;
		constexpr static T default_value = Default;
		using value_type = T;
		using size_type = size_t;
		using index_type = size_t;
		using key_type = typename detail::generate_matrix_key_type<index_type, dimension>::type;
		using iterator_value_type = typename detail::generate_matrix_iterator_value_type<index_type,
																						 value_type,
																						 dimension>::type;

		[[nodiscard]] size_type size() const
		{
			return data.size();
		}

		detail::indexer<matrix, dimension, index_type, key_type, value_type, dimension - 1> operator[](index_type i)
		{
			return detail::indexer<matrix, dimension, index_type, key_type, value_type, dimension - 1>(*this, {}, i);
		}

		value_type get(key_type key) const
		{
			auto it = data.find(key);
			if (it == data.end())
				return default_value;

			return it->second;
		}

		void set(key_type key, value_type value)
		{
			if (value == default_value)
				remove(key);
			else
			{
				auto x = data.emplace(key, value);
				if (!x.second)
					x.first->second = value;
			}
		}

		void remove(key_type key)
		{
			data.erase(key);
		}

		struct hash
		{
			template<size_t I>
			inline void hash_combine(std::size_t& seed, const key_type& k) const
			{
				std::hash<index_type> hash_impl;
				seed ^= (hash_impl(std::get<I>(k)) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
				if constexpr (I != 0)
				{
					hash_combine<I - 1>(seed, k);
				}
			}

			size_t operator()(const key_type& k) const
			{
				size_t seed = 0;
				hash_combine<dimension - 1>(seed, k);
				return seed;
			}
		};

		struct equality
		{
			template<size_t I>
			inline bool eq(const key_type& left, const key_type& right) const
			{
				if constexpr (I == 0)
					return std::get<I>(left) == std::get<I>(right);
				else
					return std::get<I>(left) == std::get<I>(right) && eq<I - 1>(left, right);
			}

			bool operator()(const key_type& left, const key_type& right) const
			{
				return eq<dimension - 1>(left, right);
			}
		};

		using map_type = typename std::unordered_map<key_type, value_type, hash, equality>;
		using map_iterator_type = typename map_type::iterator;

		struct iterator
		{
			explicit iterator(map_iterator_type it) : it{ it }
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
			iterator_value_type operator*() const
			{
				return make_result(it->first, it->second, std::make_index_sequence<dimension>{});
			}

		private:
			template<size_t... Is>
			static constexpr iterator_value_type
			make_result(key_type key, value_type value, std::index_sequence<Is...>)
			{
				return std::make_tuple(std::get<Is>(key)..., value);
			}

			map_iterator_type it;
		};

		iterator begin()
		{
			return iterator(data.begin());
		}

		iterator end()
		{
			return iterator(data.end());
		}

	private:
		map_type data{};
	};

}