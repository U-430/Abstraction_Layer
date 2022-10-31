#pragma once
//==============================================================================
// Filename: Model_CubeDX11.h
// Description: CubeClass for DirectX11
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_DirectX11.h"
#include "Model_Cube.h"


class ModelCubeDX11 : public ModelCube
{
public:
	//---------------------------------------------------------------------------
	// public methods
	//---------------------------------------------------------------------------

	// 初期化処理
	bool ModelInit(SystemLayer* layer);

	// 描画処理
	void ModelDraw();

	// 解放処理
	void ModelReleace();

	///<
private:
	//---------------------------------------------------------------------------
	// private variables
	//---------------------------------------------------------------------------

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
	///<
};
