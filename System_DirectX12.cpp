#include "System_DirectX12.h"
#include <Windows.h>
#include <iostream>
#include "System_ScreenSize.h"

using namespace std;

// ����p�֐�
template<typename T> void SafeRelease(T*& _ptr);

// ���̉�
//const uint32_t	                    DirectX12::FrameCount;
//
//ComPtr<ID3D12Device>                DirectX12::m_pDevice;
//ComPtr<ID3D12CommandQueue>          DirectX12::m_pQueue;
//ComPtr<IDXGISwapChain3>             DirectX12::m_pSwapChain;
//ComPtr<ID3D12Resource>              DirectX12::m_pColorBuffer[FrameCount];
//ComPtr<ID3D12CommandAllocator>      DirectX12::m_pCmdAllocator[FrameCount];
//ComPtr<ID3D12GraphicsCommandList>   DirectX12::m_pCmdList;
//ComPtr<ID3D12DescriptorHeap>        DirectX12::m_pHeadRTV;
//ComPtr<ID3D12Fence>                 DirectX12::m_pFence;
//ComPtr<ID3D12Resource>              DirectX12::m_pDepthBuffer;
//ComPtr<ID3D12DescriptorHeap>        DirectX12::m_pHeapDSV;
//
//HANDLE						        DirectX12::m_FenceEvent;
//uint64_t					        DirectX12::m_FenceCounter[FrameCount];
//uint32_t					        DirectX12::m_FrameIndex;
//
//D3D12_CPU_DESCRIPTOR_HANDLE	        DirectX12::m_HandleRTV[FrameCount];
//D3D12_CPU_DESCRIPTOR_HANDLE         DirectX12::m_HandleDSV;

