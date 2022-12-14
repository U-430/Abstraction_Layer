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

	/// 初期化処理
	virtual bool SystemInit() { return true; };
	virtual bool SystemInit(HWND _hwnd) { return true; };

	/// 描画前処理
	virtual void SystemBeforeRender() {};
	virtual void SystemBeforeRender(float r, float g, float b, float a) {};

	/// 描画後処理
	virtual void SystemAfterRender() {};

	/// 解放処理
	virtual void SystemRelease() {};

	///<
};
