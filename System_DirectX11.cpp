#include "System_DirectX11.h"

bool SystemDirectX11::Init(HWND hWnd)
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

    return true;
}

void SystemDirectX11::BeforeRender()
{
    float clearColor[4] = { 0.75f, 0.75f, 0.75f, 1.0f }; //red,green,blue,alpha

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
    m_pDeviceContext->RSSetViewports(1, &m_ViewPort);
}

void SystemDirectX11::AfterRender()
{
    m_pSwapChain->Present(0, 0);
}

void SystemDirectX11::Release()
{
   
}

ID3D11Device* SystemDirectX11::GetDevice()
{
	return m_pDevice;
}

ID3D11DeviceContext* SystemDirectX11::GetDeviceContext()
{
	return m_pDeviceContext;
}
