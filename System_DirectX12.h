#pragma once
#include <cstdint>
#include <d3d12.h>
#include <dxgi1_4.h>

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
class SystemDirectX12 
{
public:
	bool InitDX12(HWND hWnd);		// 初期化処理
	void Release();					// 解放処理
	void Render();					// 描画処理

	// 描画前処理
	void BeforeRender();
	void BeforeRender(float r, float g, float b);

	void AfterRender();				// 描画後処理

	ID3D12Device* GetDevice();
	ID3D12CommandQueue* GetQueue();
	ID3D12GraphicsCommandList* GetCmdList();
	uint32_t GetFrameIndex();

private:
	void WaitGPU();
	void Present(uint32_t _interval);

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
};
