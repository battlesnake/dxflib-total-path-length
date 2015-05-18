/**
 * @file dl_dxf.cpp
 */

/*****************************************************************************
**  $Id: dl_dxf.cpp,v 1.14 2002/03/09 01:40:14 andrew23 Exp $
**
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

#include "dl_dxf.h"
#include "dl_codes.h"
#include "dl_creationinterface.h"
#include "dl_writer_ascii.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


/**
 * @brief Reads the given file and calls the appropriate functions in
 * the given creation interface for every entity found in the file.
 *
 * @param file Full path of the file.
 * @creationInterface Pointer to an implementation of a creation 
 *   interface
 */
bool
DL_Dxf::in(const char* file, DL_CreationInterface* creationInterface) {
    FILE *fp;

    fp = fopen(file, "rt");
    if (fp) {
        while (readDxfGroups(fp, creationInterface)) {}
        fclose(fp);
        return true;
    }

    return false;
} // in()



/**
 * @brief Reads a group couplet from a DXF file.  Calls another function
 * to process it.
 *
 * A group couplet consists of two lines that represent a single
 * piece of data.  An integer constant on the first line indicates
 * the type of data.  The value is on the next line.\n
 *
 * This function reads a couplet, determines the type of data, and
 * passes the value to the the appropriate handler function of
 * \p creationInterface.\n
 * 
 * \p fp is advanced so that the next call to \p readDXFGroups() reads
 * the next couplet in the file.
 *
 * @param fp Handle of input file
 * @param creationInterface Handle of class which processes entities
 *		in the file
 *
 * @retval true If EOF not reached.
 * @retval false If EOF reached.
 */
bool
DL_Dxf::readDxfGroups(FILE *fp, DL_CreationInterface* creationInterface) {
    // Only the useful part of the group code
    static char groupCodeTmp[DL_DXF_MAXLINE];
    // ...same as integer
    static unsigned int groupCode;
    // Only the useful part of the group value
    static char groupValue[DL_DXF_MAXLINE];

    // Read one group of the DXF file and chop the lines:
    if (DL_Dxf::getChoppedLine(groupCodeTmp, DL_DXF_MAXLINE, fp) &&
            DL_Dxf::getChoppedLine(groupValue, DL_DXF_MAXLINE, fp) ) {

        groupCode = (unsigned int)atoi(groupCodeTmp);

        processDXFGroup(creationInterface, groupCode, groupValue);
    }

    return !feof(fp);
} // readDXFGroups()



