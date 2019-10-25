#pragma once

// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "Child.hpp"

// ----------------------------------------------
// CLASS DECLARATION
// ----------------------------------------------

// A class to scan and store information about the interested directory
class Data_Collector
{
private:
    // mode of program, absolute path or cwd
    Mode mode = Absolute_Directory;
    // vector of subfolders in root
    vector<Child> children_folders;
    // vector of files in root
    vector<Child> children_files;
    // the real size of root in bytes
    uintmax_t total_real_size_in_bytes;
    // size on disk of root in bytes
    uintmax_t total_size_on_disk_in_bytes;
    // total number of clusters assigned for root
    uintmax_t total_size_on_disk_in_clusters;

public:
    // constructor
    Data_Collector(CLI_Input in);

    /**
     * group of getters
     */ 

    Mode get_mode();
    vector<Child> get_children_folders();
    uintmax_t get_total_real_size_in_bytes();
    uintmax_t get_total_size_on_disk_in_bytes();
    uintmax_t get_total_size_on_disk_in_clusters();
    void print_information();
};