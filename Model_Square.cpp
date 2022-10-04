#include "Model_Square.h"
#include <d3dcompiler.h>

#pragma comment (lib, "d3dcompiler.lib")

void Square::Init(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	HRESULT hr = S_OK;

	// 頂点データ定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",	 0, DXGI_FORMAT_R32G32B32A32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	unsigned int numElement = ARRAYSIZE(layout);

	ID3DBlob* pBlobVS = nullptr;

	m_pDev = _device;
	m_pContext = _context;

	// 頂点シェーダー作成
	hr = D3DCompileFromFile(L"shader/VS.hlsl", nullptr, nullptr, "main", "vs_5_0", 0, 0, &pBlobVS, nullptr);
	if (FAILED(hr))
	{
		pBlobVS->Release();
	}

	hr = m_pDev->CreateVertexShader(pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), nullptr, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		pBlobVS->Release();
	}
}

void Square::Draw()
{
	UINT strides = sizeof(squareVertex);
	UINT offset = 0;

	m_pContext->PSSetShaderResources(0, 1, &m_pSRV);

	m_pContext->Draw(8, 0);
}

void Square::Release()
{
}