/**
 * @brief Processes a group
 *
 * @param creationInterface Handle to class that creates entities and
 * other CAD data from DXF group codes
 *
 * @param groupCode Constant indicating the data type of the group.
 *
 * @param groupValue The data value.
 *
 * @retval true if done processing current entity and new entity begun
 *
 * @retval false if not done processing current entity
*/
bool
DL_Dxf::processDXFGroup(DL_CreationInterface* creationInterface,
                        int groupCode, const char *groupValue) {

    static int currentEntity = DL_ENTITY_UNKNOWN;
    // Stores the group codes
    static char values[DL_DXF_MAXGROUPCODE][DL_DXF_MAXLINE];
    static bool firstCall=true;
    // Pointer to current polyline to fill in with VERTEX entities
    //static DL_Polyline* currentPolyline = 0;
    // Useful part of the group value if it's a setting
    static char settingValue[DL_DXF_MAXLINE];

    // Init on first call
    if (firstCall) {
        for (int i=0; i<DL_DXF_MAXGROUPCODE; ++i) {
            values[i][0] = '\0';
        }
        firstCall=false;
    }

    // Reset current polyline:
    //if (currentEntity!=DL_ENTITY_POLYLINE && currentEntity!=DL_ENTITY_VERTEX) {
    //    currentPolyline = 0;
    //}

    if (groupCode==0 || groupCode==9) { // Indicates start of entity or var
        // If new entity is encountered, last one must be complete
        // Add it via creationInterface
        switch (currentEntity) {
        case DL_ENTITY_SETTING:
            //if (!strcmp(settingValue, "$INSUNITS")) {
            //    container->setUnit(DL_Units::dxfint2unit (atoi (values[70])));
            //}
            break;

        case DL_ENTITY_LAYER:
            //container->addLayer(new DL_Layer (values[2]));
            break;

        case DL_ENTITY_POINT: {
                double p1[] = { atof(values[10]),
                                atof(values[20]),
                                atof(values[30]) };

                creationInterface->addPoint(p1);
            }
            break;

        case DL_ENTITY_LINE: {
                double p1[] = { atof(values[10]),
                                atof(values[20]),
                                atof(values[30]) };
                double p2[] = { atof(values[11]),
                                atof(values[21]),
                                atof(values[31]) };

                creationInterface->addLine(p1, p2);
            }
            break;

        case DL_ENTITY_POLYLINE: {
				printf("found polyline\n");
                creationInterface->addPolyline();
            }
            break;

        case DL_ENTITY_VERTEX: {
                double p1[] = { atof(values[10]),
                                atof(values[20]),
                                atof(values[30]) };

                creationInterface->addVertex(p1, 0.0);
            }
            break;

        case DL_ENTITY_ARC: {
                double c[] = { atof(values[10]),
                               atof(values[20]),
                               atof(values[30]) };

                creationInterface->addArc(c,
                                          atof(values[40]),
                                          atof(values[50]),
                                          atof(values[51]),
                                          false);
            }
            break;

        case DL_ENTITY_CIRCLE: {
                double c[] = { atof(values[10]),
                               atof(values[20]),
                               atof(values[30]) };

                creationInterface->addCircle(c,
                                             atof(values[40]));
            }
            break;

        case DL_ENTITY_TEXT:
            //{
            //	DL_Vector v (atof(values[10]), atof(values[20]));
            //  container->addEntity (new DL_Text (v,
            //                                     values[1],
            //                                     atof(values[50]),
            //                                     atof(values[40])));
            //}
            break;

        default:
            break;
        }

        // Last DXF entity or setting has been handled
        // Now determine what the next entity or setting type is
        if (groupValue[0]=='$') {						// Read DXF settings:
            // Read DXF
            if (!strcmp(groupValue, "$INSUNITS")) {
                currentEntity = DL_ENTITY_SETTING;
            }
            strcpy(settingValue, groupValue);
        } else if (!strcmp(groupValue, "LAYER")) {		// else new entity:
            currentEntity = DL_ENTITY_LAYER;
        } else if (!strcmp(groupValue, "POINT")) {
            currentEntity = DL_ENTITY_POINT;
        } else if (!strcmp(groupValue, "LINE")) {
            currentEntity = DL_ENTITY_LINE;
        } else if (!strcmp(groupValue, "POLYLINE")) {
            currentEntity = DL_ENTITY_POLYLINE;
        } else if (!strcmp(groupValue, "VERTEX")) {
            currentEntity = DL_ENTITY_VERTEX;
        } else if (!strcmp(groupValue, "ARC")) {
            currentEntity = DL_ENTITY_ARC;
        } else if (!strcmp(groupValue, "CIRCLE")) {
            currentEntity = DL_ENTITY_CIRCLE;
        } else if (!strcmp(groupValue, "TEXT")) {
            currentEntity = DL_ENTITY_TEXT;
        } else {
            currentEntity = DL_ENTITY_UNKNOWN;
        }

        return true;

    } else {
        // Group code does not indicate start of new entity or setting,
        // so this group must be continuation of data for the current
        // one.

        // Read in all codes (no matter if needed or not):
        if (groupCode<DL_DXF_MAXGROUPCODE) {
            strncpy(values[groupCode], groupValue, DL_DXF_MAXLINE);
        }

        return false;
    }
} // processDXFGroup()



