

add_executable(tests)



target_sources(tests
    PRIVATE
        unit/aec_test.cpp
)


target_link_libraries(tests 
    PRIVATE
        GTest::gtest_main
        aec_lib
)


include(GoogleTest)
gtest_discover_tests(tests)

