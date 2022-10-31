#pragma once
//==============================================================================
// Filename: Model_CubeDX11.h
// Description: CubeClass for DirectX11
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "System_DirectX11.h"
#include "Model_Cube.h"


class ModelCubeDX11 : public ModelCube
{
public:
	//---------------------------------------------------------------------------
	// public methods
	//---------------------------------------------------------------------------

	// ����������
	bool ModelInit(SystemLayer* layer);

	// �`�揈��
	void ModelDraw();

	// �������
	void ModelReleace();

	///<
private:
	//---------------------------------------------------------------------------
	// private variables
	//---------------------------------------------------------------------------

	ID3D11Device*				m_pDev;				/// �f�o�C�X
	ID3D11DeviceContext*		m_pContext;			/// �f�o�C�X�R���e�L�X�g
	ID3D11Buffer*				m_pVertexBuffer;	/// ���_�o�b�t�@
	ID3D11VertexShader*			m_pVertexShader;	/// ���_�V�F�[�_�[
	ID3D11PixelShader*			m_pPixelShader;		/// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*			m_pInputLayout;		/// �C���v�b�g���C�A�E�g

	ID3D11SamplerState*			m_pSampler;			/// �T���v���[
	ID3D11Texture2D*			m_pTexture;			/// �e�N�X�`��
	ID3D11ShaderResourceView*	m_pSRV;				/// �V�F�[�_�[���\�[�X�r���[

	ID3D11Buffer*				m_pIndexBuffer;		/// �C���f�b�N�X�o�b�t�@
	ID3D11Buffer*				m_pConstantBuffer;	/// �萔�o�b�t�@
	///<
};
