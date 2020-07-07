/*
 * Created by victoria on 07.07.2020.
 */

#include "hash.hpp"

#include "md5.hpp"

using namespace bayan::hash;

std::unique_ptr<hash>
bayan::hash::create_hash(std::string_view algorithm)
{
	if (algorithm == "md5")
		return std::make_unique<md5>();

	return nullptr;
}
