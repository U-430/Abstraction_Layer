#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")

struct squareVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

class Square
{
public:
	void Init(ID3D11Device* _device, ID3D11DeviceContext* _context);
	void Draw();
	void Release();

private:
	squareVertex				m_Vertex;			/// 頂点データ
	ID3D11Buffer*				m_pVertexBuffer;	/// 頂点バッファ
	ID3D11Buffer*				m_pIndexBuffer;		/// インデックスバッファ
	ID3D11VertexShader*			m_pVertexShader;	/// 頂点シェーダー
	ID3D11PixelShader*			m_pPixelShader;		/// ピクセルシェーダー	
	ID3D11InputLayout*			m_pInputLayout;		/// 頂点レイアウト

	ID3D11Device*				m_pDev;
	ID3D11DeviceContext*		m_pContext;
};
