
#pragma once

#define WIN32_LEAN_AND_MEAN
#define WINVER		 0x0601 // _WIN32_WINNT_WIN7
#define _WIN32_WINNT 0x0601
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tchar.h>
#include <math.h>
#include <crtdbg.h>
#include <intrin.h>

#pragma intrinsic(memset, memcpy, strcat, strcmp, strcpy, strlen, abs, fabs, labs, atan, atan2, tan, sqrt, sin, cos)

// IDA libs
#define USE_DANGEROUS_FUNCTIONS
#define USE_STANDARD_FILE_FUNCTIONS
#define NO_OBSOLETE_FUNCS
#include <ida.hpp>
#include <auto.hpp>
#include <loader.hpp>
#include <search.hpp>
#pragma warning(push)
#pragma warning(disable:4267) // "conversion from 'size_t' to 'xxx', possible loss of data"
#include <typeinf.hpp>
#pragma warning(pop)
#include <struct.hpp>
#include <nalt.hpp>
#include <demangle.hpp>

// Qt libs
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtGui/QApplication>
#include <QtGui/QProgressDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QHeaderView>
#include <QtGui/QScrollBar>
// (IDA SDK)\lib\x86_win_qt
#pragma comment(lib, "QtCore4.lib")
#pragma comment(lib, "QtGui4.lib")
#pragma comment(lib, "QtXml4.lib")

#include <Utility.h>
#include "undname.h"

#include <unordered_set>
#include <unordered_map>

typedef qlist<ea_t> eaList;
typedef std::unordered_set<ea_t> eaSet;
typedef std::unordered_map<ea_t, UINT> eaRefMap;
struct earef
{
    ea_t ea;
    UINT refs;
};
typedef qlist<earef> eaRefList;


// Get IDA 32 bit value with verification
template <class T> BOOL getVerify32_t(ea_t eaPtr, T &rValue)
{
	// Location valid?
    if (isLoaded(eaPtr))
	{
		// Get 32bit value
		rValue = (T) get_32bit(eaPtr);
		return(TRUE);
	}

	return(FALSE);
}

// Get address/pointer value
inline ea_t getEa(ea_t ea)
{
    #ifndef __EA64__
    return((ea_t) get_32bit(ea));
    #else
    return((ea_t) get_64bit(ea));
    #endif
}


// Returns TRUE if ea_t sized value flags
inline BOOL isEa(flags_t f)
{
    #ifndef __EA64__
    return(isDwrd(f));
    #else
    return(isQwrd(f));
    #endif
}


#define STYLE_PATH ":/classinf/"

#define MY_VERSION MAKEWORD(2, 2) // Low, high, convention: 0 to 99
