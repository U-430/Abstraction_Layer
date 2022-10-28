//==============================================================================
// Filename: System_OpenGL.cpp
// Description: OpenGL System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "System_OpenGL.h"
#include "System_ScreenSize.h"

//--------------------------------------------- 
/// \brief OpenGL�̏��������� 
/// \param[in] HWND(_hwnd) �E�C���h�E�n���h��
/// 
/// \return bool
//---------------------------------------------
bool SystemOpenGL::SystemInit(HWND _hwnd)
{
    m_HWND = _hwnd;
    m_HDC = GetDC(m_HWND);

    int pixelFormat;
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0, 0, 0, 0, 0,
        0,
        0,
        0, 0, 0, 0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    pixelFormat = ChoosePixelFormat(m_HDC, &pfd);
    SetPixelFormat(m_HDC, pixelFormat, &pfd);

    m_HRC = wglCreateContext(m_HDC);
    wglMakeCurrent(m_HDC, m_HRC);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// PC�摜�������[�A���C�����g = Byte�P��
    glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
    glDepthRange(0.0, 1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);		// �y�i�f�v�X�j�e�X�g�n�m
    glDepthFunc(GL_LEQUAL);			// �y�l���o�b�t�@�̒l�A�ȉ��ł���Ώ㏑��
    glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);	// �X�N���[���̐ݒ�
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8.0 / 200.0, 8.0 / 200.0, -4.5 / 200.0, 4.5 / 200.0, 0.1, 100.0);	// ���Ȃ�]����
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        3.0, 2.0, -6.0, 
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0);

    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    return true;
}

//--------------------------------------------- 
/// \brief OpenGL�̕`��O����
/// \return ����
//---------------------------------------------
void SystemOpenGL::SystemBeforeRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �`��ʂ̃N���A
}

//--------------------------------------------- 
/// \brief OpenGL�̕`��㏈��
/// \return ����
//---------------------------------------------
void SystemOpenGL::SystemAfterRender()
{
    glFlush();				// �R�}���h�̃t���b�V��
    SwapBuffers(m_HDC);		// ��ʂ̃t���b�v�iwgl�֐��j
}

//--------------------------------------------- 
/// \brief OpenGL�̉������
/// \return ����
//---------------------------------------------
void SystemOpenGL::SystemRelease()
{
    wglMakeCurrent(m_HDC, 0);
    wglDeleteContext(m_HRC);
    ReleaseDC(m_HWND, m_HDC);
}