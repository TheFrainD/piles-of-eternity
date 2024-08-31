project(psl)

add_library(${PROJECT_NAME}
        include/psl/file_io.h
        src/file_io.cpp
        include/psl/result.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)