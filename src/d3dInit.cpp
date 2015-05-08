//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: d3dinit.cpp
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Demonstrates how to initialize Direct3D, how to use the book's framework
//       functions, and how to clear the screen to black.  Note that the Direct3D
//       initialization code is in the d3dUtility.h/.cpp files.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"

//
// Globals
//

IDirect3DDevice9* Device = 0; 

IDirect3DVertexBuffer9* vb = NULL;
IDirect3DIndexBuffer9* ib = NULL;

const int screen_width = 800;
const int screen_height = 600;

ID3DXMesh* teapot = NULL; 


//
// Framework Functions
//

bool Setup()
{
	// Nothing to setup in this sample.
	Device->CreateVertexBuffer(8*sizeof(Vertex),D3DUSAGE_WRITEONLY,Vertex::FVF,D3DPOOL_MANAGED,&vb,0);
	Device->CreateIndexBuffer(36*sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&ib,0);
	Vertex* v;
	vb->Lock(0,0,(void**)&v,0);
	v[0] = Vertex(-1.0f, -1.0f, -1.0f,D3DCOLOR_XRGB(255,0,0));
	v[1] = Vertex(-1.0f,  1.0f, -1.0f,D3DCOLOR_XRGB(255,0,0));
	v[2] = Vertex( 1.0f,  1.0f, -1.0f,D3DCOLOR_XRGB(255,0,0));
	v[3] = Vertex( 1.0f, -1.0f, -1.0f,D3DCOLOR_XRGB(255,0,0));
	v[4] = Vertex(-1.0f, -1.0f,  1.0f,D3DCOLOR_XRGB(255,0,0));
	v[5] = Vertex(-1.0f,  1.0f,  1.0f,D3DCOLOR_XRGB(255,0,0));
	v[6] = Vertex( 1.0f,  1.0f,  1.0f,D3DCOLOR_XRGB(255,0,0));
	v[7] = Vertex( 1.0f, -1.0f,  1.0f,D3DCOLOR_XRGB(255,0,0));
	vb->Unlock();
	WORD* indices = 0;
	ib->Lock(0,0,(void**)&indices,0);
	indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
	indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

	// back side
	indices[6]  = 4; indices[7]  = 6; indices[8]  = 5;
	indices[9]  = 4; indices[10] = 7; indices[11] = 6;

	// left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;
	ib->Unlock();

	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX M;
	D3DXMatrixLookAtLH(&M,&position,&target,&up);
	Device->SetTransform(D3DTS_VIEW,&M);
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj,D3DX_PI*0.5f,(float)screen_width/(float)screen_height,1.0f,1000.0f);
	Device->SetTransform(D3DTS_PROJECTION,&proj);
	Device->SetRenderState(D3DRS_LIGHTING,false);
	Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);

	D3DXCreateTeapot(Device,&teapot,0);

	return true;
}

void Cleanup()
{
	d3d::Release(vb);
	d3d::Release(ib);
	// Nothing to cleanup in this sample.
}

bool Display(float timeDelta)
{
	if( Device ) // Only use Device methods if we have a valid device.
	{
		D3DXMATRIX rx,ry;
		D3DXMatrixRotationX(&rx,3.14f/4.0f);
		static float y = 0.0f;
		D3DXMatrixRotationY(&ry,y);
		y += timeDelta;
		if(y>=6.28f)y = 0.0f;
		D3DXMATRIX p = rx*ry;
		Device->SetTransform(D3DTS_WORLD,&p);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
		Device->BeginScene();
		Device->SetStreamSource(0,vb,0,sizeof(Vertex));
		Device->SetIndices(ib);
		Device->SetFVF(Vertex::FVF);
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,8,0,12);
		teapot->DrawSubset(0);
		Device->EndScene();
		// Swap the back and front buffers.
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		640, 480, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}