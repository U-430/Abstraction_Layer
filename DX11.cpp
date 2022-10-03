#include "DX11.h"

// ����p�֐�
template<typename T> void SafeRelease(T*& _ptr);

bool DirectX11::Init(HWND hWnd)
{
	HRESULT				hr = S_OK;
	RECT				rect;
	IDXGIFactory*		pFactory;
	IDXGIAdapter*		pAdapter;
	IDXGIOutput*		pAdapterOutput;

	unsigned int		numModes;
	unsigned int		numerator = 60;			// ���q
	unsigned int		denominator = 1;		// ����
	unsigned int		createDeviceFlags = 0;
#if defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_MODE_DESC*		pDisplayModeList;
	D3D11_BLEND_DESC	blendStateDescription;
	D3D_FEATURE_LEVEL	level;

	// �h���C�o�̎��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	// �@�\���x��
	D3D_FEATURE_LEVEL featureLevals[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	unsigned int	numDriverTypes = ARRAYSIZE(driverTypes);
	UINT			numFeatureLevels = ARRAYSIZE(featureLevals);

	GetClientRect(hWnd, &rect);

	m_Width  = (UINT)(rect.right - rect.left);
	m_Height = (UINT)(rect.bottom - rect.top);

	// DXGIFactory�̍쐬
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if(FAILED(hr))
	{
		return false;
	}

	hr = pFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(hr))
	{
		return false;
	}

	hr = pAdapter->EnumOutputs(0, &pAdapterOutput);
	if (FAILED(hr))
	{
		return false;
	}

	hr = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr)) {
		return false;
	}

	pDisplayModeList = new DXGI_MODE_DESC[numModes];
	if (!pDisplayModeList)
	{
		return false;
	}

	hr = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, pDisplayModeList);
	if (FAILED(hr)) {
		return false;
	}

	for (unsigned int i = 0; i < numModes; i++) {

		if (pDisplayModeList[i].Width == m_Width) 
		{
			if (pDisplayModeList[i].Height == m_Height) 
			{
				numerator = pDisplayModeList[i].RefreshRate.Numerator;
				denominator = pDisplayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	delete[] pDisplayModeList;
	pDisplayModeList = nullptr;

	pAdapterOutput->Release();
	pAdapterOutput = nullptr;

	pAdapter->Release();
	pAdapter = nullptr;

	pFactory->Release();
	pFactory = nullptr;

	// �X���b�v�`�F�C���̐ݒ�
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(swapDesc));

	swapDesc.BufferCount = 1;														// �o�b�N�o�b�t�@�̐�
	swapDesc.BufferDesc.Width = m_Width;											// �o�b�N�o�b�t�@�̉���
	swapDesc.BufferDesc.Height = m_Height;											// �o�b�N�o�b�t�@�̏c��
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						// �o�b�N�o�b�t�@�t�H�[�}�b�g
	swapDesc.BufferDesc.RefreshRate.Numerator = numerator;							// ���t���b�V�����[�g(����)
	swapDesc.BufferDesc.RefreshRate.Denominator = denominator;						// ���t���b�V�����[�g(���q)
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	 
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;							// �o�b�N�o�b�t�@�̎g�p���@
	swapDesc.OutputWindow = hWnd;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = TRUE;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,							// �f�B�X�v���C�f�o�C�X�̃A�_�v�^
			driverTypes[driverTypeIndex],	// �f�o�C�X�h���C�o�̃^�C�v
			NULL,							
			createDeviceFlags,				// �f�o�C�X�t���O
			featureLevals,					// �@�\���x��
			numFeatureLevels,				// �@�\���x����
			D3D11_SDK_VERSION,
			&swapDesc,						// �X���b�v�`�F�C���̐ݒ�
			&m_pSwapChain,					// SwapChain�C���^�[�t�F�[�X
			&m_pDevice,						// Device�C���^�[�t�F�[�X
			&level,							// �T�|�[�g����Ă���@�\���x��
			&m_pDeviceContext				// �f�o�C�X�R���e�L�X�g
		);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	if (FAILED(hr))
	{
		return false;
	}

	ID3D11Texture2D* pBackBuffer;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void DirectX11::BeforeRender()
{
	float clearColor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
}

void DirectX11::AfterRender()
{
	m_pSwapChain->Present(1, 0);
}

void DirectX11::Release()
{
	SafeRelease(m_pSwapChain);
	SafeRelease(m_pRenderTargetView);
	SafeRelease(m_pDeviceContext);
	SafeRelease(m_pDevice);
}

template<typename T> void SafeRelease(T*& _ptr)
{
	if (_ptr != nullptr)
	{
		_ptr->Release();
		_ptr = nullptr;
	}
}
