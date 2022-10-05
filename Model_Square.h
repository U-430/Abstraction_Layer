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
	squareVertex				m_Vertex;			/// ���_�f�[�^
	ID3D11Buffer*				m_pVertexBuffer;	/// ���_�o�b�t�@
	ID3D11Buffer*				m_pIndexBuffer;		/// �C���f�b�N�X�o�b�t�@
	ID3D11VertexShader*			m_pVertexShader;	/// ���_�V�F�[�_�[
	ID3D11PixelShader*			m_pPixelShader;		/// �s�N�Z���V�F�[�_�[	
	ID3D11InputLayout*			m_pInputLayout;		/// ���_���C�A�E�g

	ID3D11Device*				m_pDev;
	ID3D11DeviceContext*		m_pContext;
};
