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
	DIRECTX12,
	OPENGL
};

class SystemScene
{
public:

	bool SystemInit(HWND _hwnd);

	void SystemDraw();

	void SystemRelease();
private:

	SystemLayer*	m_pLayer;						/// Layer�N���X
	ModelCube*		m_pCube;						/// �L���[�u�N���X

	HWND			m_Hwnd;							/// HWND
	VERSION			m_SystemVersion = DIRECTX12;	/// �`��̃o�[�W����
};
