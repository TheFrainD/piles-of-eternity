#pragma once

#include <string_view>
#include <variant>
#include <vector>

namespace comp {
std::variant<std::vector<char>, std::string_view> compress_buffer(
    const std::vector<char> &buffer) noexcept;
}  // namespace comp