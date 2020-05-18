//
// Created by victoria on 18.05.20.
//

#pragma once

#include <cstddef>
#include <memory>

template<typename T, size_t size, typename Alloc = std::allocator<T>>
class edu_container
{
public:
	using value_type = T;
	using pointer = value_type*;
	using size_type = size_t;

	edu_container() : data{ allocator.allocate(size) }
	{
	}
	~edu_container()
	{
		allocator.deallocate(data, size);
	}

	[[nodiscard]] auto begin() const
	{
		return data;
	}

	[[nodiscard]] auto end() const
	{
		return data + size;
	}

	void insert(value_type value)
	{
		if (count == size)
			throw std::out_of_range("container size exceeded");

		data[count] = value;
		count++;
	}

private:
	Alloc allocator{};
	size_type count{};
	pointer data{ nullptr };
};