#pragma once
#include "src\d3dUtility.h"

class d3dtest3:public TestRoot
{
public:

	

	IDirect3DVertexBuffer9* vb;
	IDirect3DIndexBuffer9* ib;

	/*static const int screen_width = 800;
	static const int screen_height = 600;*/

	ID3DXMesh* teapot; 

	bool setup();
	bool cleanup();
	bool display(float timeDelta);

	d3dtest3(IDirect3DDevice9* device);
	~d3dtest3(void);
};

class d3dtest5:public TestRoot
{
public:

	/*static const int screen_width = 800;
	static const int screen_height = 600;*/

	ID3DXMesh* Objects[4];
	D3DXMATRIX Worlds[4];
	D3DMATERIAL9 Mtrls[4];

	bool setup();
	bool cleanup();
	bool display(float timeDelta);

	d3dtest5(IDirect3DDevice9* device);
	~d3dtest5(void);
};

class d3dtest6:public TestRoot
{
public:

	/*static const int screen_width = 800;
	static const int screen_height = 600;*/

	IDirect3DVertexBuffer9* lp_buffer;
	IDirect3DIndexBuffer9* lp_index;
	IDirect3DTexture9* lp_texture;

	bool setup();
	bool cleanup();
	bool display(float timeDelta);

	d3dtest6(IDirect3DDevice9* device);
	~d3dtest6(void);
};