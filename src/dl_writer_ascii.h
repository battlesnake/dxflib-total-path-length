/*!
	\file dl_writer_ascii.h
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
#pragma comment(exestr, "$Id: dl_writer_ascii.h,v 1.3 2002/03/10 01:50:14 andrew23 Exp $")

//! If DL_WRITER_ASCII_H is defined, dl_writer_ascii.h has already been included and it will
//! not be processed again.\n
//! If DL_WRITER_ASCII_H is undefined, it will be defined and dl_writer_ascii.h will be
//! included.
#if !defined(DL_WRITER_ASCII_H)
#define DL_WRITER_ASCII_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dl_writer.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////
// DL_WriterA
//////////////////////////////////////////////////////////////////////

/**
 * @brief Implements functions defined in DL_Writer for writing low
 * level DXF constructs to an ASCII format DXF file.
 * 
 * @todo What if \c fname is NULL?  Or \c fname can't be opened for
 * another reason?
 */
class DL_WriterA : public DL_Writer
{
public:
	DL_WriterA(char* fname):m_ofile(fname) {};
	virtual ~DL_WriterA() {}
	void close() const;
	void dxfReal(int gc, double value) const;
	void dxfInt(int gc, int value) const;
	void dxfString(int gc, const char* value) const;

private:
	/**
	 * @brief DXF file to be created.
	 *
	 * No special handling is required in ~DL_WriterA() unless:
	 *		- local object is changed to a pointer
	 *		- the reserve area is changed from default to user-allocated
	 */
	mutable std::ofstream m_ofile;
};

#endif // !defined(DL_WRITER_ASCII_H)
