/*****************************************************************************
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
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

#ifndef TOTAL_LENGTH_H
#define TOTAL_LENGTH_H

#include "dl_creationinterface.h"



class TotalLengthCalc : public DL_CreationInterface {
private:
	double total;
public:
	TotalLengthCalc();

	virtual void addPoint(double point[]);
	virtual void addLine(double point1[], double point2[]);
	virtual void addArc(double center[],
		double radius,
		double angle1, double angle2,
		bool reversed);
	virtual void addCircle(double center[],
		double radius);
	virtual void addPolyline();
	virtual void addVertex(double point[], double bulge);

	double getTotal() const { return total; }
};

#endif
