cmake_minimum_required(VERSION 3.16)
project(ncdc-weather)
set(ncdc-weather_VERSION_MAJOR 0)
set(ncdc-weather_VERSION_MINOR 1)
set(ncdc-weather_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CPP_STANDARD_COMPILE_FLAGS "-std=c++17")
set(OPTIMIZATION_FLAG_DEBUG "-O0")
set(OPTIMIZATION_FLAG_RELEASE "-Ofast")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAG_RELEASE}")
add_definitions(${CPP_STANDARD_COMPILE_FLAGS})

include_directories("include/")
add_executable(ncdc-weather src/main.cpp)
# To link extra libs, uncomment the following line and add "list(APPEND EXTRA_LIBS LIB_NAME_HERE)" before
# target_link_libraries(ncdc-weather ${EXTRA_LIBS})

install(TARGETS ncdc-weather DESTINATION bin)
