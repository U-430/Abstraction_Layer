#pragma once
//==============================================================================
// Filename: System_DirectX11.h
// Description: DirectX11 System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_Layer.h"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


class SystemDirectX11 : public SystemLayer
{
public:
	//---------------------------------------------------------------------------
	// public methods
	//---------------------------------------------------------------------------

	bool SystemInit(HWND hWnd);
	void SystemBeforeRender();
	void SystemAfterRender();
	void SystemRelease();

	ID3D11Device* SystemGetDevice();
	ID3D11DeviceContext* SystemGetDeviceContext();

	///<
private:
	//---------------------------------------------------------------------------
	// private variables
	//---------------------------------------------------------------------------

	ID3D11Device*			m_pDevice;				/// デバイス
	ID3D11DeviceContext*	m_pDeviceContext;		/// デバイスコンテキスト
	IDXGISwapChain*			m_pSwapChain;			/// スワップチェイン
	ID3D11RenderTargetView* m_pRenderTargetView;	/// レンダーターゲットビュー
	ID3D11Texture2D*		m_pDepthStencilTexture;	/// 
	ID3D11DepthStencilView* m_pDepthStencilView;	/// デプスステンシルビュー
	ID3D11InputLayout*		m_pInputLayout;			/// インプットレイアウト
	ID3D11RasterizerState*  m_pRRS;					/// ラスタライザ

	D3D11_VIEWPORT			m_ViewPort;				/// ビューポート


	UINT					m_Width;				/// スクリーンの横幅
	UINT					m_Height;				/// スクリーンの縦幅

	///<
};