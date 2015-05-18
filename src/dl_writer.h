/*!
	\file dl_writer.h
	\brief Defines conversation bar class interfaces

*/
/*
	This is part of the dxflib library.
	Copyright (C) 2001 Robert J. Campbell Jr.
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
	
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

// Embeds version info in the executable, but does not load at run time.
#pragma comment(exestr, "$Id: dl_writer.h,v 1.2 2002/01/18 23:31:15 rjcjr9 Exp $")

//! If DL_WRITER_H is defined, dl_writer.h has already been included and it will
//! not be processed again.\n
//! If DL_WRITER_H is undefined, it will be defined and dl_writer.h will be
//! included.
#if !defined(DL_WRITER_H)
#define DL_WRITER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// DL_Writer
//////////////////////////////////////////////////////////////////////

/**
 * @brief Defines interface for writing low level DXF constructs to
 * a file; implementation is defined in derived classes that write
 * to binary or ASCII files.\n
 * Implements functions that write higher level constructs in terms of
 * the low level ones.
 *
 * @todo Add error checking for string/entry length.
 */
class DL_Writer
{
public:
	DL_Writer() : m_handle(0) {}

	virtual ~DL_Writer() {};

	void section(const char* name) const
	{
		dxfString(0, "SECTION");
		dxfString(2, name);
	}

	void sectionHeader() const { section("HEADER"); }
	void sectionTables() const { section("TABLES"); }
	void sectionBlocks() const { section("BLOCKS"); }
	void sectionEntities() const { section("ENTITIES"); }
	void sectionClasses() const { section("CLASSES"); }
	void sectionObjects() const { section("OBJECTS"); }
	void sectionEnd() const { dxfString(0, "ENDSEC"); }
	void dxfEOF() const { dxfString(0, "EOF"); }
	void comment(const char* text) const { dxfString(999, text); }

	void entity(const char* entTypeName) const { dxfString(0, entTypeName); }
	void subClass(const char* sub) const { dxfString(100, sub); }
	void layer(const char* layerName)  const { dxfString(8, layerName); }
	void color(int col=256) const { dxfInt(62, col); }
	void lineType(const char *lt) const { dxfString(6, lt); }
	void lineTypeScale(double scale) const { dxfReal(48, scale); }
	void lineWeight(int lw) const { dxfInt(370, lw); }

	void coord(int gc, double x, double y, double z=0) const 
	{
		dxfReal(gc, x);
		dxfReal(gc+10, y);
		dxfReal(gc+20, z);
	}

	// Overloading on pointer & number is a bad idea
	void coordTriplet(int gc, const double* value) const
	{
		if (value)
		{
			dxfReal(gc, *value++);
			dxfReal(gc+10, *value++);
			dxfReal(gc+20, *value++);
		}
	}
	
	void resetHandle() const { m_handle = 0; }

	/*!
		\brief Writes a unique handle
	*/
	void handle() const { dxfInt(5, m_handle++); }

	virtual void dxfReal(int gc, double value) const = 0;
	virtual void dxfInt(int gc, int value) const = 0;
	virtual void dxfString(int gc, const char* value) const = 0;

protected:
	mutable unsigned long m_handle;
private:
};

#endif // !defined(DL_WRITER_H)
