// ----------------------------------------------
// IMPORT LIBRARIES
// ----------------------------------------------
#include "Report.hpp"

// ----------------------------------------------
// DOCUMENTATION
// ----------------------------------------------
/**
 * Author:          Hai Nguyen
 * Student ID:      0904995
 * Program:         CPA2, Winter 2019 Intake
 * Start date:      August 3rd, 2019
 * Complete date:	August 16th, 2019
 * Project:         #3 du
 * Professor:       Janice Manning
 * Purpose:         Implementing the LINUX-inspired utility "du"
 * Dependencies:	Tools, CLI_Input, Child, Data_Collector, Report (.hpp and .cpp files)
 * Software used:   Visual Studio 2019, Visual Studio Code
 * Usage:			du [-sbhznrk] [--help] [--block-size=dddd] [root folder]
 */

 // ----------------------------------------------
 // ENTRY POINT -- MAIN PROGRAM
 // ----------------------------------------------
int main(int argc, char* argv[])
{
	// scan CLI for --help
	for (int i = 1; i < argc; i++)
	{
		string temp(*(argv + i));
		if (temp.compare("--help") == 0)
		{
			print_help();
			return EXIT_SUCCESS;
		}
	}

	// ------------------------------------------
	// PHASE 1: PARSE CLI INPUT
	// ------------------------------------------
	CLI_Input in(argc, argv);
	//in.print_information();
	if (!in.is_valid())
		return EXIT_FAILURE;

	// ------------------------------------------
	// PHASE 2: COLLECT DATA
	// ------------------------------------------
	Data_Collector collector(in);
	//collector.print_information();

	// ------------------------------------------
	// PHASE 3: REPORT
	// ------------------------------------------
	print_report(in, collector);

	return EXIT_SUCCESS;
}