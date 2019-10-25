#pragma once

// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "Data_Collector.hpp"

// ----------------------------------------------
// FUNCTION PROTOTYPES
// ----------------------------------------------

// primary function
// prints complete report
void print_report(CLI_Input in, Data_Collector collector);

/**
 * deals with circumstances where -s is present.
 */
void print_report_root(CLI_Input in, Data_Collector collector);

/**
 * deals with situations where -n is present.
 * step 1: create 2 vectors/columns "names", "sizes", populate them.
 * step 2: *take advantage of "map" to sort the columns (key is name, values is size)
 *         *clear the vectors, then copy the content from map back to them
 * step 3: reverse if necessary
 * step 4: print the report containing 2 columns/vectors.
 */ 
void print_report_name(CLI_Input in, Data_Collector collector);

// deals with situations where -z is present. Same idea as above.
void print_report_size(CLI_Input in, Data_Collector collector);

// deals with situations where none of {-s, -n, -z} is present
void print_report_absent(CLI_Input in, Data_Collector collector);

// a report has 2 columns ("sizes" and "names" in strings)
// stores relevant information of 2 columns.
void populate_report(CLI_Input in, Data_Collector collector, vector<string> &names, vector<string> &sizes);

// literally prints the report to console
void print_report(CLI_Input in, Data_Collector collector, vector<string> const& names, vector<string> const& sizes);

// reverses 2 columns if -r is set
void reverse_if_needed(CLI_Input in, vector<string>& names, vector<string>& sizes);
