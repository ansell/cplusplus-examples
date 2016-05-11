# first we add the executable that generates the table
# add the binary tree directory to the search path for include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#add_executable(MakeTable MakeTable.cxx)
# add the command teo generate the source code for Table.h
#add_custom_command (
#  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
#  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
#  DEPENDS MakeTable
#)

# add the main library
add_library(CSVFunctions csv.h libcsv.c CSV.hpp CSVread.cpp CSVwrite.cpp strerror.hpp strerror.cpp)

install(TARGETS CSVFunctions DESTINATION bin)
install(FILES csv.h CSV.hpp DESTINATION include) 
