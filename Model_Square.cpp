#include "Model_Square.h"
#include <d3dcompiler.h>
#include <string>

#pragma comment (lib, "d3dcompiler.lib")

#define VERTEX_NUM 3

void Square::Init(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	HRESULT hr = S_OK;

	squareVertex vertex[] =
	{
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 1.0f, -1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f,  1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//{DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},

		//{DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//{DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//{DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//{DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
	};

	// 頂点データ定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",	 0, DXGI_FORMAT_R32G32B32A32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	unsigned int numElement = ARRAYSIZE(layout);

	ID3DBlob* pBlobVS = nullptr;
	ID3DBlob* pBlobPS = nullptr;
	ID3DBlob* pErorrMsg = nullptr;

	m_pDev = _device;
	m_pContext = _context;

	// 頂点シェーダー作成
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(L"shader/VS.hlsl", nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &pBlobVS, &errorBlob);
	if (FAILED(hr))
	{
		//pBlobVS->Release();
		//MessageBoxA(NULL, (LPCSTR)pErorrMsg->GetBufferPointer(), "Shader Erorr", MB_OK);
		std::string errorStr;
		errorStr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errorStr.begin());
	}

	hr = m_pDev->CreateVertexShader(pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), nullptr, &m_pVertexShader);
	if (FAILED(hr))
	{
		//pBlobVS->Release();
		MessageBoxA(NULL, "", "Shader Erorr", MB_OK);
	}

	// ピクセルシェーダー作成
	hr = D3DCompileFromFile(L"shader/VS.hlsl", nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &pBlobPS, &errorBlob);
	if (FAILED(hr))
	{
		//pBlobPS->Release();
		MessageBoxA(NULL, "", "Shader Erorr", MB_OK);
		std::string errorStr;
		errorStr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errorStr.begin());
	}

	hr = m_pDev->CreatePixelShader(pBlobPS->GetBufferPointer(), pBlobPS->GetBufferSize(), nullptr, &m_pPixelShader);
	if (FAILED(hr))
	{
		pBlobPS->Release();
		MessageBoxA(NULL, "", "Shader Erorr", MB_OK);
	}

	// 頂点バッファ生成
	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(vbDesc));

	vbDesc.ByteWidth = sizeof(squareVertex) * VERTEX_NUM;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertex;

	hr = m_pDev->CreateBuffer(&vbDesc, &initData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "", "Shader Erorr", MB_OK);
	}

	// 頂点レイアウト生成
	hr = m_pDev->CreateInputLayout(layout, numElement, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &m_pInputLayout);

	// インデックスバッファ生成
	D3D11_BUFFER_DESC ibDesc;
	ZeroMemory(&ibDesc, sizeof(ibDesc));

	ibDesc.ByteWidth = 3;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibDesc.Usage = D3D11_USAGE_DYNAMIC;

	hr = m_pDev->CreateBuffer(&ibDesc, &initData, &m_pIndexBuffer);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "", "Shader Erorr", MB_OK);
	}

	// 定数バッファ生成
	D3D11_BUFFER_DESC cdDesc;

	cdDesc.ByteWidth = sizeof(constantBuffer);
	cdDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cdDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cdDesc.Usage = D3D11_USAGE_DYNAMIC;
}

void Square::Draw()
{
	UINT strides = sizeof(squareVertex);
	UINT offset = 0;

	m_pContext->IASetInputLayout(m_pInputLayout);
	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offset);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_pContext->VSSetShader(m_pVertexShader, 0, 0);
	m_pContext->PSSetShader(m_pPixelShader, 0, 0);

	//m_pContext->DrawIndexed(3, 0, 0);
	m_pContext->Draw(VERTEX_NUM, 0);
}

void Square::Release()
{
	m_pIndexBuffer->Release();
	m_pIndexBuffer = nullptr;

	m_pInputLayout->Release();
	m_pInputLayout = nullptr;

	m_pPixelShader->Release();
	m_pPixelShader = nullptr;

	m_pVertexBuffer->Release();
	m_pVertexBuffer = nullptr;

	m_pVertexShader->Release();
	m_pVertexShader = nullptr;
}
