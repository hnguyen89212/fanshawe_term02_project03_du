#pragma once

// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "Tools.hpp"

// ----------------------------------------------
// CLASS DECLARATION
// ----------------------------------------------

// A class to obtain information on command line inputs
class CLI_Input
{
private:
    // stores "true" if inputs are valid; "false" otherwise
    // initially, it is "true"
    bool valid = true;
    // cluster size sepcified by user
    uintmax_t cluster_size = default_cluster_size_in_bytes;
    // collection of all switches/flags
    vector<string> switches;
    // if absolute folder is set in CLI, "folder" is same as "destination"
    // otherwise, it is empty string
    string folder;
    // path to the destination (either an absolute path or CWD)
    path destination;

public:
    // constructor
    CLI_Input(int argc, char *argv[]);

    /**
     * group of getters
     */ 

    bool is_valid();
    uintmax_t get_cluster_size();
    vector<string> get_switches();
    string get_folder();
    path get_path();

    // prints everything about the CLI input
    void print_information();
};