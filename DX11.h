#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

class DirectX11
{
public:
	bool Init(HWND hWnd);
	void BeforeRender();
	void AfterRender();
	void Release();

private:
	ID3D11Device*			m_pDevice;				// �f�o�C�X
	ID3D11DeviceContext*	m_pDeviceContext;		// �f�o�C�X�R���e�L�X�g
	IDXGISwapChain*			m_pSwapChain;			// �X���b�v�`�F�C��
	ID3D11RenderTargetView* m_pRenderTargetView;	// �����_�[�^�[�Q�b�g�r���[

	UINT					m_Width;				// �X�N���[���̉���
	UINT					m_Height;				// �X�N���[���̏c��
};