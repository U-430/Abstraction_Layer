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
/// \brief Scene�̕`�揈��
/// \return ����
//---------------------------------------------
void SystemScene::SystemDraw()
{
    m_pLayer->SystemBeforeRender();

    m_pCube->ModelDraw();

    m_pLayer->SystemAfterRender();
}

//--------------------------------------------- 
/// \brief Scene�̉������
/// \return ����
//---------------------------------------------
void SystemScene::SystemRelease()
{

    m_pCube->ModelRelease();
    m_pLayer->SystemRelease();

    delete m_pCube;
    delete m_pLayer;
}
