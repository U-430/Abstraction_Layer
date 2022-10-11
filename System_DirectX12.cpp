#include "System_DirectX12.h"
#include <Windows.h>
#include <iostream>
#include "System_ScreenSize.h"

using namespace std;

// 解放用関数
template<typename T> void SafeRelease(T*& _ptr);

// 実体化
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

        // デバッグレイヤーを有効化
        if (SUCCEEDED(hl))
        {
            cout << "デバッグレイヤー有効化" << endl;
            debug->EnableDebugLayer();
        }
    #endif

    // デバイスの生成
    auto hr = D3D12CreateDevice(
        nullptr,
        D3D_FEATURE_LEVEL_11_0,
        IID_PPV_ARGS(&m_pDevice));

    if (FAILED(hr))
    {
        cout << "デバイス生成失敗" << endl;
        return false;
    }

    cout << "デバイス生成成功" << endl;

    // コマンドキューの生成
    {
        D3D12_COMMAND_QUEUE_DESC desc = {};

        desc.Type       = D3D12_COMMAND_LIST_TYPE_DIRECT;         // コマンドキューに登録可能なコマンドリストのタイプ設定
        desc.Priority   = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;    // コマンドキューの優先度
        desc.Flags      = D3D12_COMMAND_QUEUE_FLAG_NONE;          // コマンドキューを生成する際の特性設定フラグ
        desc.NodeMask   = 0;                                      // GPUノードの識別(GPUが複数ある場合のみ設定)

        hr = m_pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_pQueue));

        if (FAILED(hr))
        {
            cout << "コマンドキュー生成失敗" << endl;
            return false;
        }

        cout << "コマンドキュー生成成功" << endl;
    }


    // スワップチェインの生成
    {
        // DXGIファクトリーの生成
        IDXGIFactory4* pFactory = nullptr;
        hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));

        if (FAILED(hr))
        {
            cout << "DXGIファクトリー生成失敗" << endl;
            return false;
        }

        cout << "DXGIファクトリー生成成功" << endl;

        // スワップチェインの設定
        //DXGI_SWAP_CHAIN_DESC1 desc = {};

        //desc.Width = SCREEN_WIDTH;                                       // 解像度の横幅
        //desc.Height = SCREEN_HEIGHT;                                     // 解像度の縦幅
        //desc.Scaling = DXGI_SCALING_NONE;                                // 拡大縮小の設定
        //desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                        // 表示形式のピクセルフォーマット
        //desc.SampleDesc.Count = 1;                                       // ピクセル単位のマルチサンプリング数
        //desc.SampleDesc.Quality = 0;                                     // 画像の品質 品質が高いほどパフォーマンスは低下
        //desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;              // バックバッファの使用方法
        //desc.BufferCount = FrameCount;                                   // バックバッファの数                                                     // フルスクリーン指定
        //desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                      // バックバッファの入れ替え時効果
        //desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;             // スワップチェインの動作オプション


        DXGI_SWAP_CHAIN_DESC desc = {};

        desc.BufferDesc.Width                   = SCREEN_WIDTH;                             // 解像度の横幅
        desc.BufferDesc.Height                  = SCREEN_HEIGHT;                            // 解像度の縦幅
        desc.BufferDesc.RefreshRate.Numerator   = 60;                                       // リフレッシュレート(Hz単位)の分子を指定
        desc.BufferDesc.RefreshRate.Denominator = 1;                                        // リフレッシュレート(Hz単位)の分母を指定
        desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;     // 走査線描画モード
        desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;            // 拡大縮小の設定
        desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;               // 表示形式のピクセルフォーマット
        desc.SampleDesc.Count                   = 1;                                        // ピクセル単位のマルチサンプリング数
        desc.SampleDesc.Quality                 = 0;                                        // 画像の品質 品質が高いほどパフォーマンスは低下
        desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;          // バックバッファの使用方法
        desc.BufferCount                        = FRAME_COUNT;                               // バックバッファの数
        desc.OutputWindow                       = hWnd;                    // 出力するウィンドウのウィンドウハンドル
        desc.Windowed                           = TRUE;                                     // フルスクリーン指定
        desc.SwapEffect                         = DXGI_SWAP_EFFECT_FLIP_DISCARD;            // バックバッファの入れ替え時効果
        desc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // スワップチェインの動作オプション

        // スワップチェインの生成
        IDXGISwapChain* pSwapChain = nullptr;
        //IDXGISwapChain1* pSwapChain = nullptr;

        hr = pFactory->CreateSwapChain(m_pQueue, &desc, &pSwapChain);

        //hr = pFactory->CreateSwapChainForHwnd(m_pQueue, WindowsApp::GetHWND(), &desc, nullptr, nullptr, &pSwapChain);

        if (FAILED(hr))
        {
            cout << "スワップチェイン生成失敗" << endl;
            SafeRelease(pFactory);
            return false;
        }

        cout << "スワップチェイン生成成功" << endl;

        //IDXGISwapChain3を取得
        hr = pSwapChain->QueryInterface(IID_PPV_ARGS(&m_pSwapChain));

        if (FAILED(hr))
        {
            cout << "IDXGISwapChain3取得失敗" << endl;
            SafeRelease(pFactory);
            SafeRelease(pSwapChain);
            return false;
        }

        cout << "IDXGISwapChain3取得成功" << endl;

        // バックバッファ番号を取得
        m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

        // 不要になったので解放
        SafeRelease(pFactory);
        SafeRelease(pSwapChain);
    }


    // コマンドアロケータの生成
    {
        for (auto i = 0u; i < FRAME_COUNT; i++)
        {
            hr = m_pDevice->CreateCommandAllocator(
                D3D12_COMMAND_LIST_TYPE_DIRECT,
                IID_PPV_ARGS(&m_pCmdAllocator[i]));

            if (FAILED(hr))
            {
                cout << "コマンドアロケータ生成失敗" << endl;
                return false;
            }

            cout << "コマンドアロケータ生成成功" << endl;
        }
    }

    // コマンドリストの生成
    {
        hr = m_pDevice->CreateCommandList(
            0,
            D3D12_COMMAND_LIST_TYPE_DIRECT,
            m_pCmdAllocator[m_FrameIndex],
            nullptr,
            IID_PPV_ARGS(&m_pCmdList));

        if (FAILED(hr))
        {
            cout << "コマンドリスト生成失敗" << endl;
            return false;
        }

        cout << "コマンドリスト生成成功" << endl;
    }


    // レンダーターゲットビューの生成
    {
        // ディスクリプタヒープの設定
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};

        desc.NumDescriptors = FRAME_COUNT;                       // ヒープ内のディスクリプタ数
        desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;   // ディスクリプタヒープのタイプ
        desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;  // D3D12_DESCRIPTOR_HEAP_FLAGS型をビット演算による値の組み合わせで指定
        desc.NodeMask       = 0;                                // GPUノードの識別(GPUが複数ある場合のみ設定)

        // ディスクリプタヒープの生成
        hr = m_pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pHeadRTV));

        if (FAILED(hr))
        {
            cout << "ディスクリプタヒープ生成失敗" << endl;
            return false;
        }

        cout << "ディスクリプタヒープ生成成功" << endl;

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

            viewDesc.Format                 = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;  // 画面で見る時のピクセルフォーマットの指定
            viewDesc.ViewDimension          = D3D12_RTV_DIMENSION_TEXTURE2D;    // どのようにレンダーターゲットのリソースにアクセスするかの次元を指定
            viewDesc.Texture2D.MipSlice     = 0;                                // 使用するミップマップレベルの番号
            viewDesc.Texture2D.PlaneSlice   = 0;                                // 使用するテクスチャの平面スライス番号

            // レンダーターゲットビューの生成
            m_pDevice->CreateRenderTargetView(m_pColorBuffer[i], &viewDesc, handle);

            m_HandleRTV[i] = handle;
            handle.ptr += incrementSize;
        }
    }


    // フェンスの生成
    {
        // フェンスカウンターをリセット
        for (auto i = 0u; i < FRAME_COUNT; i++)
        {
            m_FenceCounter[i] = 0;
        }

        // フェンスの生成
        hr = m_pDevice->CreateFence(
            m_FenceCounter[m_FrameIndex],
            D3D12_FENCE_FLAG_NONE,
            IID_PPV_ARGS(&m_pFence));

        if (FAILED(hr))
        {
            cout << "フェンス生成失敗" << endl;
            return false;
        }

        cout << "フェンス生成成功" << endl;

        m_FenceCounter[m_FrameIndex]++;

        // イベントの生成
        m_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        if (m_FenceEvent == nullptr)
        {
            cout << "イベント生成失敗" << endl;
            return false;
        }

        cout << "イベント生成成功" << endl;
    }

    // 深度ステンシルバッファの生成
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

        // ディスクリプタヒープの設定
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

    // コマンドリストを閉じる
    m_pCmdList->Close();

    return true;
}

