cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(CMAKE_CXX_STANDARD 17)

project(bayan VERSION ${PROJECT_VESRION})


add_executable(${PROJECT_NAME} src/main.cpp)

set(HasLib ON)

if(HasLib)
    add_library(${PROJECT_NAME}_lib src/File.cpp src/Filter.cpp 
    src/Mask.cpp src/Scanner.cpp src/options.cpp)  


    target_include_directories(${PROJECT_NAME}_lib
        PRIVATE "./include"
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

target_include_directories(${PROJECT_NAME}
        PRIVATE "./include"
)


set(WITH_BOOST ON)

if(WITH_BOOST)
    set(Boost_USE_STATIC_LIBS   ON)
    if(NOT GITHUBACTIONS)
        find_package(Boost COMPONENTS program_options REQUIRED)   
    endif()

    if(HasLib)
        target_include_directories(${PROJECT_NAME}_lib PRIVATE ${Boost_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME}_lib PRIVATE ${Boost_LIBRARIES})
    endif()

    target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_directories(${PROJECT_NAME} PRIVATE ${Boost_LIBRARY_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

endif()


target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#set(WITH_TESTS OFF)

if(WITH_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    
    add_executable(test tests/compareTest.cpp tests/filterTest.cpp tests/scannerTest.cpp)
    target_compile_features(test PUBLIC cxx_std_17)
    If(WITH_BOOST)
        target_include_directories(test PRIVATE ${Boost_INCLUDE_DIRS})
        target_link_libraries(test ${Boost_LIBRARIES})
    endif()
    if(HasLib)
        target_link_libraries(test GTest::gtest_main ${PROJECT_NAME}_lib)
    else()
        target_link_libraries(test GTest::gtest_main)
    endif()
    target_include_directories(test PRIVATE include)

    include(GoogleTest)
    gtest_discover_tests(test)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

endif()

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(${PROJECT_NAME}_lib PRIVATE
        /W4
    )
    if(BUILDING_TESTS)
        target_compile_options(test PRIVATE
            /W4
        )
    endif()
else()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
        if(HasLib)
            target_compile_options(${PROJECT_NAME}_lib PRIVATE
                -Wall -Wextra -pedantic -Werror
            )
        endif()
        if(BUILDING_TESTS)
            target_compile_options(test PRIVATE
                -Wall -Wextra -pedantic -Werror
            )
        endif()
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
        if(HasLib)
            target_compile_options(${PROJECT_NAME}_lib PRIVATE
                -Wall -Wextra -pedantic -Werror
            )
        endif()
        if(BUILDING_TESTS)
            target_compile_options(test PRIVATE
                -Wall -Wextra -pedantic -Werror
            )
        endif()
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