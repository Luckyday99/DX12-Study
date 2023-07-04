#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexBuffer)
{
	_vertexCount = static_cast<uint32>(vertexBuffer.size());
	_vertexSize = _vertexCount * sizeof(Vertex);
	_indexCount = static_cast<uint32>(indexBuffer.size());
	_indexSize = _indexCount * sizeof(uint32);

	CreateVBVBuffer(vertexBuffer);
	CreateVBV();
	CreateIBVBuffer(indexBuffer);
	CreateIBV();
}

void Mesh::CreateVBVBuffer(const vector<Vertex>& vertexBuffer)
{
	// GPU�� �޸� �Ҵ� ��û
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD); // Upload / Default type �и� or Upload type �������� ���
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(_vertexSize);

	DEVICE->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer)); // GPU ����

	// CPU ram map -> GPU ram copy -> unmap
	void* vertexDataBuffer = nullptr; // Ram ���� �Ҵ�
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	// Ram ���� -> GPU �������� ���� -> unmap
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &vertexBuffer[0], _vertexSize);
	_vertexBuffer->Unmap(0, nullptr);
}

void Mesh::CreateVBV()
{
	// Initialize the vertex buffer view.
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex); // ���� 1�� ũ��
	_vertexBufferView.SizeInBytes = _vertexSize; // ������ ũ��	
}

void Mesh::CreateIBVBuffer(const vector<uint32>& indexBuffer)
{
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD); // Upload / Default
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(_indexSize);

	DEVICE->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_indexBuffer));

	// CPU ram map -> GPU ram copy -> unmap
	void* indexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_indexBuffer->Map(0, &readRange, &indexDataBuffer);
	::memcpy(indexDataBuffer, &indexBuffer[0], _indexSize);
	_indexBuffer->Unmap(0, nullptr);
}

void Mesh::CreateIBV()
{
	_indexBufferView.BufferLocation = _indexBuffer->GetGPUVirtualAddress();
	_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	_indexBufferView.SizeInBytes = _indexSize;
}


void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)
	CMD_LIST->IASetIndexBuffer(&_indexBufferView);

	GENGINE->GetTableDescHeap()->CommitTable();

	CMD_LIST->DrawIndexedInstanced(_indexCount, 1, 0, 0, 0); // Instancing? �� ����
}