/**
 * @file dl_dxf.h
 */

/*****************************************************************************
**  $Id: dl_dxf.h,v 1.8 2002/03/09 01:40:14 andrew23 Exp $
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

#ifndef DL_DXF_H
#define DL_DXF_H

#include <stdio.h>

class DL_CreationInterface;
class DL_WriterA;

#define DL_DXF_MAXLINE 1024
#define DL_DXF_MAXGROUPCODE 128

#define DL_ENTITY_UNKNOWN  0
#define DL_ENTITY_LAYER    10
#define DL_ENTITY_SETTING  50
#define DL_ENTITY_POINT    100
#define DL_ENTITY_LINE     101
#define DL_ENTITY_POLYLINE 102
#define DL_ENTITY_VERTEX   103
#define DL_ENTITY_ARC      104
#define DL_ENTITY_CIRCLE   105
#define DL_ENTITY_TEXT     106


/**
 * @brief Reads the given DXF file.
 *
 * This class reads in a DXF file and calls methods from the 
 * interface DL_EntityContainer to add the entities to the
 * contianer provided by the user of the library.
 *
 * @param file Input
 *		Path and name of file to read
 * @param creationInterface
 *		Pointer to the class which takes care of the entities in the file.
 *
 * @retval true If \p file could be opened.
 * @retval false If \p file could not be opened.
 *
 * @author Andrew Mustun
 */
class DL_Dxf {
public:
    static bool in(const char* file, DL_CreationInterface* creationInterface);
    static bool readDxfGroups(FILE* fp, DL_CreationInterface* creationInterface);
    static bool processDXFGroup(DL_CreationInterface* creationInterface,
                                int groupCode, const char* groupValue);
    static bool getChoppedLine(char *s, unsigned int size, FILE *stream);
    static bool stripWhiteSpace(char *s);

	static DL_WriterA* out(const char* file);
	static void writeHeader(DL_WriterA& dw);
	static void writePoint(DL_WriterA& dw, 
                           double x, double y);
	static void writeLine(DL_WriterA& dw, 
                          double x1, double y1,
                          double x2, double y2);
	static void writePolyline(DL_WriterA& dw);
	static void writeVertex(DL_WriterA& dw,
                            double x, double y);

};

#endif

// EOF
