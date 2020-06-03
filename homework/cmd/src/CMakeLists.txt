target_sources(bulk PRIVATE
        main.cpp
        block_reader.hpp block_reader.cpp
        line_reader.hpp line_reader.cpp
        observable.hpp
        block_printer.hpp block_printer.cpp
        block_file_printer.hpp block_file_printer.cpp
        )