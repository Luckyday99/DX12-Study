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

	ComPtr<ID3D12RootSignature> _signature;

};

