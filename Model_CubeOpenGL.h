#pragma once
//==============================================================================
// Filename: Model_CubeOpenGL.h
// Description: CubeClass for OpenGL
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_OpenGL.h"
#include "Model_Cube.h"

#define TEXSIZE 32
#define TEXNUM 1

class ModelCubeOpenGL : public ModelCube
{
public:
	bool ModelInit(SystemLayer* layer);

	void ModelDraw();

	void ModelRelease();

private:
	GLubyte m_Tex[TEXSIZE][TEXSIZE][4];
};
