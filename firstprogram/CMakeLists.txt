cmake_minimum_required (VERSION 2.6)

SET(CMAKE_INSTALL_PREFIX "./target")

project (Tutorial)

# Set the version number
set(Tutorial_VERSION_MAJOR 0)
set(Tutorial_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# should we use our own maths functions?
option(USE_MYMATHS "Use tutorial provided maths implementation" ON)

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

include(CTest)

# does the usage message work?
add_test(TutorialUsage Tutorial)
set_tests_properties(TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# does the application run
add_test(TutorialRuns Tutorial 25)

# does the application compute square root of 25 correctly
add_test(TutorialComp25 Tutorial 25)
set_tests_properties(TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# does the application handle negative numbers
add_test(TutorialNegative Tutorial -1)
set_tests_properties(TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-1 is 0")

# does the application handle small numbers
add_test(TutorialSmall Tutorial 0.0001)
set_tests_properties(TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")



