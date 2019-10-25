#ifndef TOOLS_H
#define TOOLS_H

// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <filesystem>
#include <cinttypes>
#include <sys/stat.h>

using namespace std;
using namespace std::experimental::filesystem;

// ----------------------------------------------
// CONSTANTS -- all constants, literals in program are here
// ----------------------------------------------

// a cluster accounts for 4096 bytes
const uintmax_t default_cluster_size_in_bytes = 4096;

// shows only the root folder, sum of all clusters
const string sFlag = "s";

// shows units in bytes, not clusters
const string bFlag = "b";

// makes human readable
// units are in KiB, MiB, GiB, TiB rounded to either
// 1. one decimal place if less than 10 units.
// 2. zero decimal place otherwise
const string hFlag = "h";

// shows rows sorted by sizes
const string zFlag = "z";

// shows rows sorted by names
const string nFlag = "n";

// shows rows in reverse order
const string rFlag = "r";

// sets cluster size to 1024 bytes
const string kFlag = "k";

// stores all flags in a set
const set<string> single_letter_flags = {
    sFlag,
    bFlag,
    hFlag,
    zFlag,
    nFlag,
    rFlag,
    kFlag};

// sets cluster size to specified value > 0
const string blockSizeFlag = "block-size";

// displays help listing
const string helpFlag = "help";

// possible modes in program
// if user does not specify absolute path => "current working directory"
// "absolute directory" otherwise
enum Mode
{
    Absolute_Directory,
    Current_Working_Directory
};

// 1 byte
const uintmax_t _1_B = 1;

// 1 Kibibyte = 1,024 bytes
const uintmax_t _1_KiB = (uintmax_t)pow(1024, 1);

// 1 Mebibyte = 1,048,576 bytes
const uintmax_t _1_MiB = (uintmax_t)pow(1024, 2);

// 1 Gibibyte = 1,073,741,824 bytes
const uintmax_t _1_GiB = (uintmax_t)pow(1024, 3);

// 1 Tebibyte = 1,099,511,627,776 bytes
const uintmax_t _1_TiB = (uintmax_t)pow(1024, 4);

// group of 3 consecutive space character
// for printing formatted report
const string _3_SPACES = "   ";

// ----------------------------------------------
// FUNCTION PROTOTYPES
// ----------------------------------------------

/**
 * PHASE 1 FUNCTIONS
 * For parsing CLI inputs
 */

// Returns true if "f" matches one of single letter switches.
bool is_valid_single_letter_switch(string f);

// Shows program instruction.
void print_help();

bool has_particular_flag(vector<string> switches, string flag);

// Returns true if both -b and -h present.
bool has_b_and_h_flags(vector<string> switches);

// Returns true if both -k and --block-size specified.
bool has_k_flag(vector<string> switches);

// Returns true if both -z and -n present.
bool has_z_and_n_flags(vector<string> switches);

// Returns true if a flag is duplicated.
bool has_duplicates_flags(vector<string> switches);

/**
 * PHASE 2 FUNCTIONS
 */

// returns true if "key" is a child of "base".
// for example, base = "C:\Temp" and key = "C:\Temp\{2.1} HiLo", this returns true
// because the second string qualifies as a child/subfolder/subfile of the first one.
bool qualifies_as_direct_child(string base, string key);

// returns size on disk based on real size and cluster size.
uintmax_t to_size_on_disk_in_clusters(uintmax_t real_size_in_bytes, uintmax_t cluster_size);

/**
 * PHASE 3 FUNCTIONS
 */

// returns a string showing size in human readable format (MiB, etc.).
string to_human(uintmax_t number_of_clusters, uintmax_t cluster_size_in_bytes);

// returns the largest length of a vector os string "v".
size_t get_max_width(vector<string> v);

#endif
