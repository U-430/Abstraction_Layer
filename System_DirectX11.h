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

	ID3D11Device*			m_pDevice;				/// �f�o�C�X
	ID3D11DeviceContext*	m_pDeviceContext;		/// �f�o�C�X�R���e�L�X�g
	IDXGISwapChain*			m_pSwapChain;			/// �X���b�v�`�F�C��
	ID3D11RenderTargetView* m_pRenderTargetView;	/// �����_�[�^�[�Q�b�g�r���[
	ID3D11Texture2D*		m_pDepthStencilTexture;	/// 
	ID3D11DepthStencilView* m_pDepthStencilView;	/// �f�v�X�X�e���V���r���[
	ID3D11InputLayout*		m_pInputLayout;			/// �C���v�b�g���C�A�E�g
	ID3D11RasterizerState*  m_pRRS;					/// ���X�^���C�U

	D3D11_VIEWPORT			m_ViewPort;				/// �r���[�|�[�g


	UINT					m_Width;				/// �X�N���[���̉���
	UINT					m_Height;				/// �X�N���[���̏c��

	///<
};