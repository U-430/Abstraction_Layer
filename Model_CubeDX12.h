#pragma once
//==============================================================================
// Filename: Model_CubeDX12.h
// Description: CubeClass
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "System_DirectX12.h"

template<typename T>
struct ConstantBufferView
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC Desc;		// �萔�o�b�t�@�̍\���ݒ�
	D3D12_CPU_DESCRIPTOR_HANDLE		HandleCPU;	// CPU�f�B�X�N���v�^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE		HandleGPU;	// GPU�f�B�X�N���v�^�n���h��
	T*								pBuffer;	// �o�b�t�@�擪�ւ̃|�C���^
};

struct alignas(256) Transform
{
	DirectX::XMMATRIX World;	// ���[���h�s��
	DirectX::XMMATRIX View;		// �r���[�s��
	DirectX::XMMATRIX Proj;		// �ˉe�s��
};

class ModelCubeDX12 
{
public:
	// ����������
	bool ModelInit(ID3D12Device* device, ID3D12GraphicsCommandList* cmd);

	// �X�V����
	void ModelUpdate(uint32_t frameindex);

	// �`�揈��
	void ModelDraw();

	// �������
	void ModelRelease();

	void SetPos(float x);

private:
	ID3D12DescriptorHeap*	m_pHeapCBV;			/// �f�B�X�N���v�^�q�[�v(�萔�o�b�t�@�[�r���[��)
	ID3D12Resource*			m_pIB;				/// �C���f�b�N�X�o�b�t�@
	ID3D12Resource*			m_pVB;				/// ���_�o�b�t�@
	ID3D12Resource*			m_pCB[FRAME_COUNT];	/// �萔�o�b�t�@
	ID3D12RootSignature*	m_pRootSignature;	/// ���[�g�V�O�l�C�`��
	ID3D12PipelineState*	m_pPSO;				/// �p�C�v���C���X�e�[�g

	ID3D12Device*				m_pDev;				/// �f�o�C�X
	ID3D12GraphicsCommandList*	m_pCmd;				/// �R�}���h���X�g
	uint32_t					m_FrameIndex;		/// �t���[���ԍ�

	D3D12_INDEX_BUFFER_VIEW			m_IBV;				/// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW		m_VBV;				/// ���_�o�b�t�@�r���[
	D3D12_VIEWPORT					m_Viewport;			/// �r���[�|�[�g
	D3D12_RECT						m_Scissor;			/// �V�U�[��`
	ConstantBufferView<Transform>	m_CBV[FRAME_COUNT];	/// �萔�o�b�t�@�r���[
	float							m_RotateAngle;		/// ��]�p
};