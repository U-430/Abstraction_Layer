#include "DX11.h"


bool DirectX11::Init()
{
	auto			hr = S_OK;
	IDXGIFactory*	pFactory;
	IDXGIAdapter*	pAdapter;
	IDXGIOutput*	pAdapterOutput;

	unsigned int	numModes;
	unsigned int	numerator = 60;		// ���q
	unsigned int	denominator = 1;	// ����

	DXGI_MODE_DESC* pDisplayModeList;

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
}

void DirectX11::BeforeRender()
{
}

void DirectX11::AfterRender()
{
}

void DirectX11::Release()
{

}
