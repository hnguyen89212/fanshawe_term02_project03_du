// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "Child.hpp"

// ----------------------------------------------
// CLASS IMPLEMENTATION
// ----------------------------------------------

Child::Child(bool b, string s, uintmax_t k, uintmax_t c, uintmax_t cluster_size) : is_directory(b), location(s), real_size_in_bytes(k), size_on_disk_in_clusters(c)
{
    size_on_disk_in_bytes = size_on_disk_in_clusters * cluster_size;
}

string Child::get_location()
{
    return location;
}

uintmax_t Child::get_real_size_in_bytes()
{
    return real_size_in_bytes;
}

uintmax_t Child::get_size_on_disk_in_bytes()
{
    return size_on_disk_in_bytes;
}

uintmax_t Child::get_size_on_disk_in_clusters()
{
    return size_on_disk_in_clusters;
}

void Child::print_information()
{
    cout << "location = " << location << endl;
    cout << "is a directory ? " << is_directory << endl;
    cout << "real size in bytes = " << real_size_in_bytes << endl;
    cout << "size on disk in bytes = " << size_on_disk_in_bytes << endl;
    cout << "size on disk in clusters = " << size_on_disk_in_clusters << endl
         << endl;
}