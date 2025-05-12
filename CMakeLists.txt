# CMakeList.txt : CMake project for CPP-Generator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)  # Ensure C++20 is enabled
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++20 features

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CPP-Generator")

add_library(CPP_GENERATOR 
    CPP-Generator.cpp
    ExposedFunctions/cppGenerator.h
)

target_include_directories(CPP_GENERATOR
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/ExposedFunctions
    PRIVATE
        ${CMAKE_CURENT_SOURCE_DIR}/ 

)






enable_testing()

include(FetchContent)

#Fetch fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        8.0.1
)
FetchContent_MakeAvailable(fmt)

# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)


# Force consistent runtime 
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")  # Dynamic debug runtime
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MDd")  # Dynamic debug runtime for C
    set_target_properties(gtest PROPERTIES COMPILE_OPTIONS "/MDd")
    set_target_properties(gtest_main PROPERTIES COMPILE_OPTIONS "/MDd")
endif()

add_executable(generator_testing Testing/GeneratorTesting.cpp)

target_compile_options(generator_testing PRIVATE /MDd)


target_link_libraries(generator_testing PRIVATE gtest gtest_main CPP_GENERATOR fmt::fmt)


add_test(NAME Generator_Testing COMMAND generator_testing)

gtest_discover_tests(generator_testing)

