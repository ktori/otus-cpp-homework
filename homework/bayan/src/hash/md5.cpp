/*
 * Created by victoria on 07.07.2020.
 */

#include "md5.hpp"

#include <stdexcept>

bayan::hash::md5::md5()
{
	if (MD5_Init(&ctx))
		throw std::runtime_error("unable to create md5 context");
}

void
bayan::hash::md5::update(const char *data, size_t size)
{
	MD5_Update(&ctx, data, size);
}

std::vector<uint8_t>
bayan::hash::md5::finish()
{
	std::vector<uint8_t> result{};
	result.resize(MD5_DIGEST_LENGTH);

	MD5_Final(result.data(), &ctx);

	return result;
}
