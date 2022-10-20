#pragma once

//==============================================================================
// Filename: System_Scene.h
// Description: Scene System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_DirectX11.h"
#include "System_DirectX12.h"
#include "Model_CubeDX11.h"
#include "Model_CubeDX12.h"

#include "System_Layer.h"
#include "Model_Cube.h"

enum VERSION
{
	DIRECTX11,
	DIRECTX12
};

class SystemScene
{
public:

	bool SystemInit(HWND _hwnd);

	void SystemDraw();

	void SystemRelease();
private:

	SystemDirectX11	m_DirectX11;					/// DirectX11クラス
	SystemDirectX12	m_DirectX12;					/// DirectX12クラス

	ModelCubeDX11	m_CubeDX11;						/// キューブ(DX11)クラス
	ModelCubeDX12	m_CubeDX12;						/// キューブ(DX12)クラス

	SystemLayer*	m_pLayer;						/// Layerクラス
	ModelCube*		m_pCube;						/// キューブクラス

	HWND			m_Hwnd;							/// HWND
	VERSION			m_SystemVersion = DIRECTX12;	/// 描画のバージョン
};
