cmake_minimum_required (VERSION 3.10)
project (LinAsmUnitTests)

set (CMAKE_CXX_STANDARD 23)

# Set the compiler flags
set ("CMAKE_CXX_FLAGS" "-Wall -march=native -O2")

# The library include files
include_directories (/usr/local/include)

# External library to test liblinasm.so
find_library (LINASM_LIB NAMES linasm PATHS /usr/local/lib64)

if (NOT LINASM_LIB)
    message (FATAL_ERROR "The library liblinasm.so is not found in /usr/local/lib64")
endif()

# Unit-test binary files
add_executable (ArrayTests ArrayTests.cpp)
add_executable (BitFieldTests BitFieldTests.cpp)

# Link the executable with the library
target_link_libraries (ArrayTests ${LINASM_LIB})
target_link_libraries (BitFieldTests ${LINASM_LIB})
