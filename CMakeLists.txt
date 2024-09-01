cmake_minimum_required(VERSION 3.5)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(02.cpp11and14 CXX)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
configure_file(version.h.in version.h)

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(src_file ${SRC_FILES})
    get_filename_component(target ${src_file} NAME_WLE)
    add_executable(${target} ${src_file})
    list(APPEND TARGETS ${target})
    message("Target added: \"${target}\".")
endforeach(src_file ${SRC_FILES}) 

foreach(target ${TARGETS})
    target_compile_features(${target} PUBLIC cxx_std_14)
    set_target_properties(${target} PROPERTIES CXX_STANDARD_REQUIRED ON)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target}
            PRIVATE -g -Wall -Wextra -Werror -pedantic)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target}
            PRIVATE /W4)
    endif()
endforeach()


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# #enable_testing()

add_executable(
  test_ip_filter
  test_ip_filter.cc
)

target_link_libraries(
  test_ip_filter
  GTest::gtest_main
)

target_sources(test_ip_filter
    PRIVATE test_ip_filter.cc    
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.h
    PRIVATE ip_filter.cpp    
    )

# # for unit tests (disabled)
# set(INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv")
# set(EXECUTABLE "${CMAKE_CURRENT_BINARY_DIR}/test_ip_filter.exe")

# add_custom_command(
#     TARGET test_ip_filter
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E echo "Running ip_filter with input file"
#     COMMAND ${EXECUTABLE} < ${INPUT_FILE}
#     COMMENT "Running ip_filter with input file"
# )



install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)


#include(GoogleTest)
#gtest_discover_tests(test_ip_filter) 
#    DISCOVERY_MODE PRE_TEST
#    run_ip_filter)
# EXTRA_ARGS "cat ./ip_filter.tsv | ")
# gtest_add_tests(test_ip_filter "" AUTO)

