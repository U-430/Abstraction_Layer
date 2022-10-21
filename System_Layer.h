#pragma once
//==============================================================================
// Filename: System_Layer.h
// Description: Layer System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <Windows.h>

class SystemLayer
{
public:
	/// ‰Šú‰»ˆ—
	virtual bool SystemInit() { return true; };
	virtual bool SystemInit(HWND _hwnd) { return true; };

	/// •`‰æ‘Oˆ—
	virtual void SystemBeforeRender() {};
	virtual void SystemBeforeRender(float r, float g, float b, float a) {};

	/// •`‰æŒãˆ—
	virtual void SystemAfterRender() {};

	/// ‰ğ•úˆ—
	virtual void SystemRelease() {};
};
