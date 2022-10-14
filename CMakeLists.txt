cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

option(WITH_GOOGLE_TEST "Whether to build Google test" ON)

project(ipfilter_lib VERSION ${PROJECT_VESRION})


add_executable(ipfilter main.cpp)

add_library(ipfilter_lib ipfilter.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ip_filter.tsv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/sort.tsv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/sorted.tsv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/filter_1.tsv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/filter_46_70.tsv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/filter_any_46.tsv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

target_include_directories(ipfilter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ipfilter PRIVATE
    ipfilter_lib
)

target_compile_features(ipfilter_lib PUBLIC cxx_std_17)
target_compile_features(ipfilter PUBLIC cxx_std_17)

set_target_properties(ipfilter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)

if(WITH_GOOGLE_TEST)
    add_executable(google_tests tests.cpp)
    add_subdirectory(googletest)
    set_target_properties(google_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
    
    target_link_libraries(google_tests gtest_main ipfilter_lib)

endif()

if (MSVC)
    target_compile_options(ipfilter PRIVATE
        /W4
    )
    target_compile_options(ipfilter_lib PRIVATE
        /W4
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_tests PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ipfilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ipfilter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_tests PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ipfilter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT evgeniy@btnt51.ru)
include(CPack)

if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(google_tests google_tests)
endif()