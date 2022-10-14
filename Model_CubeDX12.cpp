//==============================================================================
// Filename: Model_CubeDX12.cpp
// Description: CubeClass for DirectX12
// Copyright (C) Silicon Studio Co., Ltd. All rights reserved.
//==============================================================================

#include "Model_CubeDX12.h"
#include "System_ScreenSize.h"
#include <iostream>

using namespace std;
using namespace DirectX;

struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
	XMFLOAT2 UV;
};

//--------------------------------------------- 
/// \param[in] ID3D12Device*(_device)
/// \param[in] ID3D12GraphicsCommandList*(_cmd)
/// 
/// \return 
//---------------------------------------------
bool ModelCubeDX12::ModelInit(ID3D12Device* _device, ID3D12GraphicsCommandList* _cmd)
{
	m_pDev = _device;
	m_pCmd = _cmd;

	// 頂点バッファの生成
	{
		// 頂点データ
		Vertex vertices[]
		{

		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},

		};

		// ヒーププロパティ
		D3D12_HEAP_PROPERTIES prop = {};

		prop.Type					= D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask		= 1;
		prop.VisibleNodeMask		= 1;

		// リソースの設定
		D3D12_RESOURCE_DESC desc = {};

		desc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment			= 0;
		desc.Width				= sizeof(vertices);
		desc.Height				= 1;
		desc.DepthOrArraySize	= 1;
		desc.MipLevels			= 1;
		desc.Format				= DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count	= 1;
		desc.SampleDesc.Quality	= 0;
		desc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags				= D3D12_RESOURCE_FLAG_NONE;

		// リソースを生成
		auto hr = m_pDev->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_pVB));

		if (FAILED(hr))
		{
			return false;
		}

		// マッピング
		void* ptr = nullptr;
		hr = m_pVB->Map(0, nullptr, &ptr);

		if (FAILED(hr))
		{
			return false;
		}

		// 頂点データをマッピング先に設定
		memcpy(ptr, vertices, sizeof(vertices));

		// マッピング解除
		m_pVB->Unmap(0, nullptr);

		// 頂点バッファビューの設定
		m_VBV.BufferLocation = m_pVB->GetGPUVirtualAddress();
		m_VBV.SizeInBytes = static_cast<UINT>(sizeof(vertices));
		m_VBV.StrideInBytes = static_cast<UINT>(sizeof(Vertex));
	}

	// インデックスバッファの生成
	{
		uint32_t indices[] = 
		{
			0, 1, 2, 3, 2, 1,
			4, 5, 6, 7, 6, 5,
			8, 9,10, 11, 10, 9,
			12, 13, 14, 15, 14, 13,
			16, 17, 18, 19, 18 ,17,
			20, 21, 22, 23, 22, 21, 
		};

		// ヒーププロパティ
		D3D12_HEAP_PROPERTIES prop = {};

		prop.Type					= D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask		= 1;
		prop.VisibleNodeMask		= 1;

		// リソースの設定
		D3D12_RESOURCE_DESC desc = {};

		desc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment			= 0;
		desc.Width				= sizeof(Transform);
		desc.Height				= 1;
		desc.DepthOrArraySize	= 1;
		desc.MipLevels			= 1;
		desc.Format				= DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count	= 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags				= D3D12_RESOURCE_FLAG_NONE;

		// リソースの生成
		auto hr = m_pDev->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_pIB));

		if (FAILED(hr))
		{
			return false;
		}

		// マッピング
		void* ptr = nullptr;
		hr = m_pIB->Map(0, nullptr, &ptr);

		if (FAILED(hr))
		{
			return false;
		}

		// インデックスデータをマッピング先に設定
		memcpy(ptr, indices, sizeof(indices));

		// マッピング解除
		m_pIB->Unmap(0, nullptr);

		// インデックスバッファビューの設定
		m_IBV.BufferLocation	= m_pIB->GetGPUVirtualAddress();
		m_IBV.Format			= DXGI_FORMAT_R32_UINT;
		m_IBV.SizeInBytes		= sizeof(indices);


	}

	// 定数バッファ用ディスクリプタヒープの生成
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.NumDescriptors = 1 * FRAME_COUNT;
		desc.Flags			= D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask		= 0;

		auto hr = m_pDev->CreateDescriptorHeap(
			&desc,
			IID_PPV_ARGS(&m_pHeapCBV));

		if (FAILED(hr))
		{
			return false;
		}
	}

	// 定数バッファの生成
	{
		// ヒーププロパティ
		D3D12_HEAP_PROPERTIES prop = {};

		prop.Type					= D3D12_HEAP_TYPE_UPLOAD;
		prop.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		prop.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
		prop.CreationNodeMask		= 1;
		prop.VisibleNodeMask		= 1;

		// リソースの設定
		D3D12_RESOURCE_DESC desc = {};

		desc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment			= 0;
		desc.Width				= sizeof(Transform);
		desc.Height				= 1;
		desc.DepthOrArraySize	= 1;
		desc.MipLevels			= 1;
		desc.Format				= DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count	= 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags				= D3D12_RESOURCE_FLAG_NONE;

		auto incrementSize = m_pDev->GetDescriptorHandleIncrementSize(
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
		);

		for (auto i = 0; i < FRAME_COUNT; ++i)
		{
			// リソースの生成
			auto hr = m_pDev->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&desc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_pCB[i]));

			if (FAILED(hr))
			{
				return false;
			}

			auto address = m_pCB[i]->GetGPUVirtualAddress();
			auto handleCPU = m_pHeapCBV->GetCPUDescriptorHandleForHeapStart();
			auto handleGPU = m_pHeapCBV->GetGPUDescriptorHandleForHeapStart();

			handleCPU.ptr += incrementSize * 1;
			handleGPU.ptr += incrementSize * 1;

			// 定数バッファビューの設定
			m_CBV[i].HandleCPU				= handleCPU;
			m_CBV[i].HandleGPU				= handleGPU;
			m_CBV[i].Desc.BufferLocation	= address;
			m_CBV[i].Desc.SizeInBytes		= sizeof(Transform);

			// 定数バッファビューを生成
			m_pDev->CreateConstantBufferView(
				&m_CBV[i].Desc,
				handleCPU);

			// マッピング
			hr = m_pCB[i]->Map(
				0,
				nullptr,
				reinterpret_cast<void**>(&m_CBV[i].pBuffer));

			if (FAILED(hr))
			{
				return false;
			}

			auto eyePos = XMVectorSet(-2.0f, 2.0, -5.0f, 0.0f);
			auto targetPos = XMVectorZero();
			auto upward = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

			auto fovY = XMConvertToRadians(37.5f);
			auto aspect = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);

			// 変換行列の設定
			m_CBV[i].pBuffer->World = XMMatrixIdentity();
			m_CBV[i].pBuffer->View = XMMatrixLookAtRH(eyePos, targetPos, upward);
			m_CBV[i].pBuffer->Proj = XMMatrixPerspectiveFovRH(fovY, aspect, 1.0f, 1000.0f);
		}
	}

	// ルートシグネイチャの生成
	{
		auto flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		flag |= D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;
		flag |= D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS;
		flag |= D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;

		// ルートパラメータの設定
		D3D12_ROOT_PARAMETER param[2] = {};

		param[0].ParameterType				= D3D12_ROOT_PARAMETER_TYPE_CBV;
		param[0].Descriptor.ShaderRegister	= 0;
		param[0].Descriptor.RegisterSpace	= 0;
		param[0].ShaderVisibility			= D3D12_SHADER_VISIBILITY_VERTEX;

		D3D12_DESCRIPTOR_RANGE range = {};

		range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		range.NumDescriptors = 1;
		range.BaseShaderRegister = 0;
		range.RegisterSpace = 0;
		range.OffsetInDescriptorsFromTableStart = 0;

		param[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		param[1].DescriptorTable.NumDescriptorRanges = 1;
		param[1].DescriptorTable.pDescriptorRanges = &range;
		param[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		// スタティックサンプラーの設定
		D3D12_STATIC_SAMPLER_DESC sampler = {};

		sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		sampler.MipLODBias = D3D12_DEFAULT_MIP_LOD_BIAS;
		sampler.MaxAnisotropy = 1;
		sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		sampler.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		sampler.MinLOD = -D3D12_FLOAT32_MAX;
		sampler.MaxLOD = +D3D12_FLOAT32_MAX;
		sampler.ShaderRegister = 0;
		sampler.RegisterSpace = 0;
		sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		// ルートシグネイチャの設定
		D3D12_ROOT_SIGNATURE_DESC desc = {};

		desc.NumParameters		= 2;
		desc.NumStaticSamplers	= 1;
		desc.pParameters		= param;
		desc.pStaticSamplers	= &sampler;
		desc.Flags				= flag;

		ID3DBlob* pBlob;
		ID3DBlob* pErrorBlob;

		// シリアライズ
		auto hr = D3D12SerializeRootSignature(
			&desc,
			D3D_ROOT_SIGNATURE_VERSION_1_0,
			&pBlob,
			&pErrorBlob);

		if (FAILED(hr))
		{
			return false;
		}

		// ルートシグネイチャの生成
		hr = m_pDev->CreateRootSignature(
			0,
			pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(),
			IID_PPV_ARGS(&m_pRootSignature));

		if (FAILED(hr))
		{
			return false;
		}
	}

	// パイプラインステートの生成
	{
		// 入力レイアウトの設定
		D3D12_INPUT_ELEMENT_DESC element[3];

		element[0].SemanticName			= "POSITION";
		element[0].SemanticIndex		= 0;
		element[0].Format				= DXGI_FORMAT_R32G32B32_FLOAT;
		element[0].InputSlot			= 0;
		element[0].AlignedByteOffset	= D3D12_APPEND_ALIGNED_ELEMENT;
		element[0].InputSlotClass		= D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		element[0].InstanceDataStepRate = 0;

		element[1].SemanticName			= "COLOR";
		element[1].SemanticIndex		= 0;
		element[1].Format				= DXGI_FORMAT_R32G32B32A32_FLOAT;
		element[1].InputSlot			= 0;
		element[1].AlignedByteOffset	= D3D12_APPEND_ALIGNED_ELEMENT;
		element[1].InputSlotClass		= D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		element[1].InstanceDataStepRate = 0;

		element[2].SemanticName			= "TEXCOORD";
		element[2].SemanticIndex		= 0;
		element[2].Format				= DXGI_FORMAT_R32G32_FLOAT;
		element[2].InputSlot			= 0;
		element[2].AlignedByteOffset	= D3D12_APPEND_ALIGNED_ELEMENT;
		element[2].InputSlotClass		= D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		element[2].InstanceDataStepRate = 0;

		// ラスタライザーステートの設定
		D3D12_RASTERIZER_DESC descRS;

		descRS.FillMode					= D3D12_FILL_MODE_SOLID;
		descRS.CullMode					= D3D12_CULL_MODE_NONE;
		descRS.FrontCounterClockwise	= FALSE;
		descRS.DepthBias				= D3D12_DEFAULT_DEPTH_BIAS;
		descRS.DepthBiasClamp			= D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		descRS.SlopeScaledDepthBias		= D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		descRS.DepthClipEnable			= FALSE;
		descRS.MultisampleEnable		= FALSE;
		descRS.AntialiasedLineEnable	= FALSE;
		descRS.ForcedSampleCount		= 0;
		descRS.ConservativeRaster		= D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

		// 深度ステンシルステートの設定
		D3D12_DEPTH_STENCIL_DESC descDSS = {};

		descDSS.DepthEnable		= TRUE;
		descDSS.DepthWriteMask	= D3D12_DEPTH_WRITE_MASK_ALL;
		descDSS.DepthFunc		= D3D12_COMPARISON_FUNC_LESS_EQUAL;
		descDSS.StencilEnable	= FALSE;

		// レンダーターゲットのブレンド設定
		D3D12_RENDER_TARGET_BLEND_DESC descRTBS =
		{
			FALSE, FALSE,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP,
			D3D12_COLOR_WRITE_ENABLE_ALL
		};

		// ブレンドステートの設定
		D3D12_BLEND_DESC descBS;

		descBS.AlphaToCoverageEnable = FALSE;
		descBS.IndependentBlendEnable = FALSE;

		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
		{
			descBS.RenderTarget[i] = descRTBS;
		}

		ID3DBlob* pVSBlob;
		ID3DBlob* pPSBlob;

		// 頂点シェーダ読み込み
		auto hr = D3DReadFileToBlob(L"shader/SimpleTexVS.cso", &pVSBlob);

		if (FAILED(hr))
		{
			return false;
		}

		// ピクセルシェーダ読み込み
		hr = D3DReadFileToBlob(L"shader/SimpleTexPS.cso", &pPSBlob);

		if (FAILED(hr))
		{
			return false;
		}

		// パイプラインステートの設定
		D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};

		desc.InputLayout						= { element, _countof(element) };
		desc.pRootSignature						= m_pRootSignature;
		desc.VS									= { pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize() };
		desc.PS									= { pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize() };
		desc.RasterizerState					= descRS;
		desc.BlendState							= descBS;
		desc.DepthStencilState					= descDSS;
		//desc.DepthStencilState.DepthEnable		= TRUE;
		//desc.DepthStencilState.StencilEnable	= TRUE;
		desc.SampleMask							= UINT_MAX;
		desc.PrimitiveTopologyType				= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		desc.NumRenderTargets					= 1;
		desc.RTVFormats[0]						= DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		desc.DSVFormat							= DXGI_FORMAT_D32_FLOAT;
		desc.SampleDesc.Count					= 1;
		desc.SampleDesc.Quality					= 0;

		// パイプラインステートを生成
		hr = m_pDev->CreateGraphicsPipelineState(
			&desc,
			IID_PPV_ARGS(&m_pPSO));

		if (FAILED(hr))
		{
			return false;
		}
	}

	// ビューポートとシザー矩形の設定
	{
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
		m_Viewport.Width	= static_cast<float>(SCREEN_WIDTH);
		m_Viewport.Height	= static_cast<float>(SCREEN_HEIGHT);
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;

		m_Scissor.left		= 0;
		m_Scissor.right		= SCREEN_WIDTH;
		m_Scissor.top		= 0;
		m_Scissor.bottom	= SCREEN_HEIGHT;
	}

	// テクスチャの生成
	{
		D3D12_RESOURCE_DESC texDesc;
		D3D12_HEAP_PROPERTIES heapProp;
		const UINT64 k_Width = 32;

		ZeroMemory(&texDesc, sizeof(texDesc));
		ZeroMemory(&heapProp, sizeof(heapProp));

		// テクスチャの準備
		heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
		heapProp.CreationNodeMask = 0;
		heapProp.VisibleNodeMask = 0;

		texDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		texDesc.Width = k_Width;
		texDesc.Height = k_Width;
		texDesc.DepthOrArraySize = 1;
		texDesc.MipLevels = 1;
		texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		texDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		texDesc.SampleDesc.Count = 1;
		texDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

		auto hr = m_pDev->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&texDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_Texture.pResource));

		if (FAILED(hr))
		{
			return false;
		}

		// テクスチャ更新
		D3D12_BOX box = { 0 };
		box.right = k_Width;
		box.bottom = k_Width;
		box.back = 1;
		uint32_t* p = (uint32_t*)malloc(k_Width * k_Width * sizeof(uint32_t));

		for (int i = 0; i < k_Width * k_Width; ++i)
		{
			if (i < (k_Width * k_Width) / 2)
			{
				//       A B G R
				p[i] = 0xFFFFFFFF;
			}
			else
			{
				//       A B G R
				p[i] = 0xFFFFFF00;
			}
		}

		m_Texture.pResource->WriteToSubresource(0, &box, p, 4 * k_Width, 4 * k_Width * k_Width);

		// インクリメントサイズを取得
		auto incrementSize = m_pDev->GetDescriptorHandleIncrementSize(
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		// CPUディスクリプタハンドルとGPUディスクリプタハンドルを取得
		auto handleCPU = m_pHeapCBV->GetCPUDescriptorHandleForHeapStart();
		auto handleGPU = m_pHeapCBV->GetGPUDescriptorHandleForHeapStart();

		handleCPU.ptr += incrementSize * 1;
		handleGPU.ptr += incrementSize * 1;

		m_Texture.HandleCPU = handleCPU;
		m_Texture.HandleGPU = handleGPU;

		// テクスチャの構成設定を取得
		auto textureDesc = m_Texture.pResource->GetDesc();

		// シェーダーリソースビューの設定
		D3D12_SHADER_RESOURCE_VIEW_DESC viewDesc = {};

		viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Format = textureDesc.Format;
		viewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		viewDesc.Texture2D.MostDetailedMip = 0;
		viewDesc.Texture2D.MipLevels = textureDesc.MipLevels;
		viewDesc.Texture2D.PlaneSlice = 0;
		viewDesc.Texture2D.ResourceMinLODClamp = 0.0f;

		// シェーダーリソースビューを生成
		m_pDev->CreateShaderResourceView(
			m_Texture.pResource, &viewDesc, handleCPU);
	}
	return true;
}

