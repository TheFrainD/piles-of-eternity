#pragma once

#include <filesystem>
#include <optional>
#include <vector>

namespace file_io {
std::optional<std::vector<char>> load_file(
    const std::filesystem::path &path) noexcept;
}  // namespace file_io