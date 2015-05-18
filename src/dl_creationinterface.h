/**
 * @file dl_creationinterface.h
 */
 
/*****************************************************************************
**  $Id: dl_creationinterface.h,v 1.4 2001/12/15 12:47:25 rjcjr9 Exp $
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

#ifndef DL_CREATIONINTERFACE_H
#define DL_CREATIONINTERFACE_H


/**
 * Abstract class (interface) for the creation of new entities.
 * Inherit your class which takes care of the entities in the 
 * processed DXF file from this interface. 
 *
 * @author Andrew Mustun
 */
class DL_CreationInterface {
public:
    DL_CreationInterface() {}

    /** Called for every point in the file */
    virtual void addPoint(double point[]) = 0;

    /** Called for every line in the file */
    virtual void addLine(double point1[], double point2[]) = 0;

    /** Called for every arc in the file */
	virtual void addArc(double center[], 
                        double radius, 
                        double angle1, double angle2, 
                        bool reversed) = 0;
	
    /** Called for every arc in the file */
	virtual void addCircle(double center[], 
                           double radius) = 0;

	/** Called for every polyline start in the file */
	virtual void addPolyline() = 0;

    /** Called for every polyline vertex in the file */
	virtual void addVertex(double point[], double bulge) = 0;
};

#endif
