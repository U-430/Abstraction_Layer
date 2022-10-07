#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(o) {if(o != NULL){o->Release();o = NULL;}else{o = NULL;}}

class ModelCube
{
public:

	bool Init(ID3D11Device* _device, ID3D11DeviceContext* _context);

	void Draw();

	void Releace();

private:
	ID3D11Device* m_pDev;
	ID3D11DeviceContext* m_pContext;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pInputLayout;

	ID3D11SamplerState* m_pSampler;
	ID3D11Texture2D* m_pTexture;
	ID3D11ShaderResourceView* m_pSRV;

	ID3D11Buffer* m_pConstantBuffer;
};
