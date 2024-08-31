#pragma once

#include <filesystem>
#include <optional>
#include <variant>
#include <vector>

namespace file_io {
std::optional<std::vector<char>> load_file(
    const std::filesystem::path &path) noexcept;

std::variant<std::vector<std::filesystem::path>, std::string_view>
find_files_with_extension(const std::filesystem::path &directory,
                          const std::string_view &extension,
                          bool recursive = true) noexcept;
}  // namespace file_io