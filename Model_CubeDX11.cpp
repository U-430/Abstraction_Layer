//==============================================================================
// Filename: Model_Cube.cpp
// Description: CubeClass
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "Model_CubeDX11.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "System_ScreenSize.h"

#pragma comment (lib, "d3dcompiler.lib")

#define VERTEX_NUM 24

struct Vertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT2 tex;
};

struct ConstantBuffer
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;
};

//--------------------------------------------- 
/// \param[in] ID3D11Device*(_device)
/// \param[in] ID3D11DeviceContext*(_context)
/// 
/// \return 
//---------------------------------------------
bool ModelCubeDX11::Init(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	HRESULT hr = S_OK;

	ID3DBlob* pBlobVS = nullptr;
	ID3DBlob* pBlobPS = nullptr;
	ID3DBlob* pErrorBlob = nullptr;

	m_pDev = _device;
	m_pContext = _context;

	Vertex v[] =
	{
		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3( 0.5f, -0.5f, 0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, 0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, 0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f, 0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f, 0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f, 0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
	};

	WORD indexList[]
	{
		0, 1, 2, 3, 2, 1,
		4, 5, 6, 7, 6, 5,
		8, 9,10, 11, 10, 9,
		12, 13, 14, 15, 14, 13,
		16, 17, 18, 19, 18 ,17,
		20, 21, 22, 23, 22, 21,
	};

	// 頂点データ定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0,							   0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",	 0, DXGI_FORMAT_R32G32B32A32_FLOAT,	 0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		 0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	//頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(Vertex) * VERTEX_NUM;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = v;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	hr = m_pDev->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	// 頂点シェーダー作成
	hr = D3DCompileFromFile(L"shader/VSPSShader.hlsl", nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &pBlobVS, &pErrorBlob);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (LPCSTR)pErrorBlob->GetBufferPointer(), "Vertex Shader Erorr", MB_OK);
		return false;
	}

	hr = m_pDev->CreateVertexShader(pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), nullptr, &m_pVertexShader);
	if (FAILED(hr))
	{
		return false;
	}

	// ピクセルシェーダー生成
	hr = D3DCompileFromFile(L"shader/VSPSShader.hlsl", nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &pBlobPS, &pErrorBlob);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (LPCSTR)pErrorBlob->GetBufferPointer(), "Pixel Shader Erorr", MB_OK);
		return false;
	}

	hr = m_pDev->CreatePixelShader(pBlobPS->GetBufferPointer(), pBlobPS->GetBufferSize(), nullptr, &m_pPixelShader);
	if (FAILED(hr))
	{
		return false;
	}

	// インプットレイアウト生成
	hr = m_pDev->CreateInputLayout(layout, ARRAYSIZE(layout), pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &m_pInputLayout);

	D3D11_BUFFER_DESC ibDesc;
	ibDesc.ByteWidth = sizeof(WORD) * 6 * 6;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA irData;
	irData.pSysMem = indexList;
	irData.SysMemPitch = 0;
	irData.SysMemSlicePitch = 0;

	hr = m_pDev->CreateBuffer(&ibDesc, &irData, &m_pIndexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	// 定数バッファ生成
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = m_pDev->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	// 行列計算
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(2.0f, 2.0f, -5.0f, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eye, focus, up);

	constexpr float    fov = DirectX::XMConvertToRadians(45.0f);
	float    aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	// 定数バッファ更新
	ConstantBuffer cb;
	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(worldMatrix));
	DirectX::XMStoreFloat4x4(&cb.view, DirectX::XMMatrixTranspose(viewMatrix));
	DirectX::XMStoreFloat4x4(&cb.proj, DirectX::XMMatrixTranspose(projMatrix));
	m_pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);


	// サンプラー設定
	D3D11_SAMPLER_DESC smpDesc;

	ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = m_pDev->CreateSamplerState(&smpDesc, &m_pSampler);
	if (FAILED(hr))
	{
		return false;
	}

	// テクスチャ生成
	const int k_PixSize = 32;//縦横ピクセル数

	D3D11_TEXTURE2D_DESC td;

	td.Width = k_PixSize;
	td.Height = k_PixSize;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DYNAMIC;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	td.MiscFlags = 0;
	hr = m_pDev->CreateTexture2D(&td, nullptr, &m_pTexture);
	if (FAILED(hr))
	{
		return false;
	}

	//テクスチャ書き替え
	D3D11_MAPPED_SUBRESOURCE msr;
	m_pContext->Map(m_pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	byte srcData[k_PixSize * k_PixSize * 4] = { 1 };//ビットマップを白で初期化
	for (int i = 0; i < k_PixSize * k_PixSize * 4; i += 4)
	{
		srcData[i] = 0; // 赤
		srcData[i + 1] = 1; // 緑
		srcData[i + 2] = 1; // 青
	}
	memcpy(msr.pData, srcData, sizeof(srcData));

	m_pContext->Unmap(m_pTexture, 0);

	// シェーダーリソースビュー生成
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = m_pDev->CreateShaderResourceView(m_pTexture, &srv, &m_pSRV);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeDX11::Draw()
{
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	// ポリゴン
	m_pContext->IASetInputLayout(m_pInputLayout);
	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// バッファ
	m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// テクスチャ
	m_pContext->PSSetShaderResources(0, 1, &m_pSRV);
	m_pContext->PSSetSamplers(0, 1, &m_pSampler);

	// シェーダー
	m_pContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pContext->PSSetShader(m_pPixelShader, NULL, 0);

	// 描画
	//m_pContext->Draw(VERTEX_NUM, 0);
	m_pContext->DrawIndexed(6 * 6, 0, 0);
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeDX11::Releace()
{
	SAFE_RELEASE(m_pSampler);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSRV);
	SAFE_RELEASE(m_pIndexBuffer);
}
