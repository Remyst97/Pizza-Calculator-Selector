
// Pizza_Calc_Select.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Pizza_Calculator:
// See Pizza_Calc_Select.cpp for the implementation of this class
//

class Pizza_Calculator : public CWinApp
{
public:
	Pizza_Calculator();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Pizza_Calculator theApp;
