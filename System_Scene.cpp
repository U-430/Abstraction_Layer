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

/// �؂�ւ��o�[�W����
VERSION g_Switch = NONE;

//--------------------------------------------- 
/// \brief Scene�̏���������
/// \param[in] HWND(_hwnd) �E�C���h�E�n���h��
/// 
/// \return bool
//---------------------------------------------
bool SystemScene::SystemInit(HWND _hwnd)
{
    m_Hwnd = _hwnd;

    // �o�[�W�����I��
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

    // ���C���[������
    if (m_pLayer->SystemInit(m_Hwnd))
    {
        // �L���[�u������
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
/// \brief Scene�̍X�V����
/// \return ����
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
/// \brief Scene�̕`�揈��
/// \return ����
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
/// \brief Scene�̉������
/// \return ����
//---------------------------------------------
void SystemScene::SystemRelease()
{

    m_pCube->ModelRelease();
    delete m_pCube;

    m_pLayer->SystemRelease();
    delete m_pLayer;
}

//--------------------------------------------- 
/// \brief Layer�̐؂�ւ�
/// \return ����
//---------------------------------------------
void SystemScene::SystemSwitchLayer(VERSION ver)
{
    SystemRelease();

    m_SystemVersion = ver;

    // �o�[�W�����I��
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

    // ���C���[������
    if (m_pLayer->SystemInit(m_Hwnd))
    {
        // �L���[�u������
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