bool SystemDirectX12::InitDX12(HWND hWnd)
{

    #if defined(DEBUG) || defined(_DEBUG)
        ID3D12Debug* debug;

        auto hl = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));

        // �f�o�b�O���C���[��L����
        if (SUCCEEDED(hl))
        {
            cout << "�f�o�b�O���C���[�L����" << endl;
            debug->EnableDebugLayer();
        }
    #endif

    // �f�o�C�X�̐���
    auto hr = D3D12CreateDevice(
        nullptr,
        D3D_FEATURE_LEVEL_11_0,
        IID_PPV_ARGS(&m_pDevice));

    if (FAILED(hr))
    {
        cout << "�f�o�C�X�������s" << endl;
        return false;
    }

    cout << "�f�o�C�X��������" << endl;

    // �R�}���h�L���[�̐���
    {
        D3D12_COMMAND_QUEUE_DESC desc = {};

        desc.Type       = D3D12_COMMAND_LIST_TYPE_DIRECT;         // �R�}���h�L���[�ɓo�^�\�ȃR�}���h���X�g�̃^�C�v�ݒ�
        desc.Priority   = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;    // �R�}���h�L���[�̗D��x
        desc.Flags      = D3D12_COMMAND_QUEUE_FLAG_NONE;          // �R�}���h�L���[�𐶐�����ۂ̓����ݒ�t���O
        desc.NodeMask   = 0;                                      // GPU�m�[�h�̎���(GPU����������ꍇ�̂ݐݒ�)

        hr = m_pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_pQueue));

        if (FAILED(hr))
        {
            cout << "�R�}���h�L���[�������s" << endl;
            return false;
        }

        cout << "�R�}���h�L���[��������" << endl;
    }


    // �X���b�v�`�F�C���̐���
    {
        // DXGI�t�@�N�g���[�̐���
        IDXGIFactory4* pFactory = nullptr;
        hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));

        if (FAILED(hr))
        {
            cout << "DXGI�t�@�N�g���[�������s" << endl;
            return false;
        }

        cout << "DXGI�t�@�N�g���[��������" << endl;

        // �X���b�v�`�F�C���̐ݒ�
        //DXGI_SWAP_CHAIN_DESC1 desc = {};

        //desc.Width = SCREEN_WIDTH;                                       // �𑜓x�̉���
        //desc.Height = SCREEN_HEIGHT;                                     // �𑜓x�̏c��
        //desc.Scaling = DXGI_SCALING_NONE;                                // �g��k���̐ݒ�
        //desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                        // �\���`���̃s�N�Z���t�H�[�}�b�g
        //desc.SampleDesc.Count = 1;                                       // �s�N�Z���P�ʂ̃}���`�T���v�����O��
        //desc.SampleDesc.Quality = 0;                                     // �摜�̕i�� �i���������قǃp�t�H�[�}���X�͒ቺ
        //desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;              // �o�b�N�o�b�t�@�̎g�p���@
        //desc.BufferCount = FrameCount;                                   // �o�b�N�o�b�t�@�̐�                                                     // �t���X�N���[���w��
        //desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                      // �o�b�N�o�b�t�@�̓���ւ�������
        //desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;             // �X���b�v�`�F�C���̓���I�v�V����


        DXGI_SWAP_CHAIN_DESC desc = {};

        desc.BufferDesc.Width                   = SCREEN_WIDTH;                             // �𑜓x�̉���
        desc.BufferDesc.Height                  = SCREEN_HEIGHT;                            // �𑜓x�̏c��
        desc.BufferDesc.RefreshRate.Numerator   = 60;                                       // ���t���b�V�����[�g(Hz�P��)�̕��q���w��
        desc.BufferDesc.RefreshRate.Denominator = 1;                                        // ���t���b�V�����[�g(Hz�P��)�̕�����w��
        desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;     // �������`�惂�[�h
        desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;            // �g��k���̐ݒ�
        desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;               // �\���`���̃s�N�Z���t�H�[�}�b�g
        desc.SampleDesc.Count                   = 1;                                        // �s�N�Z���P�ʂ̃}���`�T���v�����O��
        desc.SampleDesc.Quality                 = 0;                                        // �摜�̕i�� �i���������قǃp�t�H�[�}���X�͒ቺ
        desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;          // �o�b�N�o�b�t�@�̎g�p���@
        desc.BufferCount                        = FRAME_COUNT;                               // �o�b�N�o�b�t�@�̐�
        desc.OutputWindow                       = hWnd;                    // �o�͂���E�B���h�E�̃E�B���h�E�n���h��
        desc.Windowed                           = TRUE;                                     // �t���X�N���[���w��
        desc.SwapEffect                         = DXGI_SWAP_EFFECT_FLIP_DISCARD;            // �o�b�N�o�b�t�@�̓���ւ�������
        desc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // �X���b�v�`�F�C���̓���I�v�V����

        // �X���b�v�`�F�C���̐���
        IDXGISwapChain* pSwapChain = nullptr;
        //IDXGISwapChain1* pSwapChain = nullptr;

        hr = pFactory->CreateSwapChain(m_pQueue, &desc, &pSwapChain);

        //hr = pFactory->CreateSwapChainForHwnd(m_pQueue, WindowsApp::GetHWND(), &desc, nullptr, nullptr, &pSwapChain);

        if (FAILED(hr))
        {
            cout << "�X���b�v�`�F�C���������s" << endl;
            SafeRelease(pFactory);
            return false;
        }

        cout << "�X���b�v�`�F�C����������" << endl;

        //IDXGISwapChain3���擾
        hr = pSwapChain->QueryInterface(IID_PPV_ARGS(&m_pSwapChain));

        if (FAILED(hr))
        {
            cout << "IDXGISwapChain3�擾���s" << endl;
            SafeRelease(pFactory);
            SafeRelease(pSwapChain);
            return false;
        }

        cout << "IDXGISwapChain3�擾����" << endl;

        // �o�b�N�o�b�t�@�ԍ����擾
        m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

        // �s�v�ɂȂ����̂ŉ��
        SafeRelease(pFactory);
        SafeRelease(pSwapChain);
    }


    // �R�}���h�A���P�[�^�̐���
    {
        for (auto i = 0u; i < FRAME_COUNT; i++)
        {
            hr = m_pDevice->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT,
                IID_PPV_ARGS(&m_pCmdAllocator[i]));

            if (FAILED(hr))
            {
                cout << "�R�}���h�A���P�[�^�������s" << endl;
                return false;
            }

            cout << "�R�}���h�A���P�[�^��������" << endl;
        }
    }

    // �R�}���h���X�g�̐���
    {
        hr = m_pDevice->CreateCommandList(
            0,
            D3D12_COMMAND_LIST_TYPE_DIRECT,
            m_pCmdAllocator[m_FrameIndex],
            nullptr,
            IID_PPV_ARGS(&m_pCmdList));

        if (FAILED(hr))
        {
            cout << "�R�}���h���X�g�������s" << endl;
            return false;
        }

        cout << "�R�}���h���X�g��������" << endl;
    }


    // �����_�[�^�[�Q�b�g�r���[�̐���
    {
        // �f�B�X�N���v�^�q�[�v�̐ݒ�
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};

        desc.NumDescriptors = FRAME_COUNT;                       // �q�[�v���̃f�B�X�N���v�^��
        desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;   // �f�B�X�N���v�^�q�[�v�̃^�C�v
        desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;  // D3D12_DESCRIPTOR_HEAP_FLAGS�^���r�b�g���Z�ɂ��l�̑g�ݍ��킹�Ŏw��
        desc.NodeMask       = 0;                                // GPU�m�[�h�̎���(GPU����������ꍇ�̂ݐݒ�)

        // �f�B�X�N���v�^�q�[�v�̐���
        hr = m_pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pHeadRTV));

        if (FAILED(hr))
        {
            cout << "�f�B�X�N���v�^�q�[�v�������s" << endl;
            return false;
        }

        cout << "�f�B�X�N���v�^�q�[�v��������" << endl;

        auto handle = m_pHeadRTV->GetCPUDescriptorHandleForHeapStart();
        auto incrementSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        for (auto i = 0u; i < FRAME_COUNT; i++)
        {
            hr = m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pColorBuffer[i]));

            if (FAILED(hr))
            {
                return false;
            }

            D3D12_RENDER_TARGET_VIEW_DESC viewDesc = {};

            viewDesc.Format                 = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;  // ��ʂŌ��鎞�̃s�N�Z���t�H�[�}�b�g�̎w��
            viewDesc.ViewDimension          = D3D12_RTV_DIMENSION_TEXTURE2D;    // �ǂ̂悤�Ƀ����_�[�^�[�Q�b�g�̃��\�[�X�ɃA�N�Z�X���邩�̎������w��
            viewDesc.Texture2D.MipSlice     = 0;                                // �g�p����~�b�v�}�b�v���x���̔ԍ�
            viewDesc.Texture2D.PlaneSlice   = 0;                                // �g�p����e�N�X�`���̕��ʃX���C�X�ԍ�

            // �����_�[�^�[�Q�b�g�r���[�̐���
            m_pDevice->CreateRenderTargetView(m_pColorBuffer[i], &viewDesc, handle);

            m_HandleRTV[i] = handle;
            handle.ptr += incrementSize;
        }
    }


    // �t�F���X�̐���
    {
        // �t�F���X�J�E���^�[�����Z�b�g
        for (auto i = 0u; i < FRAME_COUNT; i++)
        {
            m_FenceCounter[i] = 0;
        }

        // �t�F���X�̐���
        hr = m_pDevice->CreateFence(
            m_FenceCounter[m_FrameIndex],
            D3D12_FENCE_FLAG_NONE,
            IID_PPV_ARGS(&m_pFence));

        if (FAILED(hr))
        {
            cout << "�t�F���X�������s" << endl;
            return false;
        }

        cout << "�t�F���X��������" << endl;

        m_FenceCounter[m_FrameIndex]++;

        // �C�x���g�̐���
        m_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        if (m_FenceEvent == nullptr)
        {
            cout << "�C�x���g�������s" << endl;
            return false;
        }

        cout << "�C�x���g��������" << endl;
    }

    // �[�x�X�e���V���o�b�t�@�̐���
    {
        D3D12_HEAP_PROPERTIES prop = {};

        prop.Type                   = D3D12_HEAP_TYPE_DEFAULT;
        prop.CPUPageProperty        = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        prop.MemoryPoolPreference   = D3D12_MEMORY_POOL_UNKNOWN;
        prop.CreationNodeMask       = 1;
        prop.VisibleNodeMask        = 1;

        D3D12_RESOURCE_DESC resDesc = {};

        resDesc.Dimension           = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        resDesc.Alignment           = 0;
        resDesc.Width               = SCREEN_WIDTH;
        resDesc.Height              = SCREEN_HEIGHT;
        resDesc.DepthOrArraySize    = 1;
        resDesc.MipLevels           = 1;
        resDesc.Format              = DXGI_FORMAT_D32_FLOAT;
        resDesc.SampleDesc.Count    = 1;
        resDesc.SampleDesc.Quality  = 0;
        resDesc.Layout              = D3D12_TEXTURE_LAYOUT_UNKNOWN;
        resDesc.Flags               = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

        D3D12_CLEAR_VALUE clearValue;

        clearValue.Format               = DXGI_FORMAT_D32_FLOAT;
        clearValue.DepthStencil.Depth   = 1.0;
        clearValue.DepthStencil.Stencil = 0;

        hr = SystemDirectX12::GetDevice()->CreateCommittedResource(
            &prop,
            D3D12_HEAP_FLAG_NONE,
            &resDesc,
            D3D12_RESOURCE_STATE_DEPTH_WRITE,
            &clearValue,
            IID_PPV_ARGS(&m_pDepthBuffer));

        if (FAILED(hr))
        {
            return false;
        }

        // �f�B�X�N���v�^�q�[�v�̐ݒ�
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};

        heapDesc.NumDescriptors = 1;
        heapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        heapDesc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        heapDesc.NodeMask       = 0;

        hr = m_pDevice->CreateDescriptorHeap(
            &heapDesc,
            IID_PPV_ARGS(&m_pHeapDSV));

        if (FAILED(hr))
        {
            return false;
        }

        auto handle = m_pHeapDSV->GetCPUDescriptorHandleForHeapStart();
        auto incrementSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

        D3D12_DEPTH_STENCIL_VIEW_DESC viewDesc = {};

        viewDesc.Format             = DXGI_FORMAT_D32_FLOAT;
        viewDesc.ViewDimension      = D3D12_DSV_DIMENSION_TEXTURE2D;
        viewDesc.Texture2D.MipSlice = 0;
        viewDesc.Flags              = D3D12_DSV_FLAG_NONE;

        m_pDevice->CreateDepthStencilView(m_pDepthBuffer, &viewDesc, handle);

        m_HandleDSV = handle;
    }

    // �R�}���h���X�g�����
    m_pCmdList->Close();

    return true;
}

