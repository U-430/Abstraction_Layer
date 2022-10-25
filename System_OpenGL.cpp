//==============================================================================
// Filename: System_OpenGL.cpp
// Description: OpenGL System
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================
#include "System_OpenGL.h"
#include "System_ScreenSize.h"

//--------------------------------------------- 
/// \param[in] HWND(_hwnd)
/// 
/// \return 
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

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// PC画像メモリーアライメント = Byte単位
    glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
    glDepthRange(0.0, 1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);		// Ｚ（デプス）テストＯＮ
    glDepthFunc(GL_LEQUAL);			// Ｚ値がバッファの値、以下であれば上書き
    glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);	// スクリーンの設定
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8.0 / 200.0, 8.0 / 200.0, -4.5 / 200.0, 4.5 / 200.0, 0.1, 100.0);	// かなり望遠に
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, -6.0, 
        0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0);

    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    return true;
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void SystemOpenGL::SystemBeforeRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 描画面のクリア
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void SystemOpenGL::SystemAfterRender()
{
    glFlush();				// コマンドのフラッシュ
    SwapBuffers(m_HDC);		// 画面のフリップ（wgl関数）
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void SystemOpenGL::SystemRelease()
{
    wglMakeCurrent(m_HDC, 0);
    wglDeleteContext(m_HRC);
    ReleaseDC(m_HWND, m_HDC);
}
