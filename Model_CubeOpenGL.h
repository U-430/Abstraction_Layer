#pragma once
//==============================================================================
// Filename: Model_CubeOpenGL.h
// Description: CubeClass for OpenGL
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_OpenGL.h"
#include "Model_Cube.h"

class ModelCubeOpenGL : public ModelCube
{
	bool ModelInit(SystemLayer* layer);

	void ModelDraw();

	void ModelRelease();
};
