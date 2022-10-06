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
	ID3D11Device* m_pDevice;				/// デバイス
	ID3D11DeviceContext* m_pDeviceContext;		/// デバイスコンテキスト
	IDXGISwapChain* m_pSwapChain;			/// スワップチェイン
	ID3D11RenderTargetView* m_pRenderTargetView;	/// レンダーターゲットビュー
	ID3D11Texture2D* m_pDepthStencilTexture;	/// 
	ID3D11DepthStencilView* m_pDepthStencilView;	/// デプスステンシルビュー
	ID3D11InputLayout* m_pInputLayout;			/// インプットレイアウト
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11SamplerState* m_pSamperState;
	ID3D11BlendState* m_pBlendState;
	ID3D11Buffer* m_pBuffer;

	D3D11_VIEWPORT			m_viewPort;				/// ビューポート


	UINT					m_Width;				/// スクリーンの横幅
	UINT					m_Height;				/// スクリーンの縦幅
};