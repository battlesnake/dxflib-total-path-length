/*
 * @file main.cpp
 */

/*****************************************************************************
**  This is part of the dxflib library
**  Copyright (C) 2000-2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dl_dxf.h"
#include "dl_creationinterface.h"

#include "test_creationclass.h"
#include "total_length.h"

void usage();


/*
 * @brief Main function for DXFLib test program.
 *
 * @param argc Number of delimited items on command line,
 *		including program name.
 * @param argv Pointer to array of command line items
 *
 * @retval 0 if missing input file argument or
 *		file couldn't be opened
 * @retval 1 if file opened
 */
int main(int argc, char **argv) {
	int i = 0;
	int mode = 0;
	char *file = 0;

	for (i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (arg[0] == '-') {
			if (strcmp(arg, "-l") == 0) {
				mode = 1;
			} else {
				std::cout << "Invalid parameter: '" << arg << "'\n";
				usage();
				return 2;
			}
		} else {
			if (file) {
				std::cout << "Multiple files not supported\n";
				usage();
				return 2;
			}
			file = arg;
		}
	}

	// Check given arguments:
	if (!file) {
		usage();
		return 2;
	}
	
	// Load DXF file into memory:
    std::cout << "Reading file " << file << "...\n";

	if (mode == 0) {
		Test_CreationClass creationClass;
		if (!DL_Dxf::in(file, &creationClass)) { // if file open failed
			std::cerr << file << " could not be opened.\n";
			return 1;
		}
	} else if (mode == 1) {
		TotalLengthCalc ruler;
		if (!DL_Dxf::in(file, &ruler)) { // if file open failed
			std::cerr << file << " could not be opened.\n";
			return 1;
		}
		printf("Total length = %f\n", (float) ruler.getTotal());
	}
	return 0;
	
}



/*
 * @brief Prints error message if file name not specified as command
 * line argument.
 */
void usage() {
	std::cout << "\nUsage: test [-l] <DXF file>\n\n";
}

// EOF
