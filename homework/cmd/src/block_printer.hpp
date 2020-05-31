//
// Created by victoria on 31.05.20.
//

#pragma once

#include "observable.hpp"

#include <memory>
#include <ostream>
#include <vector>
#include <string>

namespace bulk
{

	/**
	 * Prints incoming blocks (vectors of string) in format: "bulk: A, B, C<newline>"
	 */
	class BlockPrinter : public Observer<std::vector<std::string>>, public std::enable_shared_from_this<BlockPrinter>
	{
	public:
		~BlockPrinter() override = default;

		/**
		 * Create an instance of BlockPrinter
		 * @param stream Stream to write to
		 * @return Instance of BlockPrinter
		 */
		static std::shared_ptr<bulk::BlockPrinter> create(std::ostream& stream);

		/**
		 * Process (print) a block, function from Observer
		 * @param data
		 */
		void update(const std::vector<std::string>& data) override;

	private:
		explicit BlockPrinter(std::ostream& stream);

		std::ostream& stream;
	};

}