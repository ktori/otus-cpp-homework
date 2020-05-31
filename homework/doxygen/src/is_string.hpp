//
// Created by victoria on 31.05.20.
//

/**
 * @file
 * @brief Helper types
 */

#pragma once

#include <string>

template<typename T, typename = void>
struct is_string
{
	static constexpr bool value = false;
};

template<typename T, class Traits, class Alloc>
struct is_string<std::basic_string<T, Traits, Alloc>, void>
{
	static constexpr bool value = true;
};

template<typename T>
constexpr bool is_string_v = is_string<T>::value;

template<typename T>
constexpr bool is_c_string_v = std::is_same_v<char*,
											  std::remove_reference_t<
												  std::remove_cv_t<
													  std::decay_t<T>
												  >
											  >
>;