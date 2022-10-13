#pragma once
//==============================================================================
// Filename: Model_CubeDX11.h
// Description: CubeClass
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(o) {if(o != NULL){o->Release();o = NULL;}else{o = NULL;}}

class ModelCubeDX11
{
public:
	// 初期化処理
	bool ModelInit(ID3D11Device* _device, ID3D11DeviceContext* _context);

	// 描画処理
	void ModelDraw();

	// 解放処理
	void ModelReleace();

private:
	ID3D11Device*				m_pDev;				/// デバイス
	ID3D11DeviceContext*		m_pContext;			/// デバイスコンテキスト
	ID3D11Buffer*				m_pVertexBuffer;	/// 頂点バッファ
	ID3D11VertexShader*			m_pVertexShader;	/// 頂点シェーダー
	ID3D11PixelShader*			m_pPixelShader;		/// ピクセルシェーダー
	ID3D11InputLayout*			m_pInputLayout;		/// インプットレイアウト

	ID3D11SamplerState*			m_pSampler;			/// サンプラー
	ID3D11Texture2D*			m_pTexture;			/// テクスチャ
	ID3D11ShaderResourceView*	m_pSRV;				/// シェーダーリソースビュー

	ID3D11Buffer*				m_pIndexBuffer;		/// インデックスバッファ
	ID3D11Buffer*				m_pConstantBuffer;	/// 定数バッファ
};
