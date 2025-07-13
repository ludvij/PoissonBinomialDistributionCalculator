cmake_minimum_required(VERSION 3.31)

project(PoissonBinomialDistribution)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)



set(SOURCES
	src/main.cpp
	src/PoissonBinomialDistribution.cpp

	include/PoissonBinomialDistribution.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
	PUBLIC ludutils
)

target_include_directories(${PROJECT_NAME}
	PUBLIC src
	PUBLIC include
)