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
	ID3D11Device*			m_pDevice;				// デバイス
	ID3D11DeviceContext*	m_pDeviceContext;		// デバイスコンテキスト
	IDXGISwapChain*			m_pSwapChain;			// スワップチェイン
	ID3D11RenderTargetView* m_pRenderTargetView;	// レンダーターゲットビュー

	UINT					m_Width;				// スクリーンの横幅
	UINT					m_Height;				// スクリーンの縦幅
};