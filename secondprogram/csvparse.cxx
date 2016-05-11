// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csvparseConfig.h"
#ifdef USE_LIBCSV
  #include "csv.h"
#endif

int main(int argc, char* argv[]) {

  if(argc < 2) {
    fprintf(stdout, "%s Version %d.%d\n", argv[0], csvparse_VERSION_MAJOR, csvparse_VERSION_MINOR);
    fprintf(stdout, "Usage: %s number\n", argv[0]);
    return 1;
  }

  double inputValue = atof(argv[1]);

#ifdef USE_MYMATHS
  double outputValue = mysqrt(inputValue);
#else
  double outputValue = sqrt(inputValue);
#endif

  fprintf(stdout, "The square root of %g is %g\n", inputValue, outputValue);

  return 0;
}
