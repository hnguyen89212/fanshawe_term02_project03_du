// ----------------------------------------------
// LINK TO HEADER FILE
// ----------------------------------------------
#include "Tools.hpp"

// ----------------------------------------------
// FUNCTIONS IMPLEMENTATION
// ----------------------------------------------

/**
 * PHASE 1 FUNCTIONS
 */

bool is_valid_single_letter_switch(string f)
{
    return single_letter_flags.find(f) != single_letter_flags.end();
}

void print_help()
{
    cout << "====================================\n";
    cout << "du (c) 2019 by Hai Nguyen\n";
    cout << "====================================\n";
    cout << "Version 1.0.0\n\n";
    cout << "A mini program reporting disk usage inspired by the UNIX command \"du\".\n\n";
    cout << "Usage: du [-skhb] [--help] [-block-size=dddd] [folder]*\n\n";
    cout << "Examples:\n";
    cout << "\tdu\n\t> displays the sum of the cluster sizes of each directory\n\tstarting the current working directory\n\n";
    cout << "\tdu folder\n\t> displays the summ of the cluster sizes of each directory\n\n";
    cout << "\tdu -h\n\t> displays the results in a human readable form\n\n";
    cout << "\tdu -s\n\t> displays only the final summary\n\n";
    cout << "\tdu -b\n\t> displays in bytes\n\n";
    cout << "\tdu -k\n\t> sets cluster size to 1024 bytes\n\n";
    cout << "\tdu -z\n\t> displays the list sorted by size\n\n";
    cout << "\tdu -n\n\t> displays the list sorted by name\n\n";
    cout << "\tdu -r\n\t> displays the list in reverse order\n\n";
    cout << "\tdu --block-size=dddd\n\t> sets the cluster size to the specified integer dddd > 0.\n\n";
    cout << "\tdu --help\n\t> displays the help\n\n";
    cout << "*Notes:\n";
    cout << "1. -b and -h switches are incompatible\n";
    cout << "2. -k and --block-size are incompatible\n";
    cout << "3. -z and -n switches are incompatible\n";
    cout << "4. No switch should be duplicated\n";
    cout << "5. There cannot be unknown switches\n";
}

bool has_particular_flag(vector<string> switches, string flag)
{
    vector<string>::const_iterator citr = switches.cbegin();
    while (citr != switches.cend())
    {
        string s = *(citr);
        if (s.compare(flag) == 0)
            return true;
        ++citr;
    }
    return false;
}

bool has_b_and_h_flags(vector<string> switches)
{
    bool has_b_flag = has_particular_flag(switches, bFlag);
    bool has_h_flag = has_particular_flag(switches, hFlag);
    if (has_b_flag && has_h_flag)
    {
        cerr << "Error: Cannot use -b and -h simultaneously.\n";
        return true;
    }
    return false;
}

bool has_k_flag(vector<string> switches)
{
    return has_particular_flag(switches, kFlag);
}

bool has_z_and_n_flags(vector<string> switches)
{
    bool has_z_flag = has_particular_flag(switches, zFlag);
    bool has_n_flag = has_particular_flag(switches, nFlag);
    if (has_z_flag && has_n_flag)
    {
        cerr << "Error: Cannot use -n and -z simultaneously.\n";
        return true;
    }
    return false;
}

bool has_duplicates_flags(vector<string> switches)
{
    set<string> s(switches.begin(), switches.end());
    // if vector and set has different sizes --> there must be duplicates.
    if (s.size() != switches.size())
    {
        cerr << "Error: duplicate switches are not allowed\n";
        return true;
    }
    return false;
}

bool qualifies_as_direct_child(string base, string key)
{
    string extended = key.substr(base.length() + 1, string::npos);
    return extended.find("\\", 0) == string::npos;
}

uintmax_t to_size_on_disk_in_clusters(uintmax_t real_size_in_bytes, uintmax_t cluster_size)
{
    return (uintmax_t)ceil(real_size_in_bytes * 1.0 / cluster_size);
}

/**
 * PHASE 3 FUNCTIONS
 */

string to_human(uintmax_t number_of_clusters, uintmax_t cluster_size_in_bytes)
{
    if (number_of_clusters == 0)
        return "0";
    uintmax_t bytes = number_of_clusters * cluster_size_in_bytes;
    string result("");
    string unit("");
    double temp = 0.0;
    if (bytes < _1_KiB)
    {
        temp = bytes * 1.0;
        unit.append("B");
    }
    else if (bytes < _1_MiB)
    {
        temp = bytes * 1.0 / _1_KiB;
        unit.append("K");
    }
    else if (bytes < _1_GiB)
    {
        temp = bytes * 1.0 / _1_MiB;
        unit.append("M");
    }
    else if (bytes < _1_TiB)
    {
        temp = bytes * 1.0 / _1_GiB;
        unit.append("G");
    }
    // round
    if (temp >= 10)
    {
        // round to zero decimal place (nearest
        uintmax_t n = (uintmax_t)(round(temp));
        result.append(to_string(n));
    }
    else
    {
        // round to one decimal place, cut all trailing zeros
        temp = static_cast<uintmax_t>((temp + 0.05) * 10.0) / 10.0;
        string str = to_string(temp);
        str.erase(str.find_last_not_of('0') + 1, string::npos);
        result.append(str);
    }
    result.append(unit);
    return result;
}

size_t get_max_width(vector<string> v)
{
    size_t max_width = 0;
    for (auto each : v)
    {
        size_t current_length = each.length();
        if (max_width < current_length)
            max_width = current_length;
    }
    return max_width;
}