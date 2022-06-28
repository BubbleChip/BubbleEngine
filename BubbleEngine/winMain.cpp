#include "gtest/gtest.h"
#include "BubbleEngineLibrary.h"
#include <thread>

class TestApplication : public BEApp
{
public:
	TestApplication()
		: window(nullptr)
		, graphicsDevice(nullptr)
	{}

	void OnInitialize() override
	{
		window = BEWindow::CreatePlatformWindow();
		window->Create();
		window->Show();

		graphicsDevice = BEGraphicsDevice::CreateGraphicsDevice();
		commandQueue = graphicsDevice->CreateCommandQueue();
		swapChain = commandQueue->CreateSwapChain(window);

		vertexBuffer = graphicsDevice->CreateGPUBuffer(50000, BEGPUBuffer::CPUCacheMode::WriteCombined);

		BETextureDescriptor whiteTextureDesc;
		whiteTextureDesc.type = BETexture::Type2D;
		whiteTextureDesc.format = BEPixelFormat::RGBA8Unorm;
		whiteTextureDesc.width = 4; // texture minimum size.
		whiteTextureDesc.height = 4; // texture minimum size.
		whiteTextureDesc.depth = 1;
		whiteTextureDesc.mipmapLevelCount = 1;
		whiteTextureDesc.sampleCount = 1;
		whiteTextureDesc.usage = BETexture::UsageShaderRead;
		whiteTexture = graphicsDevice->CreateTexture(whiteTextureDesc);

		//Add Pipeline
		vertexShader = graphicsDevice->CreateShader(L"Resource/SimpleShader.hlsl", "VS", BEShader::StageType::Vertex);
		pixelShader = graphicsDevice->CreateShader(L"Resource/SimpleShader.hlsl", "PS", BEShader::StageType::Fragment);

		BERenderPipelineDescriptor descriptor{};
		descriptor.sampleCount = 1;
		descriptor.vertexShader = vertexShader;
		descriptor.fragmentShader = pixelShader;
		descriptor.vertexDescriptor.attributes = {
			{BEVertexFormat::Float3, "POSITION", 0, 0},
			{BEVertexFormat::Float3, "NORMAL", 0, 12 },
			{BEVertexFormat::Float4, "COLOR", 0, 24 },
		};
		descriptor.colorAttachments = { { BEPixelFormat::RGBA8Unorm, false } };
		descriptor.depthStencilAttachmentPixelFormat = BEPixelFormat::Depth24UnormStencil8;
		descriptor.inputPrimitiveTopology = BEPrimitiveTopologyType::Triangle;

		renderPipeline = graphicsDevice->CreateRenderPipeline(descriptor);


		loopThread = std::jthread([this](std::stop_token token)
			{
				while (!token.stop_requested())
				{
					Update();
					Draw();
				}
			});
	}

	void OnTerminate() override
	{
		loopThread.request_stop();
		loopThread.join();
	}

	void Update()
	{

	}

	void Draw()
	{
		if (BEObject<BECommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
		{
			if (BEObject<BERenderCommandEncoder> encoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
			{
				BEViewport viewport(0, 0, (float)window->Width(), (float)window->Height(), 0.f, 1.f);
				encoder->SetViewport(viewport);

				BERect scissorRect(0, 0, (float)window->Width(), (float)window->Height());
				encoder->SetScissorRect(scissorRect);

				encoder->ClearRenderTargetView(swapChain->CurrentColorTexture(), BELinearColor(0.0f, 0.0f, 1.0f, 1.0f));
				encoder->ClearDepthStencilView(swapChain->DepthStencilTexture(), BERenderCommandEncoder::DepthStencilClearFlag::All, 1.f, 0);

				encoder->SetRenderTargets({ swapChain->CurrentColorTexture() }, swapChain->DepthStencilTexture());

				encoder->EndEncoding();
			}

			commandBuffer->Commit();
		}

		swapChain->Present();
		commandQueue->WaitComplete();
	}

private:
	std::jthread loopThread;

	BEObject<BEWindow> window;
	BEObject<BEGraphicsDevice> graphicsDevice;
	BEObject<BECommandQueue> commandQueue;
	BEObject<BESwapChain> swapChain;
	BEObject<BERenderPipeline> renderPipeline;

	BEObject<BEGPUBuffer> vertexBuffer;
	BEObject<BETexture> whiteTexture;

	BEObject<BEShader> vertexShader;
	BEObject<BEShader> pixelShader;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}