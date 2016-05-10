cmake_minimum_required (VERSION 2.6)

SET(CMAKE_INSTALL_PREFIX "./target")

project (Tutorial)

# Set the version number
set(Tutorial_VERSION_MAJOR 0)
set(Tutorial_VERSION_MINOR 1)


# does this system provide the log and exp functions
include(CheckFunctionExists)
#include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
#set(CMAKE_REQUIRED_INCLUDES math.h)
#set(CMAKE_REQUIRED_LIBRARIES m)
# TODO: The following are not working for me currently
check_function_exists(sqrt HAVE_SQRT)
check_function_exists(log HAVE_LOG)
check_function_exists(exp HAVE_EXP)

# should we use our own maths functions?
option(USE_MYMATHS "Use tutorial provided maths implementation" ON)

# configure a header file to pass some of the CMake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# add the MathsFunctions library?
if(USE_MYMATHS)
  include_directories("${PROJECT_SOURCE_DIR}/MathsFunctions")
  add_subdirectory(MathsFunctions)
  set(EXTRA_LIBS ${EXTRA_LIBS} MathsFunctions)  
endif(USE_MYMATHS)

# add executables/libraries
add_executable(Tutorial tutorial.cxx)
target_link_libraries(Tutorial ${EXTRA_LIBS})

# add the install targets
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# Do some testing

#include(CTest)
enable_testing()

#define a macro to simplify adding tests, then use it
macro (do_test arg result)
  add_test ("TutorialCompute'${arg}'" Tutorial ${arg})
  set_tests_properties ("TutorialCompute'${arg}'"
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# does the application run
add_test(TutorialRuns Tutorial 25)

# does the usage message work?
do_test("" "Usage:.*number")
#add_test(TutorialUsage Tutorial)
#set_tests_properties(TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# does the application compute square root of 25 correctly
do_test("25" "25 is 5")
#add_test(TutorialComp25 Tutorial 25)
#set_tests_properties(TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# does the application handle negative numbers
do_test("-1" "-1 is 0")
#add_test(TutorialNegative Tutorial -1)
#set_tests_properties(TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-1 is 0")

# does the application handle small numbers
do_test("0.0001" "0.0001 is 0.01")
#add_test(TutorialSmall Tutorial 0.0001)
#set_tests_properties(TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")



