#pragma once

// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "CLI_Input.hpp"

// ----------------------------------------------
// CLASS DECLARATION
// ----------------------------------------------

// A class to represent a folder/file.
class Child
{
private:
    // holds "true" if it is a directory/folder
    bool is_directory;
    // absolute path to the object (in string)
    string location;
    // real size of object in bytes
    uintmax_t real_size_in_bytes;
    // potentially higher space to store object on disk (in bytes)
    uintmax_t size_on_disk_in_bytes;
    // number of clusters assigned to store object
    uintmax_t size_on_disk_in_clusters;

public:
    Child(bool b, string s, uintmax_t k, uintmax_t c, uintmax_t cluster_size);

    /**
     * group of getters
     */ 

    string get_location();
    uintmax_t get_real_size_in_bytes();
    uintmax_t get_size_on_disk_in_bytes();
    uintmax_t get_size_on_disk_in_clusters();
    void print_information();
};