project(asset-packer)

add_executable(${PROJECT_NAME}
        src/main.cpp
        include/file_io.h
        src/file_io.cpp
        include/compression.h
        src/compression.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(zstd REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(${PROJECT_NAME}
        zstd::libzstd_static
        spdlog::spdlog)
