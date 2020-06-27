cmake_minimum_required(VERSION 3.16)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 20)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.72.0_3)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.72.0_3/lib)
find_package(Boost 1.72.0 COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()
add_executable(OOP_Project main.cpp MyAllocator.hpp MyMemoryPool.hpp SimpleAllocator.hpp MyStack.hpp)
if(Boost_FOUND)

    target_link_libraries(OOP_Project ${Boost_LIBRARIES})

endif()
