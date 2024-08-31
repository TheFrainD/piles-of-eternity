#pragma once

#include <filesystem>
#include <optional>
#include <variant>
#include <vector>

#include "psl/result.h"

namespace psl {
std::optional<std::vector<char>> load_file(
    const std::filesystem::path &path) noexcept;

Result<std::vector<std::filesystem::path>> find_files_with_extension(
    const std::filesystem::path &directory, const std::string_view &extension,
    bool recursive = true) noexcept;
}  // namespace psl