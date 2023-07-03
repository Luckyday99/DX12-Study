#pragma once

#include "Device.h"			// ���� �ٽ����� �κ�
#include "CommandQueue.h"	// ��û�� ������, CommandQueue�� ���ļ� �ѹ��� ����
#include "SwapChain.h"		// ���� ���۸�(GPU�� ���� <-> ���� ȭ�� ��� �����ư��� ����
							// GPU�� ��û�� View(���ҽ��� ���� ����)�� ����
#include "RootSignature.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"
#include "DepthStencilBuffer.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "Input.h"
#include "Timer.h"

class Engine
{
public:

	void Init(const WindowInfo& window);
	void Render();

public:

	void Update();

public:

	shared_ptr<Device> GetDevice() { return _device; }
	shared_ptr<CommandQueue> GetCmdQueue() { return _cmdQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	shared_ptr<ConstantBuffer>	GetCstBuffer() { return _cstBuffer; }
	shared_ptr<DepthStencilBuffer> GetDSBuffer() { return _dsBuffer; }
	shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return _tableDescHeap; }

	shared_ptr<Timer> GetTimer() { return _timer; }

public:

	void ResizeWindow(int32 width, int32 height);

	void RenderBegin();
	void RenderEnd();

private:

	void ShowFps();

private:

	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	shared_ptr<Device>				_device = make_shared<Device>();
	shared_ptr<CommandQueue>		_cmdQueue = make_shared<CommandQueue>();
	shared_ptr<SwapChain>			_swapChain = make_shared<SwapChain>();
	shared_ptr<RootSignature>		_rootSignature = make_shared<RootSignature>();
	shared_ptr<ConstantBuffer>		_cstBuffer = make_shared<ConstantBuffer>();
	shared_ptr<TableDescriptorHeap> _tableDescHeap = make_shared<TableDescriptorHeap>();
	shared_ptr<DepthStencilBuffer>	_dsBuffer = make_shared<DepthStencilBuffer>();

	shared_ptr<Mesh> _mesh = make_shared<Mesh>();
	shared_ptr<Shader> _shader = make_shared<Shader>();
	shared_ptr<Texture> _texture = make_shared<Texture>();

	shared_ptr<Timer>	_timer = make_shared<Timer>();
};

