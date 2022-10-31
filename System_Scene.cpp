//==============================================================================
// Filename: System_Scene.cpp
// Description: Scene System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_Scene.h"

#include "System_DirectX11.h"
#include "System_DirectX12.h"
#include "System_OpenGL.h"
#include "Model_CubeDX11.h"
#include "Model_CubeDX12.h"
#include "Model_CubeOpenGL.h"

/// 切り替えバージョン
VERSION g_Switch = NONE;

//--------------------------------------------- 
/// \brief Sceneの初期化処理
/// \param[in] HWND(_hwnd) ウインドウハンドル
/// 
/// \return bool
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
        m_pLayer = new SystemOpenGL();
        m_pCube = new ModelCubeOpenGL();
        break;

    case NONE:
        m_pLayer = new SystemLayer();
        m_pCube = new ModelCube();
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
/// \brief Sceneの更新処理
/// \return 無し
//---------------------------------------------
void SystemScene::SystemUpdate()
{
    if (GetAsyncKeyState('1') && !m_KeyFlg)
    {
        m_KeyFlg = true;
        g_Switch = DIRECTX11;
    }
    else if (GetAsyncKeyState('2') && !m_KeyFlg)
    {
        m_KeyFlg = true;
        g_Switch = DIRECTX12;
    }
    else if (GetAsyncKeyState('3') && !m_KeyFlg)
    {
        m_KeyFlg = true;
        g_Switch = OPENGL;
    }
    else if (GetAsyncKeyState('4') && !m_KeyFlg)
    {
        m_KeyFlg = true;
        g_Switch = NONE;
    }
    else
    {
        m_KeyFlg = false;
    }
}

//--------------------------------------------- 
/// \brief Sceneの描画処理
/// \return 無し
//---------------------------------------------
void SystemScene::SystemDraw()
{
    m_pLayer->SystemBeforeRender();

    m_pCube->ModelDraw();

    m_pLayer->SystemAfterRender();


    if (g_Switch != m_SystemVersion && g_Switch != DIRECTX12)
    {
        SystemSwitchLayer(g_Switch);
    }
}

//--------------------------------------------- 
/// \brief Sceneの解放処理
/// \return 無し
//---------------------------------------------
void SystemScene::SystemRelease()
{

    m_pCube->ModelRelease();
    delete m_pCube;

    m_pLayer->SystemRelease();
    delete m_pLayer;
}

//--------------------------------------------- 
/// \brief Layerの切り替え
/// \return 無し
//---------------------------------------------
void SystemScene::SystemSwitchLayer(VERSION ver)
{
    SystemRelease();

    m_SystemVersion = ver;

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
        m_pLayer = new SystemOpenGL();
        m_pCube = new ModelCubeOpenGL();

        break;

    case NONE:
        m_pLayer = new SystemLayer();
        m_pCube = new ModelCube();

        break;
    default:
        break;
    }

    // レイヤー初期化
    if (m_pLayer->SystemInit(m_Hwnd))
    {
        // キューブ初期化
        if (!m_pCube->ModelInit(m_pLayer))
        {
            return;
        }
    }
    else
    {
        return;
    }
}
