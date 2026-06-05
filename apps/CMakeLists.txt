
add_executable(aec)


target_sources(aec
    PRIVATE
        main.cpp
)


target_link_libraries(aec PRIVATE aec_lib)


