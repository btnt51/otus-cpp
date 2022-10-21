cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})


project(ipfilter_lib VERSION ${PROJECT_VESRION})


add_executable(ip_filter src/main.cpp)

add_library(ipfilter_lib src/ipfilter.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ip_filter.tsv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



target_include_directories(ipfilter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ipfilter_lib
)

target_compile_features(ipfilter_lib PUBLIC cxx_std_17)
target_compile_features(ip_filter PUBLIC cxx_std_17)

set_target_properties(ipfilter_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)

if(BUILDING_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data_tests
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    
    add_executable(${PROJECT_NAME}_test  tests/split.cpp tests/ipAddress.cpp tests/sort.cpp  tests/filters.cpp)
    target_compile_features(${PROJECT_NAME}_test PUBLIC cxx_std_17)
    target_link_libraries(${PROJECT_NAME}_test GTest::gtest_main ${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME}_test PRIVATE include)

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_test)
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ipfilter_lib PRIVATE
        /W4
    )
    if(BUILDING_TESTS)
        target_compile_options(${PROJECT_NAME}_test PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ipfilter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(BUILDING_TESTS)
        target_compile_options(${PROJECT_NAME}_test PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

if (APPLE)
    message("Packing for MacOS")
    set(CPACK_GENERATOR DragNDrop)
elseif (UNIX)
    message("Packing for Debian distros")
    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_CONTACT evgeniy@btnt51.ru)
endif ()
set(CPACK_OUTPUT_FILE_PREFIX release)
include(CPack)
