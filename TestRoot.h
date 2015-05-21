#pragma once
class TestRoot
{
public:
	IDirect3DDevice9* Device;
	virtual bool setup() = 0;
	virtual bool cleanup() = 0;
	virtual bool display(float timeDelta) = 0;

	TestRoot(IDirect3DDevice9* device)
	{
		this->Device = device;
	}

	virtual ~TestRoot(void)
	{
	}
};

