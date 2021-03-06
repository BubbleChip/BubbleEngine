#include "SwapChain.h"
#include "Window/BEWindow.h"
#include "CommandQueue.h"

SwapChain::SwapChain(GraphicsDevice* _device, CommandQueue* _queue, const BEWindow* _window)
	: width(_window->Width())
	, height(_window->Height())
	, currentColorTextureIndex(0)
	, swapChain(nullptr)
	, device(_device)
{
    DXGI_SWAP_CHAIN_DESC1 desc{};
    desc.Width = width;
    desc.Height = height;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferCount = FRAME_BUFFER_COUNT;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Scaling = DXGI_SCALING_NONE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    ComPtr<IDXGISwapChain1> swapChain1;
    ThrowIfFailed(device->Factory()->CreateSwapChainForHwnd(
        _queue->Queue(),
        reinterpret_cast<HWND>(_window->PlatformHandle()),
        &desc,
        nullptr,
        nullptr,
        swapChain1.GetAddressOf()));

    ThrowIfFailed(swapChain1.As(&swapChain));
    currentColorTextureIndex = swapChain->GetCurrentBackBufferIndex();

    SetupColorTextures();
    SetupDepthStencil();
}

void SwapChain::Resize(uint32_t _width, uint32_t _height)
{
    if (this->width != _width || this->height != _height)
    {
        this->width = _width;
        this->height = _height;

        // Clear resources
        for (int i = 0; i < FRAME_BUFFER_COUNT; ++i)
            colorTexture[i] = nullptr;
        depthStencilTexture = nullptr;

        DXGI_SWAP_CHAIN_DESC desc{};
        swapChain->GetDesc(&desc);
        ThrowIfFailed(swapChain->ResizeBuffers(
            FRAME_BUFFER_COUNT,
            _width, _height,
            desc.BufferDesc.Format,
            desc.Flags));

        // Reset the frame index to the current back buffer index.
        currentColorTextureIndex = swapChain->GetCurrentBackBufferIndex();

        SetupColorTextures();
        SetupDepthStencil();
    }
}

const BETexture* SwapChain::CurrentColorTexture() const
{
    return colorTexture[currentColorTextureIndex];
}

const BETexture* SwapChain::DepthStencilTexture() const
{
    return depthStencilTexture;
}

void SwapChain::Present()
{
    // swap the back and front buffers
    ThrowIfFailed(swapChain->Present(0, 0));
    currentColorTextureIndex = (currentColorTextureIndex + 1) % FRAME_BUFFER_COUNT;
}

void SwapChain::SetupColorTextures()
{
    for (UINT i = 0; i < FRAME_BUFFER_COUNT; ++i)
    {
        ComPtr<ID3D12Resource> buffer;
        ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&buffer)));
        colorTexture[i] = new Texture(buffer.Get(), D3D12_RESOURCE_STATE_PRESENT);

        D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        heapDesc.NodeMask = 0;
        heapDesc.NumDescriptors = 1;

        ComPtr<ID3D12DescriptorHeap> descriptorHeap;
        ThrowIfFailed(device->Device()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

        D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
        rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

        device->Device()->CreateRenderTargetView(buffer.Get(), &rtvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
        colorTexture[i]->SetRenderTargetViewHeap(descriptorHeap.Get());
    }
}

void SwapChain::SetupDepthStencil()
{
    BETextureDescriptor desc;
    desc.type = Texture::Type2D;
    desc.format = BEPixelFormat::Depth24UnormStencil8;
    desc.width = width;
    desc.height = height;
    desc.depth = 1;
    desc.mipmapLevelCount = 1;
    desc.sampleCount = 1;
    desc.usage = Texture::UsageDepthStencil;
    depthStencilTexture = device->CreateTexture(desc).DynamicCast<Texture>();
}