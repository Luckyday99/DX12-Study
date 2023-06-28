#pragma once

// � �޸𸮸� ����� ������... ��


// Constant Buffer
// root constant(���), root descriptor(�����Ͷ� ���), root table(� �������� �������)

class RootSignature
{
public:

	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature>	GetSignature() { return _signature; }

private:

	void CreateSamplerDesc();
	void CreateRootSignature(ComPtr<ID3D12Device> device);

private:

	D3D12_STATIC_SAMPLER_DESC	_samplerDesc;
	ComPtr<ID3D12RootSignature> _signature;
};

