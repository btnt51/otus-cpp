cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})


project(allocator VERSION ${PROJECT_VESRION})

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(HasLib ON)

if(HasLib)
    add_library(${PROJECT_NAME}_lib src/fact.cpp)  


    target_include_directories(${PROJECT_NAME}_lib
        PRIVATE "${CMAKE_BINARY_DIR}"
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${PROJECT_NAME}_lib
    )

    target_compile_features(${PROJECT_NAME}_lib PUBLIC cxx_std_17)
    set_target_properties(${PROJECT_NAME}_lib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
    )
endif()

if(WITH_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    
    add_executable(test  tests/allocator_test.cpp tests/own_list_test.cpp)
    target_compile_features(test PUBLIC cxx_std_17)
    target_link_libraries(test GTest::gtest_main ${PROJECT_NAME}_lib)
    target_include_directories(test PRIVATE include)

    include(GoogleTest)
    gtest_discover_tests(test)
endif()

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    if(HasLib)
        target_compile_options(${PROJECT_NAME}_lib PRIVATE
            /W4
        )
    endif()
    if(BUILDING_TESTS)
        target_compile_options(${PROJECT_NAME}_test PRIVATE
            /W4
        )
    endif()
else ()
    #target_compile_options(${PROJECT_NAME} PRIVATE
    #    -Wall -Wextra -pedantic -Werror
    #)
    if(HasLib)
        target_compile_options(${PROJECT_NAME}_lib PRIVATE
           -Wall -Wextra -pedantic -Werror
        )
    endif()
    if(BUILDING_TESTS)
        target_compile_options(${PROJECT_NAME}_test PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

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