###############################################
###              BaSyx C++ Components       ###
###############################################
cmake_minimum_required(VERSION 3.13.0)

set(PROJECT_NAME "BaSyx C++ Components")
set(PROJECT_SHORTNAME "BaSyx Components")

project(${PROJECT_NAME} VERSION "1.0")

### CMake settings ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(build_source_group)
include(diagnostics_print)
include(enable_clang_format)
include(enable_clang_tidy)
include(enable_cppcheck)
include(FetchContent)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### Project settings ###
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "" )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

### BaSyx directories ###
set(BASYX_COMP_SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BASYX_COMP_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(BASYX_COMP_TEST_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/tests")

### Build options ###
set(BASYX_COMP_BUILD_TESTS ${BASYX_BUILD_TESTS_DEFAULT} CACHE BOOL "Build unit tests")
option(BASYX_COMP_VERBOSE_CMAKE_OUTPUT "Show detailed CMake output" ON)

### Compiler settings ###
set(CMAKE_CXX_STANDARD 17)

###############################################
###           Library Settings              ###
###############################################

### Detect OS threading library ###
find_package(Threads)

if(BASYX_SDK_DIR)
    add_subdirectory("${BASYX_SDK_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/build_basyx_sdk" EXCLUDE_FROM_ALL)
else()
    ### BaSyx C++ SDK ###
    FetchContent_Declare(
	    basyx_cpp_sdk
	    GIT_REPOSITORY https://github.com/IESE-T3/basyx-cpp-sdk
	    GIT_TAG development_v2
    )

    FetchContent_GetProperties(basyx_cpp_sdk)
    if(NOT basyx_cpp_sdk_POPULATED)
	    FetchContent_Populate(basyx_cpp_sdk)
	    add_subdirectory(${basyx_cpp_sdk_SOURCE_DIR} ${basyx_cpp_sdk_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()
endif()
   
### spdlog ###
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.x
)

FetchContent_MakeAvailable(spdlog)
   
### GoogleTest ###
if(${BASYX_COMP_BUILD_TESTS})
    include(GoogleTest)

    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

###############################################
###           Library Directory             ###
###############################################

###############################################
###           Source Directory              ###
###############################################

add_subdirectory(src/api)
add_subdirectory(src/http)

###############################################
###           Test Directory                ###
###############################################

if(${BASYX_COMP_BUILD_TESTS})
    include( CTest )
    add_subdirectory(tests/api_unit_tests)
    add_subdirectory(tests/basyxpp-http-tests)
endif()

###############################################
###           Utility Projects              ###
###############################################

if(${BASYX_UTILITY_PROJECTS})
    enable_clang_format()
    enable_clang_tidy()
    enable_cppcheck()
endif()
