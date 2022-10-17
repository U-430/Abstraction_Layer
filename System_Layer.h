#pragma once
//==============================================================================
// Filename: System_DirectX12.h
// Description: DirectX12 System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_DirectX11.h"
#include "System_DirectX12.h"

enum VERSION
{
	DIRECTX11,
	DIRECTX12
};

class SystemLayer
{
public:

	void Init(HWND _hwnd);

	void Draw();

	void Release();
private:

	SystemDirectX11	m_DirectX11;		/// DirectX11クラス
	SystemDirectX12	m_DirectX12;		/// DirectX12クラス

	HWND			m_Hwnd;				/// HWND
	VERSION			m_SystemVersion;	/// 描画のバージョン
};
