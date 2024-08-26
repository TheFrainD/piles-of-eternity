add_executable(${PROJECT_NAME}
        src/main.cpp
        include/resource/resource_manager.h
        include/game.h
        src/game.cpp
        include/graphics/window.h
        src/graphics/window.cpp
        include/graphics/graphics.h
        src/graphics/graphics.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(spdlog REQUIRED)
find_package(EnTT REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(stx REQUIRED)
find_package(gsl-lite REQUIRED)

target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2
        ZLIB::ZLIB
        spdlog::spdlog
        gsl::gsl-lite
        EnTT::EnTT
        Eigen3::Eigen
        stx::stx)