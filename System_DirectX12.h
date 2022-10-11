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
* @brief	DirectX12�N���X
*/

/// <summary>
/// DirectX12�N���X
/// </summary>
class SystemDirectX12 
{
public:
	bool InitDX12(HWND hWnd);		// ����������
	void Release();					// �������
	void Render();					// �`�揈��

	// �`��O����
	void BeforeRender();
	void BeforeRender(float r, float g, float b);

	void AfterRender();				// �`��㏈��

	ID3D12Device* GetDevice();
	ID3D12CommandQueue* GetQueue();
	ID3D12GraphicsCommandList* GetCmdList();
	uint32_t GetFrameIndex();

private:
	void WaitGPU();
	void Present(uint32_t _interval);

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
};
