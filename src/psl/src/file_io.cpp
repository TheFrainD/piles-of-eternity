#include "psl/file_io.h"

#include <fstream>

namespace psl {
namespace fs = std::filesystem;

std::optional<std::vector<char>> load_file(const fs::path &path) noexcept {
    std::ifstream file(path);
    if (!file.is_open()) {
        return std::nullopt;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
    return buffer;
}

Result<std::vector<std::filesystem::path>> find_files_with_extension(
    const fs::path &directory, const std::string_view &extension,
    bool recursive) noexcept {
    std::vector<fs::path> files;

    auto process_entry = [&files, extension](const auto &entry) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            files.push_back(entry.path());
        }
    };

    try {
        if (recursive) {
            for (const auto &entry :
                 fs::recursive_directory_iterator(directory)) {
                process_entry(entry);
            }
            return files;
        }

        for (const auto &entry : fs::directory_iterator(directory)) {
            process_entry(entry);
        }
        return files;
    } catch (const fs::filesystem_error &err) {
        return err.what();
    }
}
}  // namespace psl