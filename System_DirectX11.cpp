//==============================================================================
// Filename: System_DirectX11.cpp
// Description: DirectX11 System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_DirectX11.h"

//--------------------------------------------- 
/// \brief DirectX11の初期化 
/// \param[in] HWND (hWnd) ウインドウハンドル
/// 
/// \return 
//---------------------------------------------
bool SystemDirectX11::SystemInit(HWND hWnd)
{
    HRESULT  hr;
    RECT rect;

    UINT flags = 0;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL level;

    GetClientRect(hWnd, &rect);

    m_Width = (UINT)(rect.right - rect.left);
    m_Height = (UINT)(rect.bottom - rect.top);

    DXGI_SWAP_CHAIN_DESC scDesc;
    ZeroMemory(&scDesc, sizeof(scDesc));
    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Width = m_Width;
    scDesc.BufferDesc.Height = m_Height;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = hWnd;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.Windowed = TRUE;

    hr = D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        pLevels,
        1,
        D3D11_SDK_VERSION,
        &scDesc,
        &m_pSwapChain,
        &m_pDevice,
        &level,
        &m_pDeviceContext);
    if (FAILED(hr))
    {
        return false;
    }


    ID3D11Texture2D* pBackBuffer;

    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
    {
        return false;
    }

    //ビューポート設定
    m_ViewPort.TopLeftX = 0;
    m_ViewPort.TopLeftY = 0;
    m_ViewPort.Width = (FLOAT)m_Width;
    m_ViewPort.Height = (FLOAT)m_Height;
    m_ViewPort.MinDepth = 0.0f;
    m_ViewPort.MaxDepth = 1.0f;

    // 深度ステンシルバッファ
    D3D11_TEXTURE2D_DESC txDesc;
    ZeroMemory(&txDesc, sizeof(txDesc));
    txDesc.Width = m_Width;
    txDesc.Height = m_Height;
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    txDesc.SampleDesc.Count = 1;
    txDesc.SampleDesc.Quality = 0;
    txDesc.Usage = D3D11_USAGE_DEFAULT;
    txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    txDesc.CPUAccessFlags = 0;
    txDesc.MiscFlags = 0;
    hr = m_pDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilTexture);
    if (FAILED(hr))
    {
        return false;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.Format = txDesc.Format;
    dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsDesc.Texture2D.MipSlice = 0;

    hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsDesc, &m_pDepthStencilView);
    if (FAILED(hr))
    {
        return false;
    }

    D3D11_RASTERIZER_DESC ras = {};
    ras.FillMode = D3D11_FILL_SOLID;
    ras.CullMode = D3D11_CULL_NONE;
    hr = m_pDevice->CreateRasterizerState(&ras, &m_pRRS);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

//--------------------------------------------- 
/// \brief DirectX11の描画前処理
/// \return 無し
//---------------------------------------------
void SystemDirectX11::SystemBeforeRender()
{
    float clearColor[4] = { 0.75f, 0.75f, 0.75f, 1.0f }; //red,green,blue,alpha

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
    m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    m_pDeviceContext->RSSetViewports(1, &m_ViewPort);
    m_pDeviceContext->RSSetState(m_pRRS);
}

//--------------------------------------------- 
/// \brief DirectX11の描画後処理
/// \return 無し
//---------------------------------------------
void SystemDirectX11::SystemAfterRender()
{
    m_pSwapChain->Present(0, 0);
}

//--------------------------------------------- 
/// \brief DirectX11の解放処理
/// \return 無し
//---------------------------------------------
void SystemDirectX11::SystemRelease()
{
    SAFE_RELEASE(m_pDepthStencilTexture);
    SAFE_RELEASE(m_pDepthStencilView);
    SAFE_RELEASE(m_pRenderTargetView);
    SAFE_RELEASE(m_pRRS);
    SAFE_RELEASE(m_pInputLayout);
    SAFE_RELEASE(m_pSwapChain);
    SAFE_RELEASE(m_pDeviceContext);
    SAFE_RELEASE(m_pDevice);
}

//---------------------------------------------
/// \brief ID3D11Deviceを取得
/// \return ID3D11Device*
//---------------------------------------------
ID3D11Device* SystemDirectX11::SystemGetDevice()
{
	return m_pDevice;
}

//--------------------------------------------- 
/// \brief ID3D11DeviceContextを取得
/// \return ID3D11DeviceContext*
//---------------------------------------------
ID3D11DeviceContext* SystemDirectX11::SystemGetDeviceContext()
{
	return m_pDeviceContext;
}
