#pragma once
//==============================================================================
// Filename: Model_Cube.h
// Description: CubeClass for Layer
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_Layer.h"


#define SAFE_RELEASE(o) {if(o != NULL){o->Release();o = NULL;}else{o = NULL;}}
#define VERTEX_NUM 24
#define INDEX_NUM 36

struct VertexData
{
	float pos[3];	// x, y, z
	float color[4];	// r, g, b, a
	float uv[2];	// u, v
};

class ModelCube
{
public:
	virtual bool ModelInit(SystemLayer* layer) { return true; };

	virtual bool ModelInit() { return true; };

	virtual void ModelDraw() {};

	virtual void ModelRelease() {};

protected:
	
	/// 頂点データ
	VertexData m_V[VERTEX_NUM] =
	{
		{(-0.5f, -0.5f, -0.5f), (1.0f, 1.0f, 1.0f, 1.0f), (0.0f, 1.0f)},
		{(-0.5f,  0.5f, -0.5f), (1.0f, 1.0f, 1.0f, 1.0f), (0.0f, 0.0f)},
		{( 0.5f, -0.5f, -0.5f), (1.0f, 1.0f, 1.0f, 1.0f), (1.0f, 1.0f)},
		{( 0.5f,  0.5f, -0.5f), (1.0f, 1.0f, 1.0f, 1.0f), (1.0f, 0.0f)},

		{( 0.5f, -0.5f, -0.5f), (1.0f, 0.0f, 0.0f, 1.0f), (0.0f, 1.0f)},
		{( 0.5f,  0.5f, -0.5f), (1.0f, 0.0f, 0.0f, 1.0f), (0.0f, 0.0f)},
		{( 0.5f, -0.5f,  0.5f), (1.0f, 0.0f, 0.0f, 1.0f), (1.0f, 1.0f)},
		{( 0.5f,  0.5f,  0.5f), (1.0f, 0.0f, 0.0f, 1.0f), (1.0f, 0.0f)},

		{( 0.5f, -0.5f,  0.5f), (0.0f, 1.0f, 0.0f, 1.0f), (0.0f, 1.0f)},
		{( 0.5f,  0.5f,  0.5f), (0.0f, 1.0f, 0.0f, 1.0f), (0.0f, 0.0f)},
		{(-0.5f, -0.5f,  0.5f), (0.0f, 1.0f, 0.0f, 1.0f), (1.0f, 1.0f)},
		{(-0.5f,  0.5f,  0.5f), (0.0f, 1.0f, 0.0f, 1.0f), (1.0f, 0.0f)},

		{(-0.5f, -0.5f,  0.5f), (0.0f, 0.0f, 1.0f, 1.0f), (0.0f, 1.0f)},
		{(-0.5f,  0.5f,  0.5f), (0.0f, 0.0f, 1.0f, 1.0f), (0.0f, 0.0f)},
		{(-0.5f, -0.5f, -0.5f), (0.0f, 0.0f, 1.0f, 1.0f), (1.0f, 1.0f)},
		{(-0.5f,  0.5f, -0.5f), (0.0f, 0.0f, 1.0f, 1.0f), (1.0f, 0.0f)},

		{(-0.5f,  0.5f,  0.5f), (1.0f, 1.0f, 0.0f, 1.0f), (0.0f, 1.0f)},
		{( 0.5f,  0.5f,  0.5f), (1.0f, 1.0f, 0.0f, 1.0f), (0.0f, 0.0f)},
		{(-0.5f,  0.5f, -0.5f), (1.0f, 1.0f, 0.0f, 1.0f), (1.0f, 1.0f)},
		{( 0.5f,  0.5f, -0.5f), (1.0f, 1.0f, 0.0f, 1.0f), (1.0f, 0.0f)},

		{(-0.5f, -0.5f, -0.5f), (1.0f, 0.0f, 1.0f, 1.0f), (0.0f, 1.0f)},
		{(-0.5f, -0.5f,  0.5f), (1.0f, 0.0f, 1.0f, 1.0f), (0.0f, 0.0f)},
		{( 0.5f, -0.5f, -0.5f), (1.0f, 0.0f, 1.0f, 1.0f), (1.0f, 1.0f)},
		{( 0.5f, -0.5f,  0.5f), (1.0f, 0.0f, 1.0f, 1.0f), (1.0f, 0.0f)},
	};

	/// インデックスリスト 
	WORD m_IndexList[INDEX_NUM] = 
	{
		0, 1, 2, 3, 2, 1,
		4, 5, 6, 7, 6, 5,
		8, 9,10, 11, 10, 9,
		12, 13, 14, 15, 14, 13,
		16, 17, 18, 19, 18 ,17,
		20, 21, 22, 23, 22, 21,
	};
};
