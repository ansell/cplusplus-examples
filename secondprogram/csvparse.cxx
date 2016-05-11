// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <atomic>
#include <math.h>
#include "csvparseConfig.h"
#ifdef USE_LIBCSV
  #include "csv.h"
  #include "CSV.hpp"
#endif

#ifdef USE_LIBCSV
int parse_with_libcsv(std::string filename) {
    jay::util::CSVread csv_read(filename,
        jay::util::CSVread::strict_mode
        | jay::util::CSVread::text_mode
        | jay::util::CSVread::process_empty_records
        //| jay::util::CSVread::skip_utf8_bom_check
    );
    if(csv_read.error) {
        std::cerr << "Reading CSV file failed: " << csv_read.error_msg << std::endl;
        return 1;
    }
    
    std::atomic_int count(0); 
    while(csv_read.ReadRecord()) {
        count++;
#ifndef NDEBUG
        std::cout << std::endl << "Record #" << csv_read.record_num << std::endl;
        for(unsigned i = 0; i < csv_read.fields.size(); i++) {
            std::cout << "fields[ " << i << " ]: " << csv_read.fields[ i ] << "(" << csv_read.fields[ i ].length() << ")"<< std::endl;
        }
#endif
    }

    std::cout << "Read " << count << " records" << std::endl;

    std::cout << std::endl;

    if(csv_read.eof && (csv_read.record_num == csv_read.end_record_num)) {
        std::cout << "All records read successfully. (" << csv_read.end_record_num << ")" << std::endl;
        if(csv_read.end_record_not_terminated) {
            std::cout << "WARNING: End record not terminated!" << std::endl;
        }
    } else if(csv_read.error) {
        std::cerr << "Error: " << csv_read.error_msg << std::endl;
    }

    std::cout << std::endl;

    return 0;
}
#endif

int main(int argc, char* argv[]) {

  if(argc < 2) {
    fprintf(stdout, "%s Version %d.%d\n", argv[0], csvparse_VERSION_MAJOR, csvparse_VERSION_MINOR);
    fprintf(stdout, "Usage: %s csvfile\n", argv[0]);
    return 1;
  }

#ifdef USE_LIBCSV
  return parse_with_libcsv(argv[1]);
#else
  fprintf(stdout, "No csvparser implementation selected.");
  return 2;
#endif
}


