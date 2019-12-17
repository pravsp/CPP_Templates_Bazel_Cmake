# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)


#############################
# Add My Template Library
#############################

# Project's name

project(my_template_lib)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB TEMPLATE_LIB_SOURCES "template_lib/src/*.cc")
include_directories(${CMAKE_SOURCE_DIR}/template_lib/include)
add_library(my_templ STATIC
            ${TEMPLATE_LIB_SOURCES})
set_property(TARGET my_templ PROPERTY CXX_STANDARD 17)
install(TARGETS my_templ DESTINATION ../lib)
##################################
# Download and install GoogleTest
##################################
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

################
# Define a test
file(GLOB TEMPLATE_TEST_SOURCES "template_lib/test/*.cc")

include_directories(${PROJECT_SOURCE_DIR}/template_lib/include)
add_executable(template_test ${TEMPLATE_TEST_SOURCES})
target_link_libraries(template_test gtest_main)
set_property(TARGET template_test PROPERTY CXX_STANDARD 17)
######################################

######################################
# Configure the test to use GoogleTest
#
# If used often, could be made a macro.

# add_dependencies(template_test gtest)
# include_directories(${source_dir}/include)
# target_link_libraries(template_test ${binary_dir}/libgtest.a)
# target_link_libraries(template_test ${binary_dir}/libgtest_main.a)
target_link_libraries(template_test ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libmy_templ.a)

##################################
# Just make the test runnable with
#   $ make test

enable_testing()
add_test(NAME    template_test 
         COMMAND template_test)

