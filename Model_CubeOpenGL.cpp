#include "Model_CubeOpenGL.h"
//==============================================================================
// Filename: Model_CubeOpenGL.cpp
// Description: CubeClass for OpenGL
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

bool ModelCubeOpenGL::ModelInit(SystemLayer* layer)
{
    return true;
}

void ModelCubeOpenGL::ModelDraw()
{
    glBegin(GL_TRIANGLE_STRIP);

    for (int i = 0; i < INDEX_NUM; i += 3)
    {
        glColor3f(m_V[m_IndexList[i]].color[0], m_V[m_IndexList[i]].color[1], m_V[m_IndexList[i]].color[2]);
        glVertex3f(m_V[m_IndexList[i]].pos[0], m_V[m_IndexList[i]].pos[1], m_V[m_IndexList[i]].pos[2]);
    }

    glEnd();
}

void ModelCubeOpenGL::ModelRelease()
{
}
