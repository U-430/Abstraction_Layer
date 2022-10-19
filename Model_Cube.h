#pragma once

#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_RELEASE(o) {if(o != NULL){o->Release();o = NULL;}else{o = NULL;}}
#define VERTEX_NUM 24
#define INDEX_NUM 36

struct Vertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT2 tex;
};

class ModelCube
{
public:
	virtual bool ModelInit(ID3D11Device* _device, ID3D11DeviceContext* _context) { return true; };

	virtual bool ModelInit(ID3D12Device* device, ID3D12GraphicsCommandList* cmd) { return true; };

	virtual void ModelDraw() {};

	virtual void ModelRelease() {};

private:
	Vertex v[VERTEX_NUM] =
	{
		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
	};

	WORD indexList[INDEX_NUM] = 
	{
		0, 1, 2, 3, 2, 1,
		4, 5, 6, 7, 6, 5,
		8, 9,10, 11, 10, 9,
		12, 13, 14, 15, 14, 13,
		16, 17, 18, 19, 18 ,17,
		20, 21, 22, 23, 22, 21,
	};
};
