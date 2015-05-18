//////////////////////////////////////////////////////////////////////
// dxf_codes.h
//////////////////////////////////////////////////////////////////////

/*!
	\file dxf_codes.h
	\brief Defines common DXF codes and constants

	Oddly enough there is no standard AutoCAD
	file for these codes.

	This file started as lst__5_1.h in _Programming AutoCAD in C and C++_
*/

// Embeds version info in the executable, but does not load at run time.
#pragma comment(exestr, "$Id: dl_codes.h,v 1.2 2002/03/01 17:31:44 andrew23 Exp $")

//! If DXF_CODES_H is defined, dxf_codes.h has already been included and
//! it will not be processed again.\n
//! If DXF_CODES_H is undefined, it will be defined and dxf_codes.h will
//! be included.
#if !defined(DXF_CODES_H)
#define DXF_CODES_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class dxfConst
{
public:
	enum color
	{
		black = 255, // Is this right? I just guessed.
		green = 3,
		red = 1,
		brown = 15,
		yellow = 2,
		cyan = 4,
		magenta = 6,
		gray = 8,
		blue = 5,
		l_blue = 163,
		l_green = 121,
		l_cyan = 131,
		l_red = 23,
		l_magenta = 221,
		l_gray = 252,
		white = 7,
		bylayer = 256,
		byblock = 0
	};
};

/*************** DXF COLOR CONSTANTS ******************/
// Only the constants used by CK are defined so far
// Would be better if actual palettes could be compared,
// i.e., map one to another based on RGB content.



/*************** DXF VERSIONS ******************/
#define VER_R12    "AC1009"
#define VER_LT2    "AC1009"
#define VER_R13    "AC1012"
#define VER_LT95   "AC1012"
#define VER_R14    "AC1014"
#define VER_LT97   "AC1014"
#define VER_LT98   "AC1014"
#define VER_2000   "AC1015"
#define VER_2002   "AC1015"


/*************** DXF GROUP CODES ******************/

// Strings
#define STRGRP_START      0
#define STRGRP_END        9

// Coordinates
#define CRDGRP_START     10
#define CRDGRP_END       19

// Real values
#define RLGRP_START      38
#define RLGRP_END        59

// Short integer values
#define SHOGRP_START     60
#define SHOGRP_END       79

// New in Release 13,
#define SUBCLASS        100

// More coordinates
#define CRD2GRP_START   210
#define CRD2GRP_END     239

// Extended data strings
#define ESTRGRP_START  1000
#define ESTRGRP_END    1009

// Extended data reals
#define ERLGRP_START   1010
#define ERLGRP_END     1059


#define Y8_COORD_CODE       28
#define Z0_COORD_CODE       30
#define Z8_COORD_CODE       38

#define POINT_COORD_CODE    10
#define INSERT_COORD_CODE   10

#define CRD2GRP_START      210
#define CRD2GRP_END        239

#define THICKNESS            39
#define FIRST_REAL_CODE      THICKNESS
#define LAST_REAL_CODE       59
#define FIRST_INT_CODE       60
#define ATTFLAGS_CODE        70
#define PLINE_FLAGS_CODE     70
#define LAYER_FLAGS_CODE     70
#define FLD_LEN_CODE         73 // Inside ATTRIB resbuf
#define LAST_INT_CODE        79
#define X_EXTRU_CODE        210
#define Y_EXTRU_CODE        220
#define Z_EXTRU_CODE        230
#define COMMENT_CODE        999

// Start and endpoints of a line
#define LINE_START_CODE      10  // Followed by x coord
#define LINE_END_CODE        11  // Followed by x coord

// Some codes used by blocks
#define BLOCK_FLAGS_CODE     70  // An int containing flags
#define BLOCK_BASE_CODE      10  // Origin of block definition
#define XREF_DEPENDENT       16  // If a block contains an XREF
#define XREF_RESOLVED        32  // If a XREF resolved ok
#define REFERENCED           64  // If a block is ref'd in DWG

