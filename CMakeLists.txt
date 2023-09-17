cmake_minimum_required(VERSION 3.26)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(hello_cpp VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(hello_cpp main.cpp)
add_library(hello lib.cpp)
add_executable(test_boost_version test_boost_version.cpp)
add_executable(test_gtest_version test_gtest_version.cpp)

target_include_directories(hello_cpp PRIVATE ${CMAKE_BINARY_DIR})

set_target_properties(test_boost_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(hello_cpp hello)
target_link_libraries(test_boost_version ${Boost_LIBRARIES} hello)
target_link_libraries(test_gtest_version GTest::gtest_main hello)

if (MSVC)
    target_compile_options(hello_cpp PRIVATE /W4)
    target_compile_options(hello PRIVATE /W4)
    target_compile_options(test_boost_version PRIVATE /W4)
    target_compile_options(test_gtest_version PRIVATE /W4)
else ()
    target_compile_options(hello_cpp PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(hello PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_boost_version PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_gtest_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()

install(TARGETS hello_cpp RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT example@test.com)
include(CPack)

enable_testing()
add_test(test_boost_version test_boost_version)

include(GoogleTest)
gtest_discover_tests(test_gtest_version)