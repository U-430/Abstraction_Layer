#include "Model_CubeOpenGL.h"
//==============================================================================
// Filename: Model_CubeOpenGL.cpp
// Description: CubeClass for OpenGL
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

struct GLPos
{
    float x;
    float y;
    float z;
};

GLPos g_Pos[8] =
{
    {-1.0f, -1.0f, -1.0f},
    {-1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},

    { 1.0f, -1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},
    {-1.0f, -1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f}
};

float g_Color[6][3] =
{
    {1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 0.0f},
    {1.0f, 0.0f, 1.0f}
};

int g_Index[24] =
{
    0, 1, 2, 3,
    2, 3, 4, 5,
    4, 5, 6, 7,
    6, 7, 0, 1,
    1, 3, 7, 5,
    4, 6, 2, 0
};

GLuint g_Texname[TEXNUM];

//--------------------------------------------- 
/// \param[in] SystemLayer*(layer)
/// 
/// \return 
//---------------------------------------------
bool ModelCubeOpenGL::ModelInit(SystemLayer* layer)
{
    // テクスチャ生成
    for (int y = 0; y < TEXSIZE; y++)
    {
        for (int x = 0; x < TEXSIZE; x++)
        {
            if (y % 2 == 0)
            {
                m_Tex[y][x][0] = 255.0f; // R
                m_Tex[y][x][1] = 255.0f; // G
                m_Tex[y][x][2] = 0.0f; // B
                m_Tex[y][x][3] = 255.0f; // A
            }
            else
            {
                m_Tex[y][x][0] = 0.0f; // R
                m_Tex[y][x][1] = 0.0f; // G
                m_Tex[y][x][2] = 255.0f; // B
                m_Tex[y][x][3] = 255.0f; // A
            }
        }
    }

    // テクスチャセット
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXSIZE, TEXSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return true;
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeOpenGL::ModelDraw()
{
    glEnable(GL_BLEND);		// 透明度による重ね合わせを有効にする
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// 重ね合わせの方法
    //glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_TRIANGLE_STRIP);
    //glBegin(GL_LINE_STRIP);

    // 頂点、色、UVなどを設定
    for (int i = 0; i < 24; i += 4)
    {
        glColor3f(g_Color[i / 4][0], g_Color[i / 4][1], g_Color[i / 4][2]);

        glVertex3f(g_Pos[g_Index[i]].x, g_Pos[g_Index[i]].y, g_Pos[g_Index[i]].z);
        glTexCoord2f(0.0f, 1.0f);

        glVertex3f(g_Pos[g_Index[i + 1]].x, g_Pos[g_Index[i + 1]].y, g_Pos[g_Index[i + 1]].z);
        glTexCoord2f(0.0f, 0.0f);

        glVertex3f(g_Pos[g_Index[i + 2]].x, g_Pos[g_Index[i + 2]].y, g_Pos[g_Index[i + 2]].z);
        glTexCoord2f(1.0f, 1.0f);

        glVertex3f(g_Pos[g_Index[i + 3]].x, g_Pos[g_Index[i + 3]].y, g_Pos[g_Index[i + 3]].z);
        glTexCoord2f(1.0f, 0.0f);
    }

    //// 正面
    //glColor3f(1.0f, 1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //glVertex3f(-1.0f,  1.0f, -1.0f);
    //glVertex3f( 1.0f, -1.0f, -1.0f);
    //glVertex3f( 1.0f,  1.0f, -1.0f);

    //// 左面
    //glColor3f(1.0f, 0.0f, 0.0f);
    //glVertex3f (1.0f, -1.0f, -1.0f);
    //glVertex3f( 1.0f,  1.0f, -1.0f);
    //glVertex3f( 1.0f, -1.0f,  1.0f);
    //glVertex3f( 1.0f,  1.0f,  1.0f);

    //// 奥面
    //glColor3f(0.0f, 1.0f, 0.0f);
    //glVertex3f( 1.0f, -1.0f,  1.0f);
    //glVertex3f( 1.0f,  1.0f,  1.0f);
    //glVertex3f(-1.0f, -1.0f,  1.0f);
    //glVertex3f(-1.0f,  1.0f,  1.0f);

    //// 右面
    //glColor3f(0.0f, 0.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f,  1.0f);
    //glVertex3f(-1.0f,  1.0f,  1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //glVertex3f(-1.0f,  1.0f, -1.0f);

    //// 上面
    //glColor3f(1.0f, 1.0f, 0.0f);
    //glVertex3f(-1.0f, 1.0f, -1.0f);
    //glVertex3f(1.0f, 1.0f, -1.0f);
    //glVertex3f(-1.0f, 1.0f, 1.0f);
    //glVertex3f(1.0f, 1.0f, 1.0f);

    //// 下面
    //glColor3f(1.0f, 0.0f, 1.0f);
    //glVertex3f(1.0f, -1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);
    //glVertex3f(1.0f, -1.0f, -1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);

    glEnd();
    glDisable(GL_BLEND);
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeOpenGL::ModelRelease()
{
}
