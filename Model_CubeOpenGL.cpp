#include "Model_CubeOpenGL.h"
//==============================================================================
// Filename: Model_CubeOpenGL.cpp
// Description: CubeClass for OpenGL
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

float	vertex[24] = {
     1.000000f, 1.000000f,-1.000000f,
     1.000000f,-1.000000f,-1.000000f,
    -1.000000f,-1.000000f,-1.000000f,
    -1.000000f, 1.000000f,-1.000000f,
     1.000000f, 0.999999f, 1.000000f,
     0.999999f,-1.000001f, 1.000000f,
    -1.000000f,-1.000000f, 1.000000f,
    -1.000000f, 1.000000f, 1.000000f
};
int		p_vertex_idx[24] = { 0,1,2,-4,4,7,6,-6,0,4,5,-2,1,5,6,-3,2,6,7,-4,4,0,3,-8 };

//--------------------------------------------- 
/// \param[in] SystemLayer*(layer)
/// 
/// \return 
//---------------------------------------------
bool ModelCubeOpenGL::ModelInit(SystemLayer* layer)
{
    return true;
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeOpenGL::ModelDraw()
{
    //int  i = 0;
    glEnable(GL_BLEND);		// 透明度による重ね合わせを有効にする
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// 重ね合わせの方法
    glDisable(GL_TEXTURE_2D);

    //glBegin(GL_TRIANGLE_STRIP);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < VERTEX_NUM; i++)
    {
        //glColor3f(m_V[m_IndexList[i]].color[0], m_V[m_IndexList[i]].color[1], m_V[m_IndexList[i]].color[2]);
        //glVertex3f(m_V[m_IndexList[i]].pos[0], m_V[m_IndexList[i]].pos[1], m_V[m_IndexList[i]].pos[2]);

        //glColor3f(m_V[i].color[0], m_V[i].color[1], m_V[i].color[2]);
        //glVertex3f(m_V[i].pos[0], m_V[i].pos[1], m_V[i].pos[2]);
    }

    //int no;
    //for (int i = 0; i < 24; i++) {
    //    while (1) {

    //        if (p_vertex_idx[i] < 0)
    //        {
    //            no = ~p_vertex_idx[i];
    //        }
    //        else
    //        {
    //            no = p_vertex_idx[i];
    //        }

    //        glColor3f(1.0f, 1.0f, 1.0f);
    //        glVertex3f(vertex[no * 3], vertex[no * 3 + 1], vertex[no * 3 + 2]);

    //        if (p_vertex_idx[i] < 0)
    //        {
    //            break;
    //        }
    //        else
    //        {
    //            i++;
    //        }
    //    }
    //}

    // 正面
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // 左面
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f (1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);

    // 奥面
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    // 右面
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    glEnd();
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeOpenGL::ModelRelease()
{
}
