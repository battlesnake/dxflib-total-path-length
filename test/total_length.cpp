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

#include "total_length.h"

#include <iostream>
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897931
#define sqr(x) ((x)*(x))
#define sqdiff(a,b) sqr((a) - (b))
#define dist(p,q) sqrt(sqdiff(p[0],q[0]) + sqdiff(p[1],q[1]) + sqdiff(p[2],q[2]))

/**
 * Default constructor.
 */
TotalLengthCalc::TotalLengthCalc() { total = 0; }


/**
 * Sample implementation of the method which handles point entities.
 */
void
TotalLengthCalc::addPoint(double point[]) {
	total += 0;
//	printf("POINT	(%12.6f, %12.6f, %12.6f)\n",
//		point[0], point[1], point[2]);
}

/**
 * Sample implementation of the method which handles line entities.
 */
void
TotalLengthCalc::addLine(double point1[], double point2[]) {
	total += dist(point1, point2);
//	printf("LINE	 (%12.6f, %12.6f, %12.6f) (%12.6f, %12.6f, %12.6f)\n",
//		point1[0], point1[1], point1[2],
//		point2[0], point2[1], point2[2]);
}

/**
 * Sample implementation of the method which handles arc entities.
 */
void
TotalLengthCalc::addArc(double center[],
							double radius,
							double angle1, double angle2,
							bool reversed) {
	/* Are angles in radians?  I sure hope so. */
	total += fabs(angle1 - angle2) * radius;
//	printf("ARC	  (%12.6f, %12.6f, %12.6f) %12.6f, %12.6f, %12.6f %d\n",
//		center[0], center[1], center[2],
//		radius, angle1, angle2, reversed);
}

/**
 * Sample implementation of the method which handles circle entities.
 */
void
TotalLengthCalc::addCircle(double center[],
							  double radius) {
	total += 2 * PI * radius;
	printf("CIRCLE	(%12.6f, %12.6f, %12.6f) %12.6f\n",
			center[0], center[1], center[2],
			radius);
}


/**
 * Sample implementation of the method which handles polyline entities.
 */
void
TotalLengthCalc::addPolyline() {
	total += 0;
//	printf("POLYLINE \n");
}


/**
 * Sample implementation of the method which handles vertices.
 */
void 
TotalLengthCalc::addVertex(double point[], double bulge) {
	total += 0;
//	printf("VERTEX	(%12.6f, %12.6f, %12.6f) %12.6f\n",
//			point[0], point[1], point[2],
//			bulge);
}


// EOF
