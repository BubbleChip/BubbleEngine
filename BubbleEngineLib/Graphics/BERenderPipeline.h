#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BEObject.h"
#include "BEVertexDescriptor.h"
#include "BEBlendState.h"
#include "BEShader.h"
#include "BEPixelFormat.h"
#include <vector>

class BEL_API BERenderPipeline : public BERefCounter
{
public:
	BERenderPipeline() = default;
	virtual ~BERenderPipeline() noexcept = default;
};

enum class BEPrimitiveTopologyType
{
	Point,
	Line,
	Triangle
};

struct BERenderPipelineColorAttachmentDescriptor
{
	BEPixelFormat pixelFormat;

	bool blendingEnabled;

	BEBlendOperation alphaBlendOperation;
	BEBlendFactor sourceAlphaBlendFactor;
	BEBlendFactor destinationAlphaBlendFactor;

	BEBlendOperation rgbBlendOperation;
	BEBlendFactor sourceRGBBlendFactor;
	BEBlendFactor destinationRGBBlendFactor;

	BEColorWriteMask writeMask = BEColorWriteMask::ColorWriteMaskAll;
};

struct BERenderPipelineDescriptor
{
	uint32_t sampleCount;
	BEObject<BEShader> vertexShader;
	BEObject<BEShader> fragmentShader;

	BEVertexDescriptor vertexDescriptor;
	std::vector<BERenderPipelineColorAttachmentDescriptor> colorAttachments;
	BEPixelFormat depthStencilAttachmentPixelFormat;

	BEPrimitiveTopologyType inputPrimitiveTopology;
};