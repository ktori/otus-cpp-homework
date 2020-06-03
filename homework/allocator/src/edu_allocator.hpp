//
// Created by victoria on 18.05.20.
//

#pragma once

#include <cstddef>
#include <memory>
#include <cstdlib>
#include <forward_list>
#include <cassert>

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
		auto& block = get_block_for_alloc(n);

		return block.reserve(n);
	}

	void deallocate(pointer p, size_type n)
	{
		// TODO
	}

	template<class U>
	struct rebind
	{
		typedef edu_allocator<U, batch_count> other;
	};

private:
	struct block
	{
		inline explicit block(size_t required_count) :
			max_count{
				required_count % batch_count
				? (required_count / batch_count) + 1 * batch_count
				: required_count
			}, data{ reinterpret_cast<pointer>(std::malloc(max_count * sizeof(T))) }
		{
		}

		inline ~block()
		{
			std::free(data);
		}

		inline bool can_fit(size_t element_count) const
		{
			return count + element_count < max_count;
		}

		inline pointer reserve(size_t element_count)
		{
			auto ptr = data + sizeof(value_type) * count;
			count += element_count;

			assert(count <= max_count);

			return ptr;
		}

		size_t count{};
		const size_t max_count{};
		pointer data;
	};

	block& get_block_for_alloc(size_t element_count)
	{
		// find a block that would fit
		for (auto& block : blocks)
		{
			if (block.can_fit(element_count))
				return block;
		}

		// create a new block that will fit
		return blocks.emplace_front(element_count);
	}

	std::forward_list<block> blocks{};
};
