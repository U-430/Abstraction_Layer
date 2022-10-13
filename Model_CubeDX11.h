#pragma once
//==============================================================================
// Filename: Model_CubeDX11.h
// Description: CubeClass
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(o) {if(o != NULL){o->Release();o = NULL;}else{o = NULL;}}

class ModelCubeDX11
{
public:
	// ����������
	bool ModelInit(ID3D11Device* _device, ID3D11DeviceContext* _context);

	// �`�揈��
	void ModelDraw();

	// �������
	void ModelReleace();

private:
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
};
