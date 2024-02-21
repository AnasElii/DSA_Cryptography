cmake_minimum_required(VERSION 3.21)
project(DSA VERSION 1.0.0 LANGUAGES CXX)

# ========= Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    # ========= Set Boost Libraries
    set(Boost_LIBRARY_DIR  $ENV{BOOST_LIB})
    set(Boost_INCLUDE_DIR $ENV{BOOST_INCLUDE})
elseif(APPLE)
    # ========= Set Boost Libraries
    set(Boost_LIBRARY_DIR  "/Users/aninoss/Documents/boost/testing/lib")
    set(Boost_INCLUDE_DIR "/Users/aninoss/Documents/boost")
endif()

# ========= Set directories
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# ========= Include directories
include_directories(${SOURCE_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

# ========= Add directories files
file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
    "${INCLUDE_DIR}/*.h"
)

# ========= Include libraries
    find_package(Boost COMPONENTS random filesystem system REQUIRED)

# ========= Add executable
add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCES}
)

# ========= Cnfigure macOS package
if(APPLE)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
endif()

# ========= Link target subDirectories
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC src)
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC include)
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Boost_LIBRARY_DIR})

# ========= Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    Boost::random   
    Boost::filesystem
    Boost::system
)

 