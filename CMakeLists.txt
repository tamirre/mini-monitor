cmake_minimum_required(VERSION 3.16)

project(mini-monitor
    VERSION 0.1
    DESCRIPTION "Mini Energy Monitoring Backend"
    LANGUAGES CXX
)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create executable
add_executable(mini-monitor
    src/main.cpp
    src/app/Application.cpp
)

# Include directories
target_include_directories(mini-monitor
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

find_package(PostgreSQL REQUIRED)

target_link_libraries(mini-monitor
    PRIVATE
        PostgreSQL::PostgreSQL
)

# Warnings (GCC/Clang)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mini-monitor PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
    )


endif()
