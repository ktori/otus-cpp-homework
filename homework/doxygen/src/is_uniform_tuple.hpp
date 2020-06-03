//
// Created by victoria on 31.05.20.
//

#pragma once

#include <tuple>
#include <type_traits>

template<typename T, typename = void>
struct is_uniform_tuple
{
	static constexpr bool value = false;
};

template<typename T, typename... Ts>
constexpr bool is_same_all_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename... Ts>
struct is_uniform_tuple<std::tuple<Ts...>>
{
	static constexpr bool value = is_same_all_v<Ts...>;
};

/**
 * Checks if type is a tuple with uniform parameter types
 * @tparam T Type to be checked
 */
template<typename T>
constexpr bool is_uniform_tuple_v = is_uniform_tuple<std::remove_const_t<std::remove_cv_t<T>>>::value;