//////////////////////////////////////////////////////////////////////
// dl_exception.h
//////////////////////////////////////////////////////////////////////

/*!
	\file dl_exception.h
	\brief Defines conversation bar class interfaces

*/

// Embeds version info in the executable, but does not load at run time.
#pragma comment(exestr, "$Id: dl_exception.h,v 1.1 2002/01/18 00:35:58 rjcjr9 Exp $")

//! If DL_EXCEPTION_H is defined, dl_exception.h has already been included and it will
//! not be processed again.\n
//! If DL_EXCEPTION_H is undefined, it will be defined and dl_exception.h will be
//! included.
#if !defined(DL_EXCEPTION_H)
#define DL_EXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// ClassName
//////////////////////////////////////////////////////////////////////

//! Brief class description
/*!
	Long class description
*/
class DL_Exception {};
class DL_NullStrExc : public DL_Exception {};

class DL_GroupCodeExc : public DL_Exception
{
	DL_GroupCodeExc(int gc=0) : groupCode(gc) {}
	int groupCode;
};
#endif // !defined(DL_EXCEPTION_H)
