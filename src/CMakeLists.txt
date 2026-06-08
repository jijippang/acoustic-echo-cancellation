
# Make a static library for the executable and the unit tests
add_library(aec_lib STATIC)


set(HEADERS_DIR ${aec_SOURCE_DIR}/include/acoustic-echo-cancellation)
target_sources(aec_lib
    PRIVATE
        aec.cpp
        nlms.cpp
    PUBLIC 
        FILE_SET HEADERS
        BASE_DIRS ${HEADERS_DIR}
        FILES
            ${HEADERS_DIR}/aec.hpp
            ${HEADERS_DIR}/nlms.hpp
            ${HEADERS_DIR}/sliding_window.hpp
)

target_link_libraries(aec_lib PUBLIC AudioFile::AudioFile spdlog::spdlog Eigen3::Eigen)


