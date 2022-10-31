#pragma once
//==============================================================================
// Filename: System_Layer.h
// Description: Layer System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <Windows.h>
#define SAFE_RELEASE(o) {if(o != NULL){o->Release();o = NULL;}else{o = NULL;}}

class SystemLayer
{
public:
	//---------------------------------------------------------------------------
	// public methods
	//---------------------------------------------------------------------------

	/// ����������
	virtual bool SystemInit() { return true; };
	virtual bool SystemInit(HWND _hwnd) { return true; };

	/// �`��O����
	virtual void SystemBeforeRender() {};
	virtual void SystemBeforeRender(float r, float g, float b, float a) {};

	/// �`��㏈��
	virtual void SystemAfterRender() {};

	/// �������
	virtual void SystemRelease() {};

	///<
};