//--------------------------------------------- 
/// \param[in] uint32_t (frameindex)
/// \return 
//---------------------------------------------
void ModelCubeDX12::ModelUpdate(uint32_t frameindex)
{
	m_FrameIndex = frameindex;

	m_RotateAngle += 0.025f;
	m_CBV[m_FrameIndex].pBuffer->World = XMMatrixRotationY(m_RotateAngle);
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeDX12::ModelDraw()
{
	m_pCmd->SetGraphicsRootSignature(m_pRootSignature);
	m_pCmd->SetDescriptorHeaps(1, &m_pHeapCBV);
	m_pCmd->SetGraphicsRootConstantBufferView(0, m_CBV[m_FrameIndex].Desc.BufferLocation);
	m_pCmd->SetGraphicsRootDescriptorTable(1, m_Texture.HandleGPU);
	m_pCmd->SetPipelineState(m_pPSO);

	m_pCmd->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pCmd->IASetVertexBuffers(0, 1, &m_VBV);
	m_pCmd->IASetIndexBuffer(&m_IBV);
	m_pCmd->RSSetViewports(1, &m_Viewport);
	m_pCmd->RSSetScissorRects(1, &m_Scissor);

	m_pCmd->DrawIndexedInstanced(36, 1, 0, 0, 0);
}

//--------------------------------------------- 
/// \return 
//---------------------------------------------
void ModelCubeDX12::ModelRelease()
{
	for (auto i = 0; i < FRAME_COUNT; ++i)
	{
		if (m_pCB[i] != nullptr)
		{
			m_pCB[i]->Unmap(0, nullptr);
			memset(&m_CBV[i], 0, sizeof(m_CBV[i]));
		}

		//m_pCB[i].Reset();

		//m_pCB[i]->Release();
		//m_pCB[i] = nullptr;
	}

	//m_pVB.Reset();
	
	//m_pVB->Release();
	//m_pVB = nullptr;

	//m_pPSO.Reset();

	//m_pPSO->Release();
	//m_pPSO = nullptr;

	//m_pHeapCBV->Release();
	//m_pHeapCBV = nullptr;

	//m_pIB->Release();
	//m_pIB = nullptr;

	m_pRootSignature->Release();
	m_pRootSignature = nullptr;
}

void ModelCubeDX12::SetPos(float x)
{
	m_CBV->pBuffer->World = XMMatrixTranslation(x, 0, 0);
}
