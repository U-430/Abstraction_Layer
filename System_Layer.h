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

	SystemDirectX11	m_DirectX11;					/// DirectX11�N���X
	SystemDirectX12	m_DirectX12;					/// DirectX12�N���X

	ModelCubeDX11	m_CubeDX11;						/// �L���[�u(DX11)�N���X
	ModelCubeDX12	m_CubeDX12;						/// �L���[�u(DX12)�N���X

	HWND			m_Hwnd;							/// HWND
	VERSION			m_SystemVersion = DIRECTX11;	/// �`��̃o�[�W����
};
