cmake_minimum_required (VERSION 2.6)

SET(CMAKE_INSTALL_PREFIX "./target")

project (csvparse)

# Set the version number
set(csvparse_VERSION_MAJOR 0)
set(csvparse_VERSION_MINOR 1)

# use c++11
add_definitions("-std=c++11")

# does this system provide the log and exp functions
#include(CheckFunctionExists)
#include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
#set(CMAKE_REQUIRED_INCLUDES math.h)
#set(CMAKE_REQUIRED_LIBRARIES m)
# TODO: The following are not working for me currently
#check_function_exists(sqrt HAVE_SQRT)
#check_function_exists(log HAVE_LOG)
#check_function_exists(exp HAVE_EXP)

# should we use the libcsv included implementation?
# NOTE: Currently no alternative, so trivial at this point
option(USE_LIBCSV "Use provided libcsv implementation" ON)

# configure a header file to pass some of the CMake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/csvparseConfig.h.in"
  "${PROJECT_BINARY_DIR}/csvparseConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find csvparseConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# add the MathsFunctions library?
if(USE_LIBCSV)
  include_directories("${PROJECT_SOURCE_DIR}/CSVFunctions")
  add_subdirectory(CSVFunctions)
  set(EXTRA_LIBS ${EXTRA_LIBS} CSVFunctions)  
endif(USE_LIBCSV)

# add executables/libraries
add_executable(csvparse csvparse.cxx)
target_link_libraries(csvparse ${EXTRA_LIBS})

# add the install targets
install(TARGETS csvparse DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/csvparseConfig.h" DESTINATION include)

# Do some testing

#include(CTest)
enable_testing()

#define a macro to simplify adding tests, then use it
macro (do_test arg result)
  add_test ("csvparseParseTest'${arg}'" csvparse ${arg})
  set_tests_properties ("csvparseParseTest'${arg}'"
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# does the application run
#add_test(TutorialRuns Tutorial 25)

# does the usage message work?
do_test("" "Usage:.*")
#add_test(TutorialUsage Tutorial)
#set_tests_properties(TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# does the application compute square root of 25 correctly
#do_test("25" "25 is 5")
#add_test(TutorialComp25 Tutorial 25)
#set_tests_properties(TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# does the application handle negative numbers
#do_test("-1" "-1 is 0")
#add_test(TutorialNegative Tutorial -1)
#set_tests_properties(TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-1 is 0")

# does the application handle small numbers
#do_test("0.0001" "0.0001 is 0.01")
#add_test(TutorialSmall Tutorial 0.0001)
#set_tests_properties(TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${csvparse_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${csvparse_VERSION_MINOR}")
include (CPack)

