//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: d3dUtility.h
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Provides utility functions for simplifying common tasks.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __d3dUtilityH__
#define __d3dUtilityH__

#include <d3dx9.h>
#include "../TestRoot.h"
#include "../TestObjects.h"
#include <string>
#pragma comment( lib,"winmm.lib" )
#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib,"d3dx9.lib")

class TestRoot;
class Vertex{
public:
	float x,y,z;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE;
	Vertex(){};
	Vertex(float _x,float _y,float _z,D3DCOLOR _color){
		x = _x;y = _y;z = _z;color = _color;	
	};
};

class VertexEx{
public:
	float x,y,z;
	float na,ny,nz;
	float tx,ty;
	static const DWORD FVF = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1;
	VertexEx(){};
	VertexEx(float _x,float _y,float _z,float _tx,float _ty){
		x = _x;y = _y;z = _z;
		tx = _tx;ty = _ty;
	};
	
	
};

namespace d3d
{
	const D3DXCOLOR WHITE = D3DCOLOR_XRGB(255,255,255);
	const D3DXCOLOR BLACK = D3DCOLOR_XRGB(0,0,0);
	const D3DXCOLOR RED = D3DCOLOR_XRGB(255,0,0);
	const D3DXCOLOR GREEN = D3DCOLOR_XRGB(0,255,0);
	const D3DXCOLOR BLUE = D3DCOLOR_XRGB(0,0,255);
	const D3DXCOLOR YELLOW = D3DCOLOR_XRGB(255,255,0);

	D3DMATERIAL9 initMtrl(D3DXCOLOR a,D3DXCOLOR d,D3DXCOLOR s,D3DXCOLOR e,float p);
	const D3DMATERIAL9 WHITE_MATERIAL = initMtrl(WHITE,WHITE,WHITE,BLACK,8.0f);
	const D3DMATERIAL9 BLACK_MATERIAL = initMtrl(BLACK,BLACK,BLACK,BLACK,8.0f);
	const D3DMATERIAL9 RED_MATERIAL = initMtrl(RED,RED,RED,BLACK,8.0f);
	const D3DMATERIAL9 GREEN_MATERIAL = initMtrl(GREEN,GREEN,GREEN,BLACK,8.0f);
	const D3DMATERIAL9 BLUE_MATERIAL = initMtrl(BLUE,BLUE,BLUE,BLACK,8.0f);
	const D3DMATERIAL9 YELLOW_MATERIAL = initMtrl(YELLOW,YELLOW,YELLOW,BLACK,8.0f);

	

	D3DLIGHT9 initDirectonalLight(D3DXVECTOR3* dir,D3DXCOLOR* color);
	D3DLIGHT9 initPointLight(D3DXVECTOR3* pos,D3DXCOLOR* color);
	D3DLIGHT9 initSpotLight(D3DXVECTOR3* pos,D3DVECTOR* dir,D3DXCOLOR* color);

	void computNormal(D3DXVECTOR3* p1,D3DXVECTOR3* p2,D3DXVECTOR3* p3,D3DXVECTOR3* out);

	bool InitD3D(
		HINSTANCE hInstance,       // [in] Application instance.
		int width, int height,     // [in] Backbuffer dimensions.
		bool windowed,             // [in] Windowed (true)or full screen (false).
		D3DDEVTYPE deviceType,     // [in] HAL or REF
		IDirect3DDevice9** device);// [out]The created device.

	int EnterMsgLoop(TestRoot* test);

	

	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg, 
		WPARAM wParam,
		LPARAM lParam);

	template<class T> void Release(T t)
	{
		if( t )
		{
			t->Release();
			t = 0;
		}
	}
		
	template<class T> void Delete(T t)
	{
		if( t )
		{
			delete t;
			t = 0;
		}
	}
}

#endif // __d3dUtilityH__