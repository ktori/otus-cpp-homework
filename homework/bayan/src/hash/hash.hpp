/*
 * Created by victoria on 07.07.2020.
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <memory>
#include <string>

namespace bayan::hash
{

class hash
{
  public:
	virtual ~hash() = default;

	virtual void update(const char *data, size_t size) = 0;
	virtual std::vector<uint8_t> finish() = 0;
};

std::unique_ptr<hash> create_hash(std::string_view algorithm);

}