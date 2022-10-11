#pragma once
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "System_DirectX12.h"

template<typename T>
struct ConstantBufferView
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC Desc;		// 定数バッファの構成設定
	D3D12_CPU_DESCRIPTOR_HANDLE		HandleCPU;	// CPUディスクリプタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE		HandleGPU;	// GPUディスクリプタハンドル
	T*								pBuffer;	// バッファ先頭へのポインタ
};

struct alignas(256) Transform
{
	DirectX::XMMATRIX World;	// ワールド行列
	DirectX::XMMATRIX View;		// ビュー行列
	DirectX::XMMATRIX Proj;		// 射影行列
};

class Square 
{
public:
	bool Init(ID3D12Device* device, ID3D12GraphicsCommandList* cmd, uint32_t frameindex);	// 初期化処理
	void Update();	// 更新処理
	void Draw();	// 描画処理
	void Release();	// 解放処理

	void SetPos(float x);

private:
	ID3D12DescriptorHeap*	m_pHeapCBV;			/// ディスクリプタヒープ(定数バッファービュー等)
	ID3D12Resource*			m_pIB;				/// インデックスバッファ
	ID3D12Resource*			m_pVB;				/// 頂点バッファ
	ID3D12Resource*			m_pCB[FRAME_COUNT];	/// 定数バッファ
	ID3D12RootSignature*	m_pRootSignature;	/// ルートシグネイチャ
	ID3D12PipelineState*	m_pPSO;				/// パイプラインステート

	ID3D12Device*				m_pDev;				/// デバイス
	ID3D12GraphicsCommandList*	m_pCmd;				/// コマンドリスト
	uint32_t					m_FrameIndex;		/// フレーム番号

	D3D12_INDEX_BUFFER_VIEW			m_IBV;				/// インデックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW		m_VBV;				/// 頂点バッファビュー
	D3D12_VIEWPORT					m_Viewport;			/// ビューポート
	D3D12_RECT						m_Scissor;			/// シザー矩形
	ConstantBufferView<Transform>	m_CBV[FRAME_COUNT];	/// 定数バッファビュー
	float							m_RotateAngle;		/// 回転角
};