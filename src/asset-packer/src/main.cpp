#include <spdlog/spdlog.h>

#include "compression.h"
#include "file_io.h"

int main(int argc, char *argv[]) {
    using namespace std::literals;

    if (argc != 2) {
        spdlog::error("Requires only one arguments. {} given."sv, argc - 1);
        return 1;
    }

    std::filesystem::path filepath(argv[1]);

    auto buf = file_io::load_file(filepath);
    if (!buf.has_value()) {
        spdlog::error("Failed to load file at {}"sv, filepath.string());
        return 1;
    }

    auto result = comp::compress_buffer(buf.value());
    if (std::holds_alternative<std::string_view>(result)) {
        spdlog::error("Compression failed! Error: {}",
                      std::get<std::string_view>(result));
        return 1;
    }

    auto compressed_buf = std::get<std::vector<char>>(result);

    spdlog::info("Success! Original size: {}\tCompressed size: {}"sv,
                 buf->size(), compressed_buf.size());

    return 0;
}