add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(spdlog REQUIRED)
find_package(EnTT REQUIRED)
find_package(Eigen3)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 ZLIB::ZLIB spdlog::spdlog EnTT::EnTT Eigen3::Eigen)