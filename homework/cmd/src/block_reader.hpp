//
// Created by victoria on 30.05.20.
//

#pragma once

#include "observable.hpp"

#include <cstddef>
#include <memory>
#include <vector>
#include <string>

namespace bulk
{

	/**
	 * Reads blocks from stream of lines, emits blocks when they are formed correctly
	 * By default, a block is a vector of size determined by block_size, but this can be changed if block contains
	 * commands like { and }
	 */
	class BlockReader
		: public AbstractObservable<std::vector<std::string>>,
		  public Observer<std::string>,
		  public std::enable_shared_from_this<BlockReader>
	{
	public:
		~BlockReader() override = default;

		/**
		 * Creates an instance of BlockReader
		 * @param block_size Amount of lines the block will contain if input doesn't have { or } commands
		 * @return Instance of BlockReader
		 */
		static std::shared_ptr<BlockReader> create(size_t block_size);

		/**
		 * Process a line
		 * @param data Line without trailing newline character, "{" and "}" have special meaning
		 */
		void update(const std::string& data) override;

		/**
		 * Flushes (emits) a block, only if "{" command wasn't issued, or had "}" that was paired to it
		 */
		void flush();

		const size_t block_size;
	private:
		explicit BlockReader(size_t block_size);

		std::vector<std::string> stored_commands{};
		size_t depth{};
	};

}