void SystemDirectX12::Release()
{
    // GPU�����̊�����ҋ@
    WaitGPU();

    // �C�x���g�j��
    if (m_FenceEvent != nullptr)
    {
        CloseHandle(m_FenceEvent);
        m_FenceEvent = nullptr;
    }

    // �t�F���X�j��
    SafeRelease(m_pFence);
    //m_pFence.Reset();

    // �����_�[�^�[�Q�b�g�r���[�̔j��
    SafeRelease(m_pHeadRTV);
    //m_pHeadRTV.Reset();

    for (auto i = 0u; i < FRAME_COUNT; i++)
    {
        SafeRelease(m_pColorBuffer[i]);
        //m_pColorBuffer[i].Reset();
    }

    // �R�}���h���X�g�̔j��
    SafeRelease(m_pCmdList);
    //m_pCmdList.Reset();

    // �R�}���h�A���P�[�^�̔j��
    for (auto i = 0u; i < FRAME_COUNT; i++)
    {
        SafeRelease(m_pCmdAllocator[i]);
       //m_pCmdAllocator[i].Reset();
    }

    // �X���b�v�`�F�C���̔j��
    SafeRelease(m_pSwapChain);
    //m_pSwapChain.Reset();

    // �R�}���h�L���[�̔j��
    SafeRelease(m_pQueue);
    //m_pQueue.Reset();

    // �f�o�C�X�̔j��
    SafeRelease(m_pDevice);
    //m_pDevice.Reset();
}

