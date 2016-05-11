// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
#include "csvparseConfig.h"
#ifdef USE_LIBCSV
  #include "csv.h"
  #include "CSV.hpp"
#endif

using namespace std;

#ifdef USE_LIBCSV
int parse_with_libcsv(string filename) {
    jay::util::CSVread csv_read(filename,
        jay::util::CSVread::strict_mode
        | jay::util::CSVread::text_mode
        | jay::util::CSVread::process_empty_records
        //| jay::util::CSVread::skip_utf8_bom_check
    );
    if(csv_read.error) {
        cerr << "Reading CSV file failed: " << csv_read.error_msg << endl;
        return 1;
    }

    while(csv_read.ReadRecord()) {
        cout << endl << "Record #" << csv_read.record_num << endl;
        for(unsigned i = 0; i < csv_read.fields.size(); i++) {
            cout << "fields[ " << i << " ]: " << csv_read.fields[ i ] << "(" << csv_read.fields[ i ].length() << ")"<< endl;
        }
    }

    cout << endl;

    if(csv_read.eof && (csv_read.record_num == csv_read.end_record_num)) {
        cout << "All records read successfully. (" << csv_read.end_record_num << ")" << endl;
        if(csv_read.end_record_not_terminated) {
            cout << "WARNING: End record not terminated!" << endl;
        }
    } else if(csv_read.error) {
        cerr << "Error: " << csv_read.error_msg << endl;
    }

    cout << endl;

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


