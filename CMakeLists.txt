cmake_minimum_required(VERSION 3.16)

project(mini-monitor
    VERSION 0.1
    DESCRIPTION "Mini Energy Monitoring Backend"
    LANGUAGES CXX
)

# Require C++20
set(CMAKE_CXX_STANDARD 20)

# Create executable
add_executable(mini-monitor
    src/main.cpp
    src/app/Application.cpp
	src/database/Database.cpp
)

# Include directories
target_include_directories(mini-monitor
    PRIVATE 
		${CMAKE_SOURCE_DIR}/src
		${PQXX_INCLUDE_DIRS}
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

target_link_libraries(mini-monitor
    PRIVATE 
		${PQXX_LIB}
		${PQ_LIB}
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