void SystemDirectX12::Render()
{
    // �R�}���h�̋L�^���J�n
    m_pCmdAllocator[m_FrameIndex]->Reset();
    m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex], nullptr);

    // ���\�[�X�o���A�̏������ݐݒ�
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;   // ���\�[�X�o���A�̃^�C�v
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;         // �t���O�ݒ�
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];       // �J�ڂɎg�p���郊�\�[�X�̃|�C���^
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_PRESENT;             // �T�u���\�[�X�̎g�p�O�̏��
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_RENDER_TARGET;       // �T�u���\�[�X�̎g�p��̏��
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;  // �J�ڂׂ̈̃T�u���\�[�X�̔ԍ�

    // ���\�[�X�o���A
    m_pCmdList->ResourceBarrier(1, &barrier);

    // �����_�[�^�[�Q�b�g�̐ݒ�
    m_pCmdList->OMSetRenderTargets(1, &m_HandleRTV[m_FrameIndex], FALSE, &m_HandleDSV);

    // �N���A�J���[�̐ݒ�
    float clearColor[] = {0.25f, 0.25f, 0.25f, 1.0f};

    // �����_�[�^�[�Q�b�g�r���[���N���A
    m_pCmdList->ClearRenderTargetView(m_HandleRTV[m_FrameIndex], clearColor, 0, nullptr);

    // �[�x�X�e���V���r���[���N���A
    m_pCmdList->ClearDepthStencilView(m_HandleDSV, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    // �`�揈��
    {
        // �`��p���������̕����ɏ���
    }

    // ���\�[�X�o���A�̕\���ݒ�
    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // ���\�[�X�o���A
    m_pCmdList->ResourceBarrier(1, &barrier);

    // �R�}���h�̋L�^���I��
    m_pCmdList->Close();

    // �R�}���h�����s
    ID3D12CommandList* ppCmdLists[] = { m_pCmdList };
    m_pQueue->ExecuteCommandLists(1, ppCmdLists);

    // ��ʂɕ\��
    Present(1);
}

