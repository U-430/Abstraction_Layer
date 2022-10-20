#include "System_Scene.h"

bool SystemScene::SystemInit(HWND _hwnd)
{
    m_Hwnd = _hwnd;

    // バージョン選択
    switch (m_SystemVersion)
    {
    case DIRECTX11:
        m_pLayer = new SystemDirectX11();

        if (m_pLayer->SystemInit(m_Hwnd))
        {
            auto work = (SystemDirectX11*)m_pLayer;
            if (!m_CubeDX11.ModelInit(work->SystemGetDevice(), work->SystemGetDeviceContext()))
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
        m_pLayer = new SystemDirectX12();

        if (m_pLayer->SystemInit(m_Hwnd))
        {
            auto work = (SystemDirectX12*)m_pLayer;
            if (!m_CubeDX12.ModelInit(work->SystemGetDevice(), work->SystemGetCmdList()))
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
    m_pLayer->SystemBeforeRender();

    switch (m_SystemVersion)
    {
    case DIRECTX11:
        m_CubeDX11.ModelDraw();

        break;
    case DIRECTX12:
        //m_CubeDX12.ModelUpdate(m_DirectX12.SystemmetFrameIndex());
        m_CubeDX12.ModelDraw();

        break;
    default:
        break;
    }

    m_pLayer->SystemAfterRender();
}

void SystemScene::SystemRelease()
{
    switch (m_SystemVersion)
    {
    case DIRECTX11:
        m_CubeDX11.ModelReleace();

        break;
    case DIRECTX12:
        m_CubeDX12.ModelRelease();

        break;
    default:
        break;
    }

    m_pLayer->SystemRelease();
    delete m_pLayer;
}
