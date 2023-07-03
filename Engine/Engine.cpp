#include "pch.h"
#include "Engine.h"


void Engine::Init(const WindowInfo& window)
{
	_window = window;
	GINPUT->Init(window.hwnd);

	// �׷��� ȭ�� ũ�⸦ ����
	_viewport = { 0, 0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, window.width, window.height);

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(window, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCmdQueue());
	_rootSignature->Init(_device->GetDevice());
	_dsBuffer->Init(window);
	_tableDescHeap->Init(256);

	_timer->Init();

	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(Transform), 256);
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(MaterialParams), 256);

	// Create Mesh
	vector<Vertex> vertex(4);
	{
		vertex[0].pos = Vec3(-0.5f, 0.5f, 0.5f);
		vertex[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
		vertex[0].uv = Vec2(0.f, 0.f);
	}
	{
		vertex[1].pos = Vec3(0.5f, 0.5f, 0.5f);
		vertex[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vertex[1].uv = Vec2(1.f, 0.f);
	}
	{
		vertex[2].pos = Vec3(0.5f, -0.5f, 0.5f);
		vertex[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
		vertex[2].uv = Vec2(1.f, 1.f);
	}
	{
		vertex[3].pos = Vec3(-0.5f, -0.5f, 0.5f);
		vertex[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vertex[3].uv = Vec2(0.f, 1.f);
	}

	vector<uint32> index;
	{
		index.push_back(0);
		index.push_back(1);
		index.push_back(2);
	}
	{
		index.push_back(0);
		index.push_back(2);
		index.push_back(3);
	}

	_mesh->Init(vertex, index);

	shared_ptr<Shader> shader = make_shared<Shader>();
	shared_ptr<Texture> texture = make_shared<Texture>();
	shader->Init(L"..\\Resources\\Shader\\default.hlsli");
	texture->Init(L"..\\Resources\\Texture\\Kitty.jpg");

	shared_ptr<Material> material = make_shared<Material>();
	material->SetShader(shader);
	material->SetFloat(0, 0.3f);
	material->SetFloat(1, 0.4f);
	material->SetFloat(2, 0.3f);
	material->SetTexture(0, texture);
	_mesh->SetMaterial(material);

	GENGINE->GetCmdQueue()->WaitSync();

	ResizeWindow(window.width, window.height);
}

void Engine::Render()
{
	RenderBegin();

	// ������ �� ����

	{
		static Transform t;
		float speed = 1.f;

		if (GINPUT->GetButton(KEY_TYPE::W))
			t.offset.y += speed * DELTA_TIME;
		if (GINPUT->GetButton(KEY_TYPE::S))
			t.offset.y -= speed * DELTA_TIME;
		if (GINPUT->GetButton(KEY_TYPE::D))
			t.offset.x += speed * DELTA_TIME;
		if (GINPUT->GetButton(KEY_TYPE::A))
			t.offset.x -= speed * DELTA_TIME;

		_mesh->SetTransform(t);

		_mesh->Render();
	}

	RenderEnd();
}

void Engine::Update()
{
	GINPUT->Update();
	_timer->Update();

	ShowFps();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	RECT rect = { 0, 0, width, height };
	_window.width = width;
	_window.height = height;

	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);

	_dsBuffer->Init(_window);
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}

void Engine::CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count)
{
	uint8 typeint = static_cast<REGISTER_TYPE>(reg);
	assert(_cstBuffers.size() == typeint);

	shared_ptr<ConstantBuffer> cstBuffer = make_shared<ConstantBuffer>();
	cstBuffer->Init(reg, bufferSize, count);
	_cstBuffers.push_back(cstBuffer);
}

void Engine::ShowFps()
{
	uint32 fps = _timer->GetFps();

	WCHAR text[100] = L"";
	::wsprintf(text, L"FPS : %d", fps);

	::SetWindowText(_window.hwnd, text);
}