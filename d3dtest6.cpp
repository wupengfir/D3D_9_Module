#include "TestObjects.h"
extern int screen_width;
extern int screen_height;
IDirect3DTexture9* Tex = 0;
bool d3dtest6::setup(){
	Device->CreateVertexBuffer(4*sizeof(VertexEx),0,VertexEx::FVF,D3DPOOL_MANAGED,&lp_buffer,0);
	Device->CreateIndexBuffer(6*sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&lp_index,0);

	VertexEx* vertices;
	lp_buffer->Lock(0,0,(void**)&vertices,0);
	vertices[0] = VertexEx(-1,1,-1,0,0);
	vertices[1] = VertexEx(1,1,-1,1,0);
	vertices[2] = VertexEx(-1,-1,-1,0,1);
	vertices[3] = VertexEx(1,-1,-1,1,1);
	lp_buffer->Unlock();

	WORD* indices;
	lp_index->Lock(0,0,(void**)&indices,0);
	indices[0] = 0;indices[1] = 1;indices[2] = 2;
	indices[3] = 1;indices[4] = 3;indices[5] = 2;
	lp_index->Unlock();

	D3DXVECTOR3 positon(0,0,-5);
	D3DXVECTOR3 target(0,0,0);
	D3DXVECTOR3 up(0,1,0);
	D3DXMATRIX v;
	D3DXMatrixLookAtLH(&v,&positon,&target,&up);

	Device->SetTransform(D3DTS_VIEW,&v);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj,D3DX_PI*0.5,(float)screen_width/(float)screen_height,1,1000);
	Device->SetTransform(D3DTS_PROJECTION,&proj);

	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	light.Diffuse   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular  = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Direction = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	Device->SetLight(0, &light);
	Device->LightEnable(0, true);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);
	Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	D3DXCreateTextureFromFile(
		Device,
		"img/crate.jpg",
		&Tex);
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//Device->SetRenderState(D3DRS_LIGHTING, false);

	return true;
};

bool d3dtest6::display(float timeDelta){

	if(Device){

		static float angle  = (3.0f * D3DX_PI) / 2.0f;
		static float height = 0;

		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			angle -= 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
			angle += 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
			height += 5.0f * timeDelta;

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
			height -= 5.0f * timeDelta; 

		D3DXVECTOR3 position( cosf(angle) * 3.0f, height, sinf(angle) * 3.0f );
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		Device->SetTransform(D3DTS_VIEW, &V);


		/*D3DXMATRIX mx,my;
		static float y = 0;
		D3DXMatrixRotationX(&mx,D3DX_PI/4);
		y += timeDelta;
		D3DXMatrixRotationY(&my,y);

		if (y>=D3DX_PI*2)
		{
		y = 0;
		}

		D3DXMATRIX final = mx*my;

		Device->SetTransform(D3DTS_WORLD,&final);*/

		Device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0xffff00ff,1,0);
		Device->BeginScene();

		Device->SetStreamSource(0,lp_buffer,0,sizeof(VertexEx));
		Device->SetIndices(lp_index);
		Device->SetFVF(VertexEx::FVF);

		Device->SetMaterial(&d3d::WHITE_MATERIAL);
		Device->SetTexture(0, Tex);

		Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,4,0,2);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);

	}

	return true;
};

bool d3dtest6::cleanup(){
	if(lp_buffer)lp_buffer->Release();
	if(lp_index)lp_index->Release();
	return true;
}

d3dtest6::d3dtest6(IDirect3DDevice9* device):TestRoot(device)
{
}


d3dtest6::~d3dtest6(void)
{
}