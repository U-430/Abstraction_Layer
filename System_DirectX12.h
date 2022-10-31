#pragma once
//==============================================================================
// Filename: System_DirectX12.h
// Description: DirectX12 System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <cstdint>
#include <d3d12.h>
#include <dxgi1_4.h>
#include "System_Layer.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define FRAME_COUNT 2

/**
* @file		DirectX12.h
* @brief	DirectX12�N���X
*/

/// <summary>
/// DirectX12�N���X
/// </summary>
class SystemDirectX12 : public SystemLayer
{
public:
	//---------------------------------------------------------------------------
	// public methods
	//---------------------------------------------------------------------------

	bool SystemInit(HWND hWnd);		/// ����������
	void SystemRelease();			/// �������
	void SystemRender();			/// �`�揈��

	// �`��O����
	void SystemBeforeRender();
	void SystemBeforeRender(float r, float g, float b);

	void SystemAfterRender();		/// �`��㏈��

	ID3D12Device*				SystemGetDevice();
	ID3D12CommandQueue*			SystemGetQueue();
	ID3D12GraphicsCommandList*	SystemGetCmdList();
	uint32_t					SystemGetFrameIndex();

	///<
private:
	//---------------------------------------------------------------------------
	// private methods
	//---------------------------------------------------------------------------
	void SystemWaitGPU();
	void SystemPresent(uint32_t _interval);

	//---------------------------------------------------------------------------
	// private variables
	//---------------------------------------------------------------------------
	ID3D12Device*				m_pDevice;						/// �f�o�C�X
	ID3D12CommandQueue*			m_pQueue;						/// �R�}���h�L���[
	IDXGISwapChain3*			m_pSwapChain;					/// �X���b�v�`�F�C��
	ID3D12Resource*				m_pColorBuffer[FRAME_COUNT];	/// �J���[�o�b�t�@
	ID3D12CommandAllocator*		m_pCmdAllocator[FRAME_COUNT];	/// �R�}���h�A���P�[�^
	ID3D12GraphicsCommandList*	m_pCmdList;						/// �R�}���h���X�g
	ID3D12DescriptorHeap*		m_pHeadRTV;						/// �f�B�X�N���v�^�q�[�v(�����_�[�^�[�Q�b�g�r���[)
	ID3D12Fence*				m_pFence;						/// �t�F���X
	ID3D12Resource*				m_pDepthBuffer;					/// �[�x�X�e���V���o�b�t�@
	ID3D12DescriptorHeap*		m_pHeapDSV;

	HANDLE						m_FenceEvent;					/// �t�F���X�C�x���g
	uint64_t					m_FenceCounter[FRAME_COUNT];	/// �t�F���X�J�E���^�[
	uint32_t					m_FrameIndex;					/// �t���[���ԍ�

	D3D12_CPU_DESCRIPTOR_HANDLE	m_HandleRTV[FRAME_COUNT];		/// CPU�f�B�X�N���v�^(�����_�[�^�[�Q�b�g�r���[)
	D3D12_CPU_DESCRIPTOR_HANDLE	m_HandleDSV;

	///<
};
