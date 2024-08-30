#include "compression.h"

#include <spdlog/spdlog.h>
#include <zstd.h>

#include <thread>

namespace {
constexpr unsigned int BASE_THREAD_COUNT = 4;
}

namespace comp {
std::variant<std::vector<char>, std::string_view> compress_buffer(
    const std::vector<char> &buffer) noexcept {
    unsigned int thread_count = std::thread::hardware_concurrency();
    if (thread_count == 0) {
        thread_count = BASE_THREAD_COUNT;
    }

    ZSTD_CCtx *cctx = ZSTD_createCCtx();
    if (!cctx) {
        return "Failed to create ZSTD_CCtx";
    }

    ZSTD_CCtx_setParameter(cctx, ZSTD_c_nbWorkers, thread_count);

    size_t compressed_size = ZSTD_compressBound(buffer.size());
    std::vector<char> compressed_buffer(compressed_size);

    compressed_size =
        ZSTD_compress2(cctx, compressed_buffer.data(), compressed_size,
                       buffer.data(), buffer.size());

    if (ZSTD_isError(compressed_size)) {
        ZSTD_freeCCtx(cctx);
        return ZSTD_getErrorName(compressed_size);
    }

    compressed_buffer.resize(compressed_size);

    ZSTD_freeCCtx(cctx);

    if (compressed_size > buffer.size()) {
        spdlog::warn(
            "Compressed size is bigger than the original size. Skipping "
            "compression.");
        return buffer;
    }

    return compressed_buffer;
}
}  // namespace comp