#define XSCALE_CODE          41
#define YSCALE_CODE          42
#define ANGLE_CODE           50
#define INS_POINT_CODE       10  // Followed by x of ins pnt
#define NAME2_CODE            3  // Second appearance of name 

// Some codes used by circle entities
#define CENTER_CODE          10  // Followed by x of center
#define RADIUS_CODE          40  // Followd by radius of circle

#define COND_OP_CODE         -4  // Conditional op,ads_ssget

// When using ads_buildlist you MUST use RTDXF0 instead of these
#define ENTITY_TYPE_CODE      0  // Then there is LINE, 3DFACE..
#define SES_CODE              0  // Start End String Code
#define FILE_SEP_CODE         0  // File separator
#define SOT_CODE              0  // Start Of Table
#define TEXTVAL_CODE          1
#define NAME_CODE             2
#define BLOCK_NAME_CODE       2
#define SECTION_NAME_CODE     2
#define ENT_HAND_CODE         5  // What follows is hexa string
#define TXT_STYLE_CODE        7  // Inside attributes
#define LAYER_NAME_CODE       8  // What follows is layer name
#define FIRST_XCOORD_CODE    10  // Group code x of 1st coord
#define FIRST_YCOORD_CODE    20  // Group code y of 1st coord
#define FIRST_ZCOORD_CODE    30  // Group code z of 1st coord
#define L_START_CODE         10
#define L_END_CODE           11
#define TXTHI_CODE           40
#define SCALE_X_CODE         41
#define SCALE_Y_CODE         42
#define SCALE_Z_CODE         43
#define BULGE_CODE           42  // Used in PLINE verts for arcs
#define ROTATION_CODE        50
#define COLOUR_CODE          62  // What follows is a color int
#define LTYPE_CODE            6  // What follows is a linetype


// Attribute flags
#define ATTS_FOLLOW_CODE     66
#define ATT_TAG_CODE          2
#define ATT_VAL_CODE          1
#define ATT_FLAGS_CODE       70  // 4 1 bit flags as follows...
#define ATT_INVIS_FLAG        1
#define ATT_CONST_FLAG        2
#define ATT_VERIFY_FLAG       4 // Prompt and verify
#define ATT_PRESET_FLAG       8 // No prompt and no verify

// PLINE defines
// Flags
#define OPEN_PLINE       0x00
#define CLOSED_PLINE     0x01
#define POLYLINE3D       0x80
#define PFACE_MESH       0x40
#define PGON_MESH        0x10
// Vertices follow entity, required in POLYLINES
#define VERTS_FOLLOW_CODE   66 // Value should always be 1
#define VERTEX_COORD_CODE   10


// LAYER flags
#define FROZEN           1
#define FROZEN_BY_DEF    2
#define LOCKED           4
#define OBJECT_USED     64   // Object is ref'd in the dwg

#define BLOCK_EN_CODE   -2   // Block entity definition 
#define E_NAME          -1   // Entity name 

// Extended data codes 
#define EXTD_SENTINEL    (-3)
#define EXTD_STR         1000
#define EXTD_APP_NAME    1001
#define EXTD_CTL_STR     1002
#define EXTD_LYR_STR     1003
#define EXTD_CHUNK       1004
#define EXTD_HANDLE      1005
#define EXTD_POINT       1010
#define EXTD_POS         1011
#define EXTD_DISP        1012
#define EXTD_DIR         1013
#define EXTD_FLOAT       1040
#define EXTD_DIST        1041
#define EXTD_SCALE       1042
#define EXTD_INT16       1070
#define EXTD_INT32       1071

// UCS codes for use in ads_trans
#define WCS_TRANS_CODE      0
#define UCS_TRANS_CODE      1
#define DCS_TRANS_CODE      2
#define PCS_TRANS_CODE      3

#endif // !defined(DXF_CODES_H)
