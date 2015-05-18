/**
 * @file dl_writer_ascii.cpp
 * @brief 
 */
/*
	This is part of the dxflib library.
	Copyright (C) 2001-2002 Robert J. Campbell Jr.
	
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
#pragma comment(exestr, "$Id: dl_writer_ascii.cpp,v 1.4 2002/03/10 01:50:14 andrew23 Exp $")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dl_writer_ascii.h"
#include "dl_exception.h"

//////////////////////////////////////////////////////////////////////
// DL_WriterA
//////////////////////////////////////////////////////////////////////

void DL_WriterA::close() const
{
	m_ofile.close();
}

void DL_WriterA::dxfReal(int gc, double value) const
{
	// Add code to check for valid group code
	// Select for debug only
	//m_ofile << gc << "\n" << value << "\n";
	m_ofile << (gc<10 ? "  " : (gc<100 ? " " : "")) << gc << "\n" << value << "\n";
}



void DL_WriterA::dxfInt(int gc, int value) const
{
	// Add code to check for valid group code
	//m_ofile << gc << "\n" << value << "\n";
	m_ofile << (gc<10 ? "  " : (gc<100 ? " " : "")) << gc << "\n" << value << "\n";
}



void DL_WriterA::dxfString(int gc, const char* value) const
{
	if (!value) throw DL_NullStrExc();
	//m_ofile << gc << "\n" << value << "\n";
	m_ofile << (gc<10 ? "  " : (gc<100 ? " " : "")) << gc << "\n" << value << "\n";
}

