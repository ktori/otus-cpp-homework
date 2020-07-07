/*
 * Created by victoria on 07.07.2020.
 */

#pragma once

#include "hash.hpp"

#include <openssl/md5.h>

namespace bayan::hash
{

class md5 : public hash
{
  public:
	md5();
	~md5() override = default;

	void update(const char *data, size_t size) override;
	std::vector<uint8_t> finish() override;

  private:
	MD5_CTX ctx{};
};

}
