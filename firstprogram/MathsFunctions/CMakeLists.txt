add_library(MathsFunctions mysqrt.cxx)

install(TARGETS MathsFunctions DESTINATION bin)
install(FILES MathsFunctions.h DESTINATION include) 
