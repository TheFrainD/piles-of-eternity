#include "file_io.h"

#include <fstream>

namespace file_io {
std::optional<std::vector<char>> load_file(
    const std::filesystem::path &path) noexcept {
    std::ifstream file(path);
    if (!file.is_open()) {
        return std::nullopt;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
    return buffer;
}
}  // namespace file_io