// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "Report.hpp"

// ----------------------------------------------
// FUNCTION IMPLEMENTATION
// ----------------------------------------------

void print_report(CLI_Input in, Data_Collector collector)
{
    vector<string> switches = in.get_switches();
    if (has_particular_flag(switches, sFlag))
        print_report_root(in, collector);
    else if (has_particular_flag(switches, nFlag))
        print_report_name(in, collector);
    else if (has_particular_flag(switches, zFlag))
        print_report_size(in, collector);
    else
        print_report_absent(in, collector);
}

void print_report_root(CLI_Input in, Data_Collector collector)
{
    vector<string> switches = in.get_switches();
    string folder = in.get_folder();
    if (has_particular_flag(switches, bFlag)) // bytes
        cout << collector.get_total_size_on_disk_in_bytes();
    else if (has_particular_flag(switches, hFlag)) // MiB, etc.
        cout << to_human(collector.get_total_size_on_disk_in_clusters(), in.get_cluster_size());
    else // #clusters
        cout << collector.get_total_size_on_disk_in_clusters();
    cout << _3_SPACES;
    if (collector.get_mode() == Absolute_Directory)
        cout << folder << endl;
    else
        cout << "." << endl;
}

void print_report_name(CLI_Input in, Data_Collector collector)
{
    // step 1
    vector<string> sizes;
    vector<string> names;
    populate_report(in, collector, names, sizes);
    // step 2
    map<string, string> m;
    for (size_t i = 0; i < names.size(); i++)
        m.insert(pair<string, string>(names[i], sizes[i]));
    sizes.clear();
    names.clear();
    map<string, string>::const_iterator citr = m.cbegin();
    while (citr != m.cend())
    {
        names.push_back(citr->first);
        sizes.push_back(citr->second);
        ++citr;
    }
    // step 3
    reverse_if_needed(in, names, sizes);
    // step 4
    print_report(in, collector, names, sizes);
}

void print_report_size(CLI_Input in, Data_Collector collector)
{
    // step 1
    uintmax_t cluster_size = in.get_cluster_size();
    vector<string> switches = in.get_switches();
    vector<Child> children_folders = collector.get_children_folders();
    vector<uintmax_t> n_sizes;
    vector<string> sizes;
    vector<string> names;
    for (auto each : children_folders)
        names.push_back(each.get_location());
    names.push_back(in.get_path().string());
    for (auto each : children_folders)
        n_sizes.push_back(each.get_size_on_disk_in_clusters());
    n_sizes.push_back(collector.get_total_size_on_disk_in_clusters());
    // step 2
    map<uintmax_t, string> m;
    for (size_t i = 0; i < names.size(); i++)
        m.insert(pair<uintmax_t, string>(n_sizes[i], names[i]));
    names.clear();
    map<uintmax_t, string>::const_iterator citr = m.cbegin();
    while (citr != m.cend())
    {
        if (has_particular_flag(switches, bFlag))
            sizes.push_back(to_string((citr->first) * (cluster_size)));
        else if (has_particular_flag(switches, hFlag))
            sizes.push_back(to_human(citr->first, cluster_size));
        else
            sizes.push_back(to_string(citr->first));
        names.push_back(citr->second);
        ++citr;
    }
    // step 3
    reverse_if_needed(in, names, sizes);
    // step 4
    print_report(in, collector, names, sizes);
}

void print_report_absent(CLI_Input in, Data_Collector collector)
{
    // step 1
    vector<string> sizes;
    vector<string> names;
    populate_report(in, collector, names, sizes);
    // step 2
    reverse_if_needed(in, names, sizes);
    // step 3
    print_report(in, collector, names, sizes);
}

void populate_report(CLI_Input in, Data_Collector collector, vector<string> &names, vector<string> &sizes)
{
    vector<string> switches = in.get_switches();
    vector<Child> children_folders = collector.get_children_folders();
    // 1.1 populate names
    for (auto each : children_folders)
        names.push_back(each.get_location());
    names.push_back(in.get_path().string()); // why not .get_folder()? because if root folder parameter is NOT present, .get_folder() returns "".
    // 1.2 populate sizes
    if (has_particular_flag(switches, bFlag)) // bytes
    {
        for (auto each : children_folders)
            sizes.push_back(to_string(each.get_size_on_disk_in_bytes()));
        sizes.push_back(to_string(collector.get_total_size_on_disk_in_bytes()));
    }
    else if (has_particular_flag(switches, hFlag)) // MiB, etc.
    {
        for (auto each : children_folders)
            sizes.push_back(to_human(each.get_size_on_disk_in_clusters(), in.get_cluster_size()));
        sizes.push_back(to_human(collector.get_total_size_on_disk_in_clusters(), in.get_cluster_size()));
    }
    else // #clusters
    {
        for (auto each : children_folders)
            sizes.push_back(to_string(each.get_size_on_disk_in_clusters()));
        sizes.push_back(to_string(collector.get_total_size_on_disk_in_clusters()));
    }
}

void print_report(CLI_Input in, Data_Collector collector, vector<string> const &names, vector<string> const &sizes)
{

    size_t max_width_in_sizes_vector = get_max_width(sizes);
    if (collector.get_mode() == Current_Working_Directory)
    {
        string cwd = in.get_path().string();
        for (size_t i = 0; i < names.size(); i++)
        {
            cout << left << setw(max_width_in_sizes_vector) << sizes[i] << _3_SPACES;
            if (names[i].compare(cwd) == 0)
                cout << "." << endl;
            else
            {
                string partial_name = names[i].substr(cwd.length() + 1, string::npos);
                cout << ".\\" << partial_name << endl;
            }
        }
    }
    else
    {
        for (size_t i = 0; i < names.size(); i++)
            cout << left << setw(max_width_in_sizes_vector) << sizes[i] << _3_SPACES << names[i] << endl;
    }
}

void reverse_if_needed(CLI_Input in, vector<string> &names, vector<string> &sizes)
{
    if (has_particular_flag(in.get_switches(), rFlag))
    {
        reverse(names.begin(), names.end());
        reverse(sizes.begin(), sizes.end());
    }
}