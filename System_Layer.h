#pragma once
//==============================================================================
// Filename: System_DirectX12.h
// Description: DirectX12 System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <Windows.h>

class SystemLayer
{
public:

	virtual bool SystemInit() { return true; };

	virtual bool SystemInit(HWND _hwnd) { return true; };

	virtual void SystemBeforeRender() {};

	virtual void SystemBeforeRender(float r, float g, float b, float a) {};

	virtual void SystemAfterRender() {};

	virtual void SystemRelease() {};
};
