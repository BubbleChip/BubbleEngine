#include "gtest/gtest.h"
#include "BubbleEngineLibrary.h"
#include <thread>
#include "tiny_obj_loader.h"

struct Vertex
{
	BEVector3 pos;
	BEVector3 normal;
	BELinearColor color;
};

struct StaticMesh
{
	std::vector<Vertex>		vertices;
	BEObject<BEGPUBuffer>	vertexBuffer;
};

struct Constants
{
	BEMatrix4 worldViewProj;
};

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

		camera.SetupViewMatrix(BEVector3{ 0.f, 0.f, -10.f }, BEVector3{}, BEVector3{ 0.f, 0.f, 0.f });
		camera.SetPerspective(0.25f * 3.1415926535f, window->AspectRatio(), 1.0f, 1000.f);

		Constants constants;
		constants.worldViewProj = camera.ViewMatrix() * camera.ProjectionMatrix();

		// Update the constant buffer with the latest worldViewProj matrix.
		constantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(Constants), BEGPUBuffer::CPUCacheMode::WriteCombined);
		constantsBuffer->WriteData(&constants, sizeof(Constants));

		LoadTestModel();

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

				encoder->SetConstantBuffer(0, constantsBuffer);

				for (const StaticMesh& mesh : staticMeshes)
				{
					encoder->SetVertexBuffer(mesh.vertexBuffer, sizeof(Vertex));

					encoder->DrawPrimitives(BERenderCommandEncoder::PrimitiveType::Triangle,
						(uint32_t)mesh.vertices.size(), 1, 0, 0);
				}

				encoder->EndEncoding();
			}

			commandBuffer->Commit();
		}

		swapChain->Present();
		commandQueue->WaitComplete();
	}

	void LoadTestModel()
	{
		tinyobj::ObjReader reader;
		if (!reader.ParseFromFile("Resource/Meshes/cube.obj"))
		{
			//reader error
			EXPECT_EQ(0, 1);
		}

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();
		auto& materials = reader.GetMaterials();

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); ++s)
		{
			std::vector<Vertex> vertices;
			vertices.reserve(shapes[s].mesh.num_face_vertices.size() * 3);

			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f)
			{
				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; ++v)
				{
					Vertex vertex{};

					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					// access to vertex
					vertex.pos = BEVector3(attrib.vertices[3 * size_t(idx.vertex_index) + 0],
						attrib.vertices[3 * size_t(idx.vertex_index) + 1],
						attrib.vertices[3 * size_t(idx.vertex_index) + 2]);

					// Check if `normal_index` is zero or positive. negative = no normal data
					if (idx.normal_index >= 0) {
						vertex.normal = BEVector3(attrib.normals[3 * size_t(idx.normal_index) + 0],
							attrib.normals[3 * size_t(idx.normal_index) + 1],
							attrib.normals[3 * size_t(idx.normal_index) + 2]);
					}

					// Check if `texcoord_index` is zero or positive. negative = no texcoord data
					/*if (idx.texcoord_index >= 0) {
						tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
						tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					}*/

					// Optional: vertex colors
					vertex.color = BELinearColor(attrib.colors[3 * size_t(idx.vertex_index) + 0],
						attrib.colors[3 * size_t(idx.vertex_index) + 1],
						attrib.colors[3 * size_t(idx.vertex_index) + 2],
						1.f);

					vertices.push_back(vertex);
				}
				index_offset += fv;
			}

			auto length = vertices.size() * sizeof(BEGPUBuffer);
			BEObject<BEGPUBuffer> vertexBuffer = graphicsDevice->CreateGPUBuffer(length, BEGPUBuffer::CPUCacheMode::WriteCombined);
			vertexBuffer->WriteData(vertices.data(), length);
			staticMeshes.push_back({ vertices, vertexBuffer });
		}
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

	BECamera camera;
	std::vector<StaticMesh> staticMeshes;
	BEObject<BEGPUBuffer> constantsBuffer;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}