void SystemDirectX12::BeforeRender()
{
    // �R�}���h�̋L�^���J�n
    m_pCmdAllocator[m_FrameIndex]->Reset();
    m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex], nullptr);

    // ���\�[�X�o���A�̏������ݐݒ�
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;   // ���\�[�X�o���A�̃^�C�v
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;         // �t���O�ݒ�
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];       // �J�ڂɎg�p���郊�\�[�X�̃|�C���^
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_PRESENT;             // �T�u���\�[�X�̎g�p�O�̏��
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_RENDER_TARGET;       // �T�u���\�[�X�̎g�p��̏��
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;  // �J�ڂׂ̈̃T�u���\�[�X�̔ԍ�

    // ���\�[�X�o���A
    m_pCmdList->ResourceBarrier(1, &barrier);

    // �����_�[�^�[�Q�b�g�̐ݒ�
    m_pCmdList->OMSetRenderTargets(1, &m_HandleRTV[m_FrameIndex], FALSE, &m_HandleDSV);

    // �N���A�J���[�̐ݒ�
    float clearColor[] = { 0.25f, 0.25f, 0.25f, 1.0f };

    // �����_�[�^�[�Q�b�g�r���[���N���A
    m_pCmdList->ClearRenderTargetView(m_HandleRTV[m_FrameIndex], clearColor, 0, nullptr);

    // �[�x�X�e���V���r���[���N���A
    m_pCmdList->ClearDepthStencilView(m_HandleDSV, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void SystemDirectX12::BeforeRender(float r, float g, float b)
{
    // �R�}���h�̋L�^���J�n
    m_pCmdAllocator[m_FrameIndex]->Reset();
    m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex], nullptr);

    // ���\�[�X�o���A�̏������ݐݒ�
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;   // ���\�[�X�o���A�̃^�C�v
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;         // �t���O�ݒ�
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];       // �J�ڂɎg�p���郊�\�[�X�̃|�C���^
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_PRESENT;             // �T�u���\�[�X�̎g�p�O�̏��
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_RENDER_TARGET;       // �T�u���\�[�X�̎g�p��̏��
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;  // �J�ڂׂ̈̃T�u���\�[�X�̔ԍ�

    // ���\�[�X�o���A
    m_pCmdList->ResourceBarrier(1, &barrier);

    // �����_�[�^�[�Q�b�g�̐ݒ�
    m_pCmdList->OMSetRenderTargets(1, &m_HandleRTV[m_FrameIndex], FALSE, &m_HandleDSV);

    // �N���A�J���[�̐ݒ�
    float clearColor[] = { r, g, b, 1.0f };

    // �����_�[�^�[�Q�b�g�r���[���N���A
    m_pCmdList->ClearRenderTargetView(m_HandleRTV[m_FrameIndex], clearColor, 0, nullptr);

    // �[�x�X�e���V���r���[���N���A
    m_pCmdList->ClearDepthStencilView(m_HandleDSV, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void SystemDirectX12::AfterRender()
{
    // ���\�[�X�o���A�̕\���ݒ�
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // ���\�[�X�o���A
    m_pCmdList->ResourceBarrier(1, &barrier);

    // �R�}���h�̋L�^���I��
    m_pCmdList->Close();

    // �R�}���h�����s
    ID3D12CommandList* ppCmdLists[] = { m_pCmdList };
    m_pQueue->ExecuteCommandLists(1, ppCmdLists);

    // ��ʂɕ\��
    Present(1);
}

ID3D12Device* SystemDirectX12::GetDevice()
{
    return m_pDevice;
}

ID3D12CommandQueue* SystemDirectX12::GetQueue()
{
    return m_pQueue;
}

ID3D12GraphicsCommandList* SystemDirectX12::GetCmdList()
{
    return m_pCmdList;
}

uint32_t SystemDirectX12::GetFrameIndex()
{
    return m_FrameIndex;
}

void SystemDirectX12::WaitGPU()
{
   // assert(m_pQueue != nullptr);
   // assert(m_pFence != nullptr);
   // assert(m_FenceEvent != nullptr);

    // �V�O�i������
    m_pQueue->Signal(m_pFence, m_FenceCounter[m_FrameIndex]);

    // �������ɃC�x���g��ݒ肷��
    m_pFence->SetEventOnCompletion(m_FenceCounter[m_FrameIndex], m_FenceEvent);

    // �ҋ@����
    WaitForSingleObjectEx(m_FenceEvent, INFINITE, FALSE);

    // �J�E���^�[�𑝂₷
    m_FenceCounter[m_FrameIndex]++;
}

void SystemDirectX12::Present(uint32_t _interval)
{
    // ��ʂɕ\��
    m_pSwapChain->Present(_interval, 0);

    // �V�O�i������
    const auto currentValue = m_FenceCounter[m_FrameIndex];
    m_pQueue->Signal(m_pFence, currentValue);

    // �o�b�N�o�b�t�@�ԍ����X�V
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

    // ���̃t���[���̕`�揀�����܂��ł���Αҋ@����
    if (m_pFence->GetCompletedValue() < m_FenceCounter[m_FrameIndex])
    {
        m_pFence->SetEventOnCompletion(m_FenceCounter[m_FrameIndex], m_FenceEvent);
        WaitForSingleObjectEx(m_FenceEvent, INFINITE, FALSE);
    }

    // ���̃t���[���̃t�F���X�J�E���^�[�𑝂₷
    m_FenceCounter[m_FrameIndex] = currentValue + 1;
}

template<typename T> void SafeRelease(T*& _ptr)
{
    if (_ptr != nullptr)
    {
        _ptr->Release();
        _ptr = nullptr;
    }
}
