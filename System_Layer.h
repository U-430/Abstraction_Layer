#pragma once
//==============================================================================
// Filename: System_DirectX12.h
// Description: DirectX12 System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_DirectX11.h"
#include "System_DirectX12.h"
#include "Model_CubeDX11.h"
#include "Model_CubeDX12.h"

enum VERSION
{
	DIRECTX11,
	DIRECTX12
};

class SystemLayer
{
public:

	bool Init(HWND _hwnd);

	void Draw();

	void Release();
private:

	SystemDirectX11	m_DirectX11;					/// DirectX11クラス
	SystemDirectX12	m_DirectX12;					/// DirectX12クラス

	ModelCubeDX11	m_CubeDX11;						/// キューブ(DX11)クラス
	ModelCubeDX12	m_CubeDX12;						/// キューブ(DX12)クラス

	HWND			m_Hwnd;							/// HWND
	VERSION			m_SystemVersion = DIRECTX11;	/// 描画のバージョン
};
