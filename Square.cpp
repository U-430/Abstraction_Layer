#include "Square.h"
#include "System_ScreenSize.h"
#include <iostream>

using namespace std;
using namespace DirectX;

struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

bool Square::Init(ID3D12Device* device, ID3D12GraphicsCommandList* cmd, uint32_t frameindex)
{
	m_pDev = device;
	m_pCmd = cmd;
	m_FrameIndex - frameindex;

	// 頂点バッファの生成
	{
		// 頂点データ
		Vertex vertices[]
		{
			{ XMFLOAT3(-1.0f,  1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ XMFLOAT3( 1.0f,  1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(	1.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
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
		uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };

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

			auto eyePos = XMVectorSet(0.0f, 0.0, 5.0f, 0.0f);
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
		D3D12_ROOT_PARAMETER param = {};

		param.ParameterType				= D3D12_ROOT_PARAMETER_TYPE_CBV;
		param.Descriptor.ShaderRegister = 0;
		param.Descriptor.RegisterSpace	= 0;
		param.ShaderVisibility			= D3D12_SHADER_VISIBILITY_VERTEX;

		// ルートシグネイチャの設定
		D3D12_ROOT_SIGNATURE_DESC desc = {};

		desc.NumParameters		= 1;
		desc.NumStaticSamplers	= 0;
		desc.pParameters		= &param;
		desc.pStaticSamplers	= nullptr;
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
		D3D12_INPUT_ELEMENT_DESC element[2];

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
		auto hr = D3DReadFileToBlob(L"SimpleVS.cso", &pVSBlob);

		if (FAILED(hr))
		{
			return false;
		}

		// ピクセルシェーダ読み込み
		hr = D3DReadFileToBlob(L"SimplePS.cso", &pPSBlob);

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
		desc.DepthStencilState.DepthEnable		= FALSE;
		desc.DepthStencilState.StencilEnable	= FALSE;
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

	return true;
}

void Square::Update()
{
	m_RotateAngle += 0.025f;
	m_CBV[m_FrameIndex].pBuffer->World = XMMatrixRotationY(m_RotateAngle);
}

void Square::Draw()
{
	m_pCmd->SetGraphicsRootSignature(m_pRootSignature);
	m_pCmd->SetDescriptorHeaps(1, &m_pHeapCBV);
	m_pCmd->SetGraphicsRootConstantBufferView(0, m_CBV[m_FrameIndex].Desc.BufferLocation);
	m_pCmd->SetPipelineState(m_pPSO);

	m_pCmd->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pCmd->IASetVertexBuffers(0, 1, &m_VBV);
	m_pCmd->IASetIndexBuffer(&m_IBV);
	m_pCmd->RSSetViewports(1, &m_Viewport);
	m_pCmd->RSSetScissorRects(1, &m_Scissor);

	m_pCmd->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void Square::Release()
{
	for (auto i = 0; i < FRAME_COUNT; ++i)
	{
		if (m_pCB[i] != nullptr)
		{
			m_pCB[i]->Unmap(0, nullptr);
			memset(&m_CBV[i], 0, sizeof(m_CBV[i]));
		}

		//m_pCB[i].Reset();

		m_pCB[i]->Release();
		m_pCB[i] = nullptr;
	}

	//m_pVB.Reset();
	
	m_pVB->Release();
	m_pVB = nullptr;

	//m_pPSO.Reset();

	m_pPSO->Release();
	m_pPSO = nullptr;
}

void Square::SetPos(float x)
{
	m_CBV->pBuffer->World = XMMatrixTranslation(x, 0, 0);
}