void SystemDirectX12::Release()
{
    // GPU処理の完了を待機
    WaitGPU();

    // イベント破棄
    if (m_FenceEvent != nullptr)
    {
        CloseHandle(m_FenceEvent);
        m_FenceEvent = nullptr;
    }

    // フェンス破棄
    SafeRelease(m_pFence);
    //m_pFence.Reset();

    // レンダーターゲットビューの破棄
    SafeRelease(m_pHeadRTV);
    //m_pHeadRTV.Reset();

    for (auto i = 0u; i < FRAME_COUNT; i++)
    {
        SafeRelease(m_pColorBuffer[i]);
        //m_pColorBuffer[i].Reset();
    }

    // コマンドリストの破棄
    SafeRelease(m_pCmdList);
    //m_pCmdList.Reset();

    // コマンドアロケータの破棄
    for (auto i = 0u; i < FRAME_COUNT; i++)
    {
        SafeRelease(m_pCmdAllocator[i]);
       //m_pCmdAllocator[i].Reset();
    }

    // スワップチェインの破棄
    SafeRelease(m_pSwapChain);
    //m_pSwapChain.Reset();

    // コマンドキューの破棄
    SafeRelease(m_pQueue);
    //m_pQueue.Reset();

    // デバイスの破棄
    SafeRelease(m_pDevice);
    //m_pDevice.Reset();
}