/**
 * @brief
 * Reads line from file & strips whitespace at start and newline at end.
 *
 * @param s Output\n
 *		Pointer to character array that chopped line will be returned in.
 * @param size Size of \p s.  (Including space for NULL.)
 * @param fp Input\n
 *		Handle of input file.
 *
 * @retval true if line could be read
 * @retval false if \p fp is already at end of file
 *
 * @todo Change function to use safer FreeBSD strl* functions
 * @todo Is it a problem if line is blank (i.e., newline only)?
 *		Then, when function returns, (s==NULL).
 */
bool
DL_Dxf::getChoppedLine(char *s, unsigned int size, FILE *fp) {
    if (!feof(fp)) {
        // The whole line in the file.  Includes space for NULL.
        char* wholeLine = new char[size];
        // Only the useful part of the line
        char* line;

        if (line = fgets (wholeLine, size, fp)) { // Evaluates to fgets() retval
            // line == wholeLine at this point.
            // Both guaranteed to be NULL terminated.

            // Strip leading whitespace and trailing CR/LF.
            stripWhiteSpace(line);

            strncpy(s, line, size);
            // s should always be NULL terminated, because:
            assert(size > strlen(line));
        }

        delete[] wholeLine; // Done with wholeLine

        return true;
    } else {
        s[0] = '\0';
        return false;
    }
} // getChoppedLine()



/**
 * @brief Strips leading whitespace and trailing Carriage Return (CR)
 * and Line Feed (LF) from NULL terminated string.
 *
 * @param s Input and output.
 *		NULL terminates string.
 *
 * @retval true if \p s is non-NULL
 * @retval false if \p s is NULL
 */
bool
DL_Dxf::stripWhiteSpace(char *s) {
    // Skip whitespace, excluding \n, at beginning of line
    while (s[0]==' ' || s[0]=='\t') {
        ++s;
    }

    int lastChar = strlen(s) - 1; // Last non-NULL character in s

    // Is last character CR or LF?
    while ( (lastChar >= 0) &&
            ((s[lastChar] == '\n') || (s[lastChar] == '\r')) ) {
        // Replace CR or LF with NULL and decrement string index
        // Would s[lastChar--] work?
        s[lastChar] = '\0';
        lastChar--;
    }

    return (s) ? true : false;
} // stripWhiteSpace()


/**
 * @brief Opens the given file for writing and returns a pointer
 * to the dxf writer. This pointer needs to be passed on to other
 * writing functions.
 *
 * @param file Full path of the file to open.
 *
 * @return Pointer to an ascii dxf writer object.
 */
DL_WriterA*
DL_Dxf::out(const char* file) {
    char* f = new char[strlen(file)];
    strcpy(f, file);
    DL_WriterA* dw = new DL_WriterA(f);
    return dw;
}

/**
 * @brief Writes a DXF header to the file currently opened 
 * by the given DXF writer object.
 */
void
DL_Dxf::writeHeader(DL_WriterA& dw) {
    dw.sectionHeader();
    dw.sectionEnd();
}

void
DL_Dxf::writePoint(DL_WriterA& dw,
                   double x, double y) {
    dw.entity("POINT");
    dw.coord(POINT_COORD_CODE, x, y);
}

void
DL_Dxf::writeLine(DL_WriterA& dw,
                  double x1, double y1,
                  double x2, double y2) {
    dw.entity("LINE");
    dw.coord(LINE_START_CODE, x1, y1);
    dw.coord(LINE_END_CODE, x2, y2);
}

void
DL_Dxf::writePolyline(DL_WriterA& dw) {
    dw.entity("POLYLINE");
    dw.coord(VERTEX_COORD_CODE, 0.0, 0.0);
}

void
DL_Dxf::writeVertex(DL_WriterA& dw,
                    double x, double y) {
    dw.entity("VERTEX");
    dw.coord(VERTEX_COORD_CODE, x, y);
}

// EOF

