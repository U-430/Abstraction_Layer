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

	SystemDirectX11	m_DirectX11;					/// DirectX11�N���X
	SystemDirectX12	m_DirectX12;					/// DirectX12�N���X

	ModelCubeDX11	m_CubeDX11;						/// �L���[�u(DX11)�N���X
	ModelCubeDX12	m_CubeDX12;						/// �L���[�u(DX12)�N���X

	SystemLayer*	m_pLayer;						/// Layer�N���X
	ModelCube*		m_pCube;						/// �L���[�u�N���X

	HWND			m_Hwnd;							/// HWND
	VERSION			m_SystemVersion = DIRECTX12;	/// �`��̃o�[�W����
};
