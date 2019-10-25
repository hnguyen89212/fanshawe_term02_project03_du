// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "Data_Collector.hpp"

// ----------------------------------------------
// CLASS IMPLEMENTATION
// ----------------------------------------------

// constructor
Data_Collector::Data_Collector(CLI_Input in)
{
    if (in.get_folder() == "")
        mode = Current_Working_Directory;
    // local, temporary variables
    uintmax_t cluster_size = in.get_cluster_size();
    vector<string> path_to_subfolders;
    vector<string> path_to_subfiles;
    string base = in.get_path().string();
    map<string, uintmax_t> store;

    /**
     * rscan algorithm (modified)
     * Credit: Professor Jannice Manning
     */
    path p = in.get_path();
    recursive_directory_iterator dir(p);
    recursive_directory_iterator end;
    while (dir != end)
    {
        string key = dir->path().string();
        if (is_directory(dir->status()))
        {
            if (qualifies_as_direct_child(base, key))
                path_to_subfolders.push_back(key);
        }
        else if (is_regular_file(dir->status()))
        {
            if (qualifies_as_direct_child(base, key))
                path_to_subfiles.push_back(key);
            uintmax_t value = file_size(dir->path());
            store.insert(pair<string, uintmax_t>(key, value));
        }
        ++dir;
    }
    // traverse the subfolders
    // build/populate the "children_folders"
    for (size_t i = 0; i < path_to_subfolders.size(); i++)
    {
        string currentpath = path_to_subfolders[i];
        uintmax_t bytes = 0;
        uintmax_t clusters = 0;
        map<string, uintmax_t>::const_iterator citr = store.cbegin();
        while (citr != store.cend())
        {
            if (citr->first.find(currentpath, 0) != string::npos)
            {
                bytes += citr->second;
                clusters += to_size_on_disk_in_clusters(citr->second, cluster_size);
            }
            ++citr;
        }
        Child infant(true, currentpath, bytes, clusters, cluster_size);
        children_folders.push_back(infant);
        // for the root
        total_size_on_disk_in_clusters += infant.get_size_on_disk_in_clusters();
        total_real_size_in_bytes += infant.get_real_size_in_bytes();
    }
    // traverse the subfiles
    // build/populate the "children_files"
    for (size_t i = 0; i < path_to_subfiles.size(); i++)
    {
        string currentpath = path_to_subfiles[i];
        uintmax_t bytes = 0;
        uintmax_t clusters = 0;
        map<string, uintmax_t>::const_iterator citr = store.cbegin();
        while (citr != store.cend())
        {
            if (citr->first.find(currentpath, 0) != string::npos)
            {
                bytes += citr->second;
                clusters += to_size_on_disk_in_clusters(citr->second, cluster_size);
            }
            ++citr;
        }
        // create Child instance, store it
        Child infant(false, currentpath, bytes, clusters, cluster_size);
        children_files.push_back(infant);
        // for the root
        total_size_on_disk_in_clusters += infant.get_size_on_disk_in_clusters();
        total_real_size_in_bytes += infant.get_real_size_in_bytes();
    }
    // derive the total clusters
    total_size_on_disk_in_bytes = total_size_on_disk_in_clusters * cluster_size;
}

Mode Data_Collector::get_mode()
{
    return mode;
}

vector<Child> Data_Collector::get_children_folders()
{
    return children_folders;
}

uintmax_t Data_Collector::get_total_real_size_in_bytes()
{
    return total_real_size_in_bytes;
}

uintmax_t Data_Collector::get_total_size_on_disk_in_bytes()
{
    return total_size_on_disk_in_bytes;
}

uintmax_t Data_Collector::get_total_size_on_disk_in_clusters()
{
    return total_size_on_disk_in_clusters;
}

void Data_Collector::print_information()
{
    cout << "====================================\n";
    cout << "subfolders in root:\n";
    for (auto each : children_folders)
        each.print_information();
    cout << "====================================\n";
    cout << "subfiles in root:\n";
    for (auto each : children_files)
        each.print_information();
    cout << "====================================\n";
    cout << "total real size in bytes of root = " << total_real_size_in_bytes << endl;
    cout << "total size on disk in bytes of root = " << total_size_on_disk_in_bytes << endl;
    cout << "total size on disk in clusters of root = " << total_size_on_disk_in_clusters << endl;
}