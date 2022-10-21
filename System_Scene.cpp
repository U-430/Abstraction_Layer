//==============================================================================
// Filename: System_Scene.cpp
// Description: Scene System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_Scene.h"

//--------------------------------------------- 
/// \param[in] HWND(_hwnd)
/// 
/// \return 
//---------------------------------------------
bool SystemScene::SystemInit(HWND _hwnd)
{
    m_Hwnd = _hwnd;

    // バージョン選択
    switch (m_SystemVersion)
    {
    case DIRECTX11:
        m_pLayer = new SystemDirectX11();
        m_pCube = new ModelCubeDX11();

        break;
    case DIRECTX12:
        m_pLayer = new SystemDirectX12();
        m_pCube = new ModelCubeDX12();

        break;

    case OPENGL:
        break;
    default:
        return false;
        break;
    }

    // レイヤー初期化
    if (m_pLayer->SystemInit(m_Hwnd))
    {
        // キューブ初期化
        if (!m_pCube->ModelInit(m_pLayer))
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void SystemScene::SystemDraw()
{
    m_pLayer->SystemBeforeRender();

    m_pCube->ModelDraw();

    m_pLayer->SystemAfterRender();
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void SystemScene::SystemRelease()
{

    m_pCube->ModelRelease();
    m_pLayer->SystemRelease();

    delete m_pCube;
    delete m_pLayer;
}
