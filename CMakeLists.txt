cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION 0.0.1)
endif()
project(HW2 VERSION ${VERSION})
set(Boost_DEBUG ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(HW2_cli main.cpp)
add_library(HW2 lib.cpp)
add_library(HW2_filter address.cpp filters.h)
add_executable(unit_test test.cpp)

set_target_properties(HW2_cli HW2 HW2_filter unit_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(HW2
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(HW2_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

set_target_properties(unit_test PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(HW2_cli PRIVATE ${Boost_LIBRARIES}
    HW2 HW2_filter
)

target_link_libraries(unit_test
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    HW2 HW2_filter
)

if (MSVC)
    target_compile_options(HW2_cli PRIVATE
        /W4
    )
target_compile_options(HW2 PRIVATE
    /W4
)
target_compile_options(HW2_filter PRIVATE
    /W4
)
    target_compile_options(unit_test PRIVATE
        /W4
    )
else ()
    target_compile_options(HW2_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
target_compile_options(HW2 PRIVATE
    -Wall -Wextra -pedantic -Werror
)
target_compile_options(HW2_filter PRIVATE
    -Wall -Wextra -pedantic -Werror
)
    target_compile_options(unit_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS HW2_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(unit_test unit_test)
