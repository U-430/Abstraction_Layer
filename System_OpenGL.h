#pragma once
//==============================================================================
// Filename: System_OpenGL.h
// Description: OpenGL System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_Layer.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

class SystemOpenGL : public SystemLayer
{
public:
	//---------------------------------------------------------------------------
	// public methods
	//---------------------------------------------------------------------------
	bool SystemInit(HWND _hwnd);

	void SystemBeforeRender();

	void SystemAfterRender();

	void SystemRelease();

	///<
private:
	//---------------------------------------------------------------------------
	// private variables
	//---------------------------------------------------------------------------

	HWND	m_HWND;	/// ウィンドウハンドル
	HDC		m_HDC;	/// デバイスコンテキスト
	HGLRC	m_HRC;	/// レンダリングコンテキスト

	///<
};
