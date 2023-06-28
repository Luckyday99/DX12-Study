#pragma once

class SwapChain;

// CommandQueue : DX12�� ����
// ��û�� CMD LIST�� ��Ƽ� �ѹ��� GPU�� ����
class CommandQueue
{
public:

	~CommandQueue();
	
	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	void FlushResourceCommandQueue();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return _cmdList; }
	ComPtr<ID3D12GraphicsCommandList> GetResCmdList() { return _resCmdList; }

private:

	ComPtr<ID3D12CommandQueue>			_cmdQueue;

	// CommandList�� Close / Open ���°� �ִµ�
	// Open ���¿��� Command�� �ִٰ� Close�� ���� �����ϴ� ����
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;
	
	// ���ҽ� �۾��� Ŀ��� ����Ʈ(�������Ҷ� �Ź� ���� ���� �ʿ䰡 ����)
	// Command List�� �� �ϳ��� �ʿ䰡 ����!
	// ==> Cmd List�� ��ü�� ���� ���°� �� ���� ����?
	ComPtr<ID3D12CommandAllocator>		_resCmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_resCmdList;

	// ��Ƽ�����带 ���� fence�� �̿�
	// CPU / GPU ����ȭ�� ���� ������ ����
	// GPU�� ���� ���������� CPU�� ���(WaitSync)�ϴ� ������� ����(ȿ�� ����)
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>		_swapChain;
};