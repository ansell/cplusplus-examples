# first we add the executable that generates the table
# add the binary tree directory to the search path for include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(MakeTable MakeTable.cxx)
# add the command teo generate the source code for Table.h
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
)

# add the main library
add_library(MathsFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

install(TARGETS MathsFunctions DESTINATION bin)
install(FILES MathsFunctions.h DESTINATION include) 
