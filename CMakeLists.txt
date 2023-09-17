cmake_minimum_required(VERSION 3.26)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(hello_cpp VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(version.h.in version.h)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(hello_cpp main.cpp)
add_library(hello lib.cpp)
add_executable(test_version test_version.cpp)

target_include_directories(hello_cpp PRIVATE ${CMAKE_BINARY_DIR})

set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(hello_cpp hello)

target_link_libraries(test_version ${Boost_LIBRARIES} hello)

if (MSVC)
    target_compile_options(hello_cpp PRIVATE /W4)
    target_compile_options(hello PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(hello_cpp PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(hello PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()

install(TARGETS hello_cpp RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_CONTACT test@test.com)
include(CPack)

enable_testing()
add_test(test_version test_version)