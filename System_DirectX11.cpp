#include "System_DirectX11.h"

bool SystemDirectX11::Init(HWND hWnd)
{
	return false;
}

void SystemDirectX11::BeforeRender()
{
}

void SystemDirectX11::AfterRender()
{
}

void SystemDirectX11::Release()
{
}

ID3D11Device* SystemDirectX11::GetDevice()
{
	return m_pDevice;
}

ID3D11DeviceContext* SystemDirectX11::GetDeviceContext()
{
	return m_pDeviceContext;
}
