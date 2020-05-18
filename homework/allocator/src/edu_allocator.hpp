//
// Created by victoria on 18.05.20.
//

#pragma once

#include <cstddef>
#include <memory>

template<typename T, size_t base_count>
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

	pointer base{ nullptr };
	size_type allocated_elements{};

	edu_allocator() : base{ reinterpret_cast<pointer>(std::malloc(base_count * sizeof(value_type))) }
	{
	}
	edu_allocator(const edu_allocator& other) = delete;
	edu_allocator(edu_allocator&& other) = delete;
	edu_allocator& operator=(const edu_allocator& other) = delete;
	edu_allocator& operator=(edu_allocator&& other) = delete;
	~edu_allocator()
	{
		std::free(base);
	}

	[[nodiscard]] pointer allocate(size_type n)
	{
		if (allocated_elements + n > base_count)
			throw std::bad_alloc();

		allocated_elements += n;

		return reinterpret_cast<pointer>(base + allocated_elements - n);
	}

	void deallocate(pointer p, size_type n)
	{
		if (p != base + allocated_elements - n)
			throw std::bad_alloc();

		allocated_elements -= n;
	}

	template<class U>
	struct rebind
	{
		typedef edu_allocator<U, base_count> other;
	};
};
