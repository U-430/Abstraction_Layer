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
* @brief	DirectX12クラス
*/

/// <summary>
/// DirectX12クラス
/// </summary>
class SystemDirectX12 : public SystemLayer
{
public:
	//---------------------------------------------------------------------------
	// public methods
	//---------------------------------------------------------------------------

	bool SystemInit(HWND hWnd);		/// 初期化処理
	void SystemRelease();			/// 解放処理
	void SystemRender();			/// 描画処理

	// 描画前処理
	void SystemBeforeRender();
	void SystemBeforeRender(float r, float g, float b);

	void SystemAfterRender();		/// 描画後処理

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
	ID3D12Device*				m_pDevice;						/// デバイス
	ID3D12CommandQueue*			m_pQueue;						/// コマンドキュー
	IDXGISwapChain3*			m_pSwapChain;					/// スワップチェイン
	ID3D12Resource*				m_pColorBuffer[FRAME_COUNT];	/// カラーバッファ
	ID3D12CommandAllocator*		m_pCmdAllocator[FRAME_COUNT];	/// コマンドアロケータ
	ID3D12GraphicsCommandList*	m_pCmdList;						/// コマンドリスト
	ID3D12DescriptorHeap*		m_pHeadRTV;						/// ディスクリプタヒープ(レンダーターゲットビュー)
	ID3D12Fence*				m_pFence;						/// フェンス
	ID3D12Resource*				m_pDepthBuffer;					/// 深度ステンシルバッファ
	ID3D12DescriptorHeap*		m_pHeapDSV;

	HANDLE						m_FenceEvent;					/// フェンスイベント
	uint64_t					m_FenceCounter[FRAME_COUNT];	/// フェンスカウンター
	uint32_t					m_FrameIndex;					/// フレーム番号

	D3D12_CPU_DESCRIPTOR_HANDLE	m_HandleRTV[FRAME_COUNT];		/// CPUディスクリプタ(レンダーターゲットビュー)
	D3D12_CPU_DESCRIPTOR_HANDLE	m_HandleDSV;

	///<
};
