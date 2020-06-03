//
// Created by victoria on 03.06.20.
//

#pragma once

#include "observable.hpp"

#include <vector>
#include <string>

namespace bulk
{

	/**
	 * @brief Saves each block into a separate file
	 * file name format: bulk123456.log
	 * Where 123456 is the timestamp in seconds
	 */
	class BlockFilePrinter
		: public Observer<std::vector<std::string>>, public std::enable_shared_from_this<BlockFilePrinter>
	{
	public:
		~BlockFilePrinter() override = default;

		static std::shared_ptr<BlockFilePrinter> create();

		void update(const std::vector<std::string>& data) override;

	private:
		BlockFilePrinter() = default;
	};

}