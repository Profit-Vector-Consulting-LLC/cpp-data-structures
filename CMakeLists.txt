cmake_minimum_required(VERSION 3.15)

project(cpp-data-structures VERSION 1.0 LANGUAGES C CXX)

# C / C++ standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings for Clang/GCC on macOS
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Collect all .cpp and .c files under src/stack (and subfolders, if any)
file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/stack/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/stack/*.c"
)

# Optional: print them so you can see what CMake picked up
message(STATUS "Source files: ${SRC_FILES}")

# Fail early if nothing was found
if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found under src/stack/. Check paths and extensions.")
endif()

# Executable target
add_executable(cpp-data-structures ${SRC_FILES})

# Includes – your source folder and LLVM include
target_include_directories(cpp-data-structures PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/stack"
    "/usr/local/opt/llvm/include"
)

# LLVM library search paths
target_link_directories(cpp-data-structures PRIVATE
    "/usr/local/opt/llvm/lib/c++"
    "/usr/local/opt/llvm/lib"
)

# Link unwind as in your VS Code config
#target_link_libraries(cpp-data-structures PRIVATE
#    unwind
#)
