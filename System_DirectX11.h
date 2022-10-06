#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


class SystemDirectX11
{
public:
	bool Init(HWND hWnd);
	void BeforeRender();
	void AfterRender();
	void Release();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:
	ID3D11Device* m_pDevice;				/// �f�o�C�X
	ID3D11DeviceContext* m_pDeviceContext;		/// �f�o�C�X�R���e�L�X�g
	IDXGISwapChain* m_pSwapChain;			/// �X���b�v�`�F�C��
	ID3D11RenderTargetView* m_pRenderTargetView;	/// �����_�[�^�[�Q�b�g�r���[
	ID3D11Texture2D* m_pDepthStencilTexture;	/// 
	ID3D11DepthStencilView* m_pDepthStencilView;	/// �f�v�X�X�e���V���r���[
	ID3D11InputLayout* m_pInputLayout;			/// �C���v�b�g���C�A�E�g
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11SamplerState* m_pSamperState;
	ID3D11BlendState* m_pBlendState;
	ID3D11Buffer* m_pBuffer;

	D3D11_VIEWPORT			m_viewPort;				/// �r���[�|�[�g


	UINT					m_Width;				/// �X�N���[���̉���
	UINT					m_Height;				/// �X�N���[���̏c��
};