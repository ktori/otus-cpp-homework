//
// Created by victoria on 31.05.20.
//

#pragma once

#include <type_traits>

/**
 * Determine if a type is container-like
 * @tparam T Type to be checked
 * @see https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time
 */
template<typename T>
struct is_stl_container_like
{
	typedef typename std::remove_const<T>::type test_type;

	template<typename A>
	static constexpr bool test(
		A* pt,
		A const* cpt = nullptr,
		decltype(pt->begin())* = nullptr,
		decltype(pt->end())* = nullptr,
		decltype(cpt->begin())* = nullptr,
		decltype(cpt->end())* = nullptr,
		typename A::iterator* pi = nullptr,
		typename A::const_iterator* pci = nullptr,
		typename A::value_type* pv = nullptr)
	{
		typedef typename A::iterator iterator;
		typedef typename A::const_iterator const_iterator;
		typedef typename A::value_type value_type;
		return std::is_same<decltype(pt->begin()), iterator>::value &&
			std::is_same<decltype(pt->end()), iterator>::value &&
			std::is_same<decltype(cpt->begin()), const_iterator>::value &&
			std::is_same<decltype(cpt->end()), const_iterator>::value &&
			std::is_same<decltype(**pi), value_type&>::value &&
			std::is_same<decltype(**pci), value_type const&>::value;

	}

	template<typename A>
	static constexpr bool test(...)
	{
		return false;
	}

	static const bool value = test<test_type>(nullptr);
};

template<typename T>
constexpr bool is_stl_container_like_v = is_stl_container_like<T>::value;