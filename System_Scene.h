#pragma once
//==============================================================================
// Filename: System_Scene.h
// Description: Scene System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_Layer.h"
#include "Model_Cube.h"

enum VERSION
{
	DIRECTX11,
	DIRECTX12,
	OPENGL
};

class SystemScene
{
public:

	bool SystemInit(HWND _hwnd);

	void SystemUpdate();

	void SystemDraw();

	void SystemRelease();
private:

	void SystemSwitchLayer(VERSION ver);

	SystemLayer*	m_pLayer;						/// Layerクラス
	ModelCube*		m_pCube;						/// キューブクラス

	HWND			m_Hwnd;							/// HWND
	VERSION			m_SystemVersion = OPENGL;		/// 描画のバージョン

	bool			m_KeyFlg = false;
};
