// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "CLI_Input.hpp"

// ----------------------------------------------
// CLASS IMPLEMENTATION
// ----------------------------------------------

// constructor
CLI_Input::CLI_Input(int argc, char *argv[])
{
    for (int i = 1; i < argc && valid; i++)
    {
        string temp(*(argv + i));
        // catch a hyphen --> collect single-letter flags/switches
        if (temp[0] == '-' && temp[1] != '-')
        {
            for (size_t i = 1; i < temp.length(); i++)
            {
                string s(temp.substr(i, 1));
                if (is_valid_single_letter_switch(s))
                    switches.push_back(s);
                else
                {
                    cerr << "Error: unknown switch: <" << s << ">\n";
                    valid = false;
                    break;
                }
            }
        }
        // catch 2 hyphens --> deal with block size or word switch
        if (temp[0] == '-' && temp[1] == '-')
        {
            string sub = temp.substr(2);
            int blockSizeIndex = sub.find(blockSizeFlag);
            // if user really specify --block-size
            if (blockSizeIndex == 0)
            {
                try
                {
                    string sizeAsStr = sub.substr(11);
                    long temp_cluster_size = stol(sizeAsStr);
                    if (temp_cluster_size <= 0)
                    {
                        cerr << "Error: block size cannot be set to negative values or zero <" << temp_cluster_size << ">\n";
                        valid = false;
                        return;
                    }
                    cluster_size = temp_cluster_size;
                }
                catch (const std::exception &e)
                {
                    cout << e.what() << endl;
                    cerr << "Error: Bad switch <--" << sub << ">" << endl;
                    valid = false;
                }
            }
            // otherwise, it is bad switch
            else
            {
                cerr << "Error: Bad switch <--" << sub << ">" << endl;
                valid = false;
            }
        }
        // catch folder
        if (temp[0] != '-')
            folder = temp;
    }
    // At this point, we are done traversing the CLI inputs, we proceed to check rules
    if (!valid)
        return;
    // check the flag constraints/compatibility {b, h}, {z, n}, duplication
    if (has_b_and_h_flags(switches) || has_z_and_n_flags(switches) || has_duplicates_flags(switches))
    {
        valid = false;
        return;
    }
    // up to this point, cluster_size can only be changed by --block-size only
    // so, if --block-size is present, cluster_size is NOT default anymore
    // check -k and --block-size
    if (cluster_size != default_cluster_size_in_bytes && has_k_flag(switches))
    {
        cerr << "Error: -k and --block-size cannot be used simultaneously.\n";
        valid = false;
        return;
    }
    if (has_k_flag(switches))
        cluster_size = 1024;
    // resolve the path/destination
    if (folder.empty())
        // here, cwd is chosen
        destination = canonical(".");
    else
    {
        destination = folder;
        if (!exists(destination))
        {
            cerr << "Error: folder <" << destination << "> does not exist.\n";
            valid = false;
            return;
        }
    }
}

bool CLI_Input::is_valid()
{
    return valid;
}

uintmax_t CLI_Input::get_cluster_size()
{
    return cluster_size;
}

vector<string> CLI_Input::get_switches()
{
    return switches;
}

string CLI_Input::get_folder()
{
    return folder;
}

path CLI_Input::get_path()
{
    return destination;
}

void CLI_Input::print_information()
{
    // validity
    cout << "valid = " << this->is_valid() << endl;
    // switches
    cout << "switches = " << endl;
    vector<string>::const_iterator citr = switches.begin();
    while (citr != switches.cend())
        cout << *(citr++) << endl;
    // cluster size
    cout << "cluster size = " << this->get_cluster_size() << endl;
    // folder
    cout << "folder parameter = " << this->get_folder() << endl;
    // path
    cout << "path = " << this->get_path() << endl
         << endl;
}