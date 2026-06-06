
cmake_minimum_required(VERSION 3.31...4.2)
project(
    aec 
    VERSION 0.1.0 
    DESCRIPTION "Implements an Acoustic Echo Cancellation (AEC) algorithm" 
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# For clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



message(
    "--------------- PROJECT DETAILS BEGIN ---------------\n"
    "Name: ${CMAKE_PROJECT_NAME}\n"
    "Version: ${CMAKE_PROJECT_VERSION}\n"
    "Description: ${CMAKE_PROJECT_DESCRIPTION}\n"
    "C++ Standard: ${CMAKE_CXX_STANDARD}\n"
    "--------------- PROJECT DETAILS END ---------------\n"
)





option(BUILD_DEBUG "Build the exectuable with debugging symbols" OFF)

# Set complier flags
if (BUILD_DEBUG)
    message("Building for debug")
    # add_compile_options(-Werror -Wall -Wextra -Wpedantic -O0 -g)
    add_compile_options(-Wall -Wextra -Wpedantic -O0 -g)
    set(CMAKE_BUILD_TYPE "Debug")
else ()
    message("Building for release")
    # add_compile_options(-Werror -Wall -Wextra -Wpedantic -O2)
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
    set(CMAKE_BUILD_TYPE "Release")
endif ()




include(FetchContent)

# Fetch and configure GoogleTest (gtest)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)
# Allows ctest to be used
enable_testing()


# Fetch and configure AudioFile
FetchContent_Declare(
    AudioFile
    GIT_REPOSITORY https://github.com/adamstark/AudioFile.git
    GIT_TAG 1.1.4
    GIT_SHALLOW TRUE
    SOURCE_SUBDIR "prevent_cmake_execution"
)
FetchContent_MakeAvailable(AudioFile)
add_library(AudioFile::AudioFile INTERFACE IMPORTED)
target_include_directories(AudioFile::AudioFile INTERFACE ${audiofile_SOURCE_DIR})


# Fetch and configure spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.17.0
    GIT_SHALLOW TRUE
    SOURCE_SUBDIR "prevent_cmake_execution"
)
FetchContent_MakeAvailable(spdlog)
add_library(spdlog::spdlog INTERFACE IMPORTED)
target_include_directories(spdlog::spdlog INTERFACE "${spdlog_SOURCE_DIR}/include")


# Fetch and configure Eigen
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 5.0.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(eigen)





# Add subdirectories
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)



