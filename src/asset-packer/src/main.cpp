#include <spdlog/spdlog.h>

#include <iostream>

#include "compression.h"
#include "file_io.h"

int main(int argc, char *argv[]) {
    using namespace std::literals;
    namespace fs = std::filesystem;

    if (argc != 2) {
        spdlog::error("Requires only one arguments. {} given."sv, argc - 1);
        return 1;
    }

    fs::path directory_path(argv[1]);

    auto result = file_io::find_files_with_extension(directory_path, ".json");
    if (std::holds_alternative<std::string_view>(result)) {
        spdlog::error("Failed to scan directory! Error: {}"sv,
                      std::get<std::string_view>(result));
        return 1;
    }

    auto files = std::get<std::vector<fs::path>>(result);
    for (const auto &filepath : files) {
        std::cout << filepath << '\n';
    }

    return 0;
}