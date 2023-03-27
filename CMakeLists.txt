cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(PROJECT_NAME async)

project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})



add_library(${PROJECT_NAME} src/cmd.cpp src/outputCMD.cpp src/async.cpp src/loggerManager.cpp )

target_include_directories(${PROJECT_NAME} PUBLIC include)

set(HasLib OFF)

if(HasLib)
    add_library(async src/cmd.cpp src/outputCMD.cpp src/async.cpp src/loggerManager.cpp )  


    target_include_directories(async
        PRIVATE "${CMAKE_BINARY_DIR}"
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE async)

    target_include_directories(async PUBLIC include)

    target_compile_features(async PUBLIC cxx_std_17)

    set_target_properties(async PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
    )
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#set(WITH_TESTS ON)

if(WITH_TESTS)
    add_executable(test src/main.cpp)
    target_compile_features(test PUBLIC cxx_std_17)
    target_link_libraries(test ${PROJECT_NAME})

endif()

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(asyncPRIVATE
        /W4
    )
    if(WITH_TESTS)
        target_compile_options(${PROJECT_NAME}_test PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(HasLib)
        target_compile_options(async PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
    if(WITH_TESTS)
        target_compile_options(test PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/local/lib)

if (APPLE)
    message("Packing for MacOS")
    set(CPACK_GENERATOR DragNDrop)
elseif (UNIX)
    message("Packing for Debian distros")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_PACKAGE_NAME "async")
    set(CPACK_PACKAGE_CONTACT evgeniy@btnt51.ru)
endif ()


set(CPACK_OUTPUT_FILE_PREFIX release)
include(CPack)