void SystemDirectX12::Render()
{
    // コマンドの記録を開始
    m_pCmdAllocator[m_FrameIndex]->Reset();
    m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex], nullptr);

    // リソースバリアの書き込み設定
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;   // リソースバリアのタイプ
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;         // フラグ設定
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];       // 遷移に使用するリソースのポインタ
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_PRESENT;             // サブリソースの使用前の状態
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_RENDER_TARGET;       // サブリソースの使用後の状態
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;  // 遷移の為のサブリソースの番号

    // リソースバリア
    m_pCmdList->ResourceBarrier(1, &barrier);

    // レンダーターゲットの設定
    m_pCmdList->OMSetRenderTargets(1, &m_HandleRTV[m_FrameIndex], FALSE, &m_HandleDSV);

    // クリアカラーの設定
    float clearColor[] = {0.25f, 0.25f, 0.25f, 1.0f};

    // レンダーターゲットビューをクリア
    m_pCmdList->ClearRenderTargetView(m_HandleRTV[m_FrameIndex], clearColor, 0, nullptr);

    // 深度ステンシルビューをクリア
    m_pCmdList->ClearDepthStencilView(m_HandleDSV, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

    // 描画処理
    {
        // 描画用処理をこの部分に書く
    }

    // リソースバリアの表示設定
    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // リソースバリア
    m_pCmdList->ResourceBarrier(1, &barrier);

    // コマンドの記録を終了
    m_pCmdList->Close();

    // コマンドを実行
    ID3D12CommandList* ppCmdLists[] = { m_pCmdList };
    m_pQueue->ExecuteCommandLists(1, ppCmdLists);

    // 画面に表示
    Present(1);
}

