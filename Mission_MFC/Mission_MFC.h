
// Mission_MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMissionMFCApp:
// See Mission_MFC.cpp for the implementation of this class
//

class CMissionMFCApp : public CWinApp
{
public:
	CMissionMFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMissionMFCApp theApp;
