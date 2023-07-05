#pragma once

#include "Device.h"			// ���� �ٽ����� �κ�
#include "CommandQueue.h"	// ��û�� ������, CommandQueue�� ���ļ� �ѹ��� ����
#include "SwapChain.h"		// ���� ���۸�(GPU�� ���� <-> ���� ȭ�� ��� �����ư��� ����
							// GPU�� ��û�� View(���ҽ��� ���� ����)�� ����
#include "RootSignature.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"
#include "DepthStencilBuffer.h"

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Engine
{
public:

	void Init(const WindowInfo& window);

public:

	void Update();

	void Render();

public:

	shared_ptr<Device> GetDevice() { return _device; }
	shared_ptr<CommandQueue> GetCmdQueue() { return _cmdQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	shared_ptr<DepthStencilBuffer> GetDSBuffer() { return _dsBuffer; }
	shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return _tableDescHeap; }
	shared_ptr<ConstantBuffer>	GetCstBuffer(CONSTANT_BUFFER_TYPE type) { return _cstBuffers[static_cast<uint8>(type)]; }

public:

	void ResizeWindow(int32 width, int32 height);

	void RenderBegin();
	void RenderEnd();

private:

	void CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count);
	void ShowFps();

private:

	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	shared_ptr<Device>				_device = make_shared<Device>();
	shared_ptr<CommandQueue>		_cmdQueue = make_shared<CommandQueue>();
	shared_ptr<SwapChain>			_swapChain = make_shared<SwapChain>();
	shared_ptr<RootSignature>		_rootSignature = make_shared<RootSignature>();
	vector<shared_ptr<ConstantBuffer>>		_cstBuffers = {};
	shared_ptr<TableDescriptorHeap> _tableDescHeap = make_shared<TableDescriptorHeap>();
	shared_ptr<DepthStencilBuffer>	_dsBuffer = make_shared<DepthStencilBuffer>();
};

