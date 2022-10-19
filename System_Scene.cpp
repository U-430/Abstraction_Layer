#include "System_Scene.h"

bool SystemScene::SystemInit(HWND _hwnd)
{
    m_Hwnd = _hwnd;

    // バージョン選択
    switch (m_SystemVersion)
    {
    case DIRECTX11:
        if (m_DirectX11.SystemInit(m_Hwnd))
        {
            if (!m_CubeDX11.ModelInit(m_DirectX11.SystemGetDevice(), m_DirectX11.SystemGetDeviceContext()))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        break;
    case DIRECTX12:
        if (m_DirectX12.SystemInit(m_Hwnd))
        {
            if (!m_CubeDX12.ModelInit(m_DirectX12.SystemGetDevice(), m_DirectX12.SystemGetCmdList()))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        break;
    default:
        return false;
        break;
    }

    return true;
}

void SystemScene::SystemDraw()
{
    switch (m_SystemVersion)
    {
    case DIRECTX11:
        m_DirectX11.SystemBeforeRender();
        m_CubeDX11.ModelDraw();
        m_DirectX11.SystemAfterRender();

        break;
    case DIRECTX12:
        //m_CubeDX12.ModelUpdate(m_DirectX12.SystemmetFrameIndex());
        m_DirectX12.SystemBeforeRender();
        m_CubeDX12.ModelDraw();
        m_DirectX12.SystemAfterRender();

        break;
    default:
        break;
    }
}

void SystemScene::SystemRelease()
{
    switch (m_SystemVersion)
    {
    case DIRECTX11:
        m_CubeDX11.ModelReleace();
        m_DirectX11.SystemRelease();

        break;
    case DIRECTX12:
        m_CubeDX12.ModelRelease();
        m_DirectX12.SystemRelease();

        break;
    default:
        break;
    }
}
