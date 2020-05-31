//
// Created by victoria on 18.05.20.
//

#pragma once

#include <cstddef>
#include <memory>
#include <cstdlib>

template<typename T, size_t batch_count>
class edu_allocator
{
public:
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	[[nodiscard]] pointer allocate(size_type n)
	{
		auto adjusted_count = n % batch_count ? batch_count * (n / batch_count + 1) : n;

		return reinterpret_cast<pointer>(std::malloc(adjusted_count * sizeof(T)));
	}

	void deallocate(pointer p, size_type n)
	{
		std::free(p);
	}

	template<class U>
	struct rebind
	{
		typedef edu_allocator<U, batch_count> other;
	};
};
