#pragma once
#include "Graphics/BEShader.h"
#include "d3dx12Include.h"
#include <string>

class Shader final : public BEShader
{
public:
    Shader(ID3DBlob* byteCode, BEShader::StageType stage, const std::string& entry);
    ~Shader() noexcept = default;

    D3D12_SHADER_BYTECODE ByteCode() const;

private:
    BEShader::StageType stage;
    std::string entry;
    ComPtr<ID3DBlob> byteCode;
};
