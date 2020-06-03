//
// Created by victoria on 18.05.20.
//

#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

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
		for (auto i = 0; i < count; ++i)
		{
			std::allocator_traits<Alloc>::destroy(allocator, &data[i]);
		}
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

	void insert(const value_type& value)
	{
		emplace(value);
	}

	void insert(value_type&& value)
	{
		emplace(std::move(value));
	}

	template<typename... Args>
	T& emplace(Args&& ... args)
	{
		if (count == size)
			throw std::out_of_range("container size exceeded");

		std::allocator_traits<Alloc>::construct(allocator, &data[count], std::forward<Args>(args)...);
		count++;

		return data[count - 1];
	}

private:
	Alloc allocator{};
	size_type count{};
	pointer data{ nullptr };
};