//
// Created by victoria on 31.05.20.
//

/**
 * @file
 * @author ktori
 * @brief Header file for LineReader class
 */

#pragma once

#include "observable.hpp"

#include <istream>

namespace bulk
{

	/**
	 * Reads an input stream line-by-line, emits every line
	 */
	class LineReader : public AbstractObservable<std::string>
	{
	public:
		~LineReader() override = default;

		/**
		 * Creates a reader, reading lines from the stream
		 * @param stream Stream to read from
		 */
		explicit LineReader(std::istream& stream);

		/**
		 * Attempts to read a single line
		 * @return true if reading was successful, false if EOF was reached, or other input error occurred
		 */
		bool read_line();

	private:
		std::istream& stream;
	};

}