void SystemDirectX12::BeforeRender()
{
    // コマンドの記録を開始
    m_pCmdAllocator[m_FrameIndex]->Reset();
    m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex], nullptr);

    // リソースバリアの書き込み設定
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;   // リソースバリアのタイプ
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;         // フラグ設定
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];       // 遷移に使用するリソースのポインタ
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_PRESENT;             // サブリソースの使用前の状態
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_RENDER_TARGET;       // サブリソースの使用後の状態
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;  // 遷移の為のサブリソースの番号

    // リソースバリア
    m_pCmdList->ResourceBarrier(1, &barrier);

    // レンダーターゲットの設定
    m_pCmdList->OMSetRenderTargets(1, &m_HandleRTV[m_FrameIndex], FALSE, &m_HandleDSV);

    // クリアカラーの設定
    float clearColor[] = { 0.25f, 0.25f, 0.25f, 1.0f };

    // レンダーターゲットビューをクリア
    m_pCmdList->ClearRenderTargetView(m_HandleRTV[m_FrameIndex], clearColor, 0, nullptr);

    // 深度ステンシルビューをクリア
    m_pCmdList->ClearDepthStencilView(m_HandleDSV, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void SystemDirectX12::BeforeRender(float r, float g, float b)
{
    // コマンドの記録を開始
    m_pCmdAllocator[m_FrameIndex]->Reset();
    m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex], nullptr);

    // リソースバリアの書き込み設定
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;   // リソースバリアのタイプ
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;         // フラグ設定
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];       // 遷移に使用するリソースのポインタ
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_PRESENT;             // サブリソースの使用前の状態
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_RENDER_TARGET;       // サブリソースの使用後の状態
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;  // 遷移の為のサブリソースの番号

    // リソースバリア
    m_pCmdList->ResourceBarrier(1, &barrier);

    // レンダーターゲットの設定
    m_pCmdList->OMSetRenderTargets(1, &m_HandleRTV[m_FrameIndex], FALSE, &m_HandleDSV);

    // クリアカラーの設定
    float clearColor[] = { r, g, b, 1.0f };

    // レンダーターゲットビューをクリア
    m_pCmdList->ClearRenderTargetView(m_HandleRTV[m_FrameIndex], clearColor, 0, nullptr);

    // 深度ステンシルビューをクリア
    m_pCmdList->ClearDepthStencilView(m_HandleDSV, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void SystemDirectX12::AfterRender()
{
    // リソースバリアの表示設定
    D3D12_RESOURCE_BARRIER barrier = {};

    barrier.Type                    = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                   = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource    = m_pColorBuffer[m_FrameIndex];
    barrier.Transition.StateBefore  = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter   = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource  = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // リソースバリア
    m_pCmdList->ResourceBarrier(1, &barrier);

    // コマンドの記録を終了
    m_pCmdList->Close();

    // コマンドを実行
    ID3D12CommandList* ppCmdLists[] = { m_pCmdList };
    m_pQueue->ExecuteCommandLists(1, ppCmdLists);

    // 画面に表示
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

    // シグナル処理
    m_pQueue->Signal(m_pFence, m_FenceCounter[m_FrameIndex]);

    // 完了時にイベントを設定する
    m_pFence->SetEventOnCompletion(m_FenceCounter[m_FrameIndex], m_FenceEvent);

    // 待機処理
    WaitForSingleObjectEx(m_FenceEvent, INFINITE, FALSE);

    // カウンターを増やす
    m_FenceCounter[m_FrameIndex]++;
}

void SystemDirectX12::Present(uint32_t _interval)
{
    // 画面に表示
    m_pSwapChain->Present(_interval, 0);

    // シグナル処理
    const auto currentValue = m_FenceCounter[m_FrameIndex];
    m_pQueue->Signal(m_pFence, currentValue);

    // バックバッファ番号を更新
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

    // 次のフレームの描画準備がまだであれば待機する
    if (m_pFence->GetCompletedValue() < m_FenceCounter[m_FrameIndex])
    {
        m_pFence->SetEventOnCompletion(m_FenceCounter[m_FrameIndex], m_FenceEvent);
        WaitForSingleObjectEx(m_FenceEvent, INFINITE, FALSE);
    }

    // 次のフレームのフェンスカウンターを増やす
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
