#pragma once

#include "Device.h"			// ���� �ٽ����� �κ�
#include "CommandQueue.h"	// ��û�� ������, CommandQueue�� ���ļ� �ѹ��� ����
#include "SwapChain.h"		// ���� ���۸�(GPU�� ���� <-> ���� ȭ�� ��� �����ư��� ����
							// GPU�� ��û�� View(���ҽ��� ���� ����)�� ����
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"

class Engine
{
public:

	void Init(const WindowInfo& window);
	void Render();

public:

	shared_ptr<Device> GetDevice() { return _device; }
	shared_ptr<CommandQueue> GetCmdQueue() { return _cmdQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	shared_ptr<ConstantBuffer>	GetCstBuffer() { return _cstBuffer; };
	shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return _tableDescHeap; }

public:

	void ResizeWindow(int32 width, int32 height);

	void RenderBegin();
	void RenderEnd();

private:

	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	shared_ptr<Device>				_device;
	shared_ptr<CommandQueue>		_cmdQueue;
	shared_ptr<SwapChain>			_swapChain;
	shared_ptr<RootSignature>		_rootSignature;
	shared_ptr<ConstantBuffer>		_cstBuffer;
	shared_ptr<TableDescriptorHeap> _tableDescHeap;
};

