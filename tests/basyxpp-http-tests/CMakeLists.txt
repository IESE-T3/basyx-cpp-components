###############################################
###              tests_misc                 ###
###############################################

cmake_minimum_required(VERSION 3.1.0)

project(tests_http_misc)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} 
	BaSyx::http
	BaSyx::util
	spdlog::spdlog
	gtest_main
)

gtest_discover_tests(${PROJECT_NAME})
