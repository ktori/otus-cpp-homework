//
// Created by victoria on 31.05.20.
//

#pragma once

#include <utility>

template<class Tup, class Func, std::size_t ...Is>
constexpr void static_for_impl(Tup&& t, Func&& f, std::index_sequence<Is...>)
{
	( f(std::integral_constant<std::size_t, Is>{}, std::get<Is>(t)), ... );
}

/**
 * Helper function to iterate over a tuple
 * @tparam T Tuple type arguments
 * @tparam Func Function type
 * @param t Tuple
 * @param f Function
 */
template<class ... T, class Func>
constexpr void static_for(const std::tuple<T...>& t, Func&& f)
{
	static_for_impl(t, std::forward<Func>(f), std::make_index_sequence<sizeof...(T)>{});
}