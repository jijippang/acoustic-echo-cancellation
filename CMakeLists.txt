
cmake_minimum_required(VERSION 3.14...3.30)
project(
    aec 
    VERSION 1.0.0 
    DESCRIPTION "Implements an Acoustic Echo Cancellation (AEC) algorithm" 
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)









# Fetch and configure GoogleTest (gtest)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 54915d462bb64e9b2bd1a3f0e70c00e6f5d817fb # v1.17.0 
)
FetchContent_MakeAvaliable(googletest)


# Fetch and configure AudioFile
FetchContent_Declare(
    AudioFile
    GIT_REPOSITORY https://github.com/adamstark/AudioFile.git
    GIT_TAG 4554279566c19602a14868b58551f23fe5c5fb53 # v1.1.4 
)
FetchContent_MakeAvaliable(AudioFile)
add_library(AudioFile::AudioFile INTERFACE IMPORTED)
target_include_directories(AudioFile::AudioFile INTERFACE ${audiofile_SOURCE_DIR})



# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)



