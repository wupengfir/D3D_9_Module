#include "TestObjects.h"
extern int screen_width;
extern int screen_height;
bool d3dtest5::setup(){
	D3DXCreateTeapot(Device, &Objects[0], 0);
	D3DXCreateSphere(Device, 1.0f, 20, 20, &Objects[1], 0);
	D3DXCreateTorus(Device, 0.5f, 1.0f, 20, 20, &Objects[2], 0);
	D3DXCreateCylinder(Device, 0.5f, 0.5f, 2.0f, 20, 20, &Objects[3], 0);

	//
	// Build world matrices - position the objects in world space.
	//

	D3DXMatrixTranslation(&Worlds[0],  0.0f,  2.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[1],  0.0f, -2.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[2], -3.0f,  0.0f, 0.0f);
	D3DXMatrixTranslation(&Worlds[3],  3.0f,  0.0f, 0.0f);

	//
	// Setup the object's materials.
	//

	Mtrls[0] = d3d::RED_MATERIAL;
	Mtrls[1] = d3d::BLUE_MATERIAL;
	Mtrls[2] = d3d::GREEN_MATERIAL;
	Mtrls[3] = d3d::YELLOW_MATERIAL;

	//
	// Setup a directional light.
	//

	D3DXVECTOR3 dir(1.0f, -0.0f, 0.25f);
	D3DXCOLOR   c = D3DCOLOR_XRGB(232,93,25);
	D3DLIGHT9 dirLight = d3d::initDirectonalLight(&dir, &c);

	//
	// Set and Enable the light.
	//

	Device->SetLight(0, &dirLight);
	Device->LightEnable(0, true);

	//
	// Set lighting related render states.
	//

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);
	Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 45 - degree
		(float)screen_width / (float)screen_height,
		1.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

bool d3dtest5::cleanup(){
	for(int i = 0; i < 4; i++)
		d3d::Release<ID3DXMesh*>(Objects[i]);
	return true;
}

bool d3dtest5::display(float timeDelta){
	
	if( Device )
	{
		// 
		// Update the scene: update camera position.
		//

		static float angle  = (3.0f * D3DX_PI) / 2.0f;
		static float height = 5.0f;
	
		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			angle -= 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
			angle += 0.5f * timeDelta;

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
			height += 5.0f * timeDelta;

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
			height -= 5.0f * timeDelta;

		D3DXVECTOR3 position( cosf(angle) * 7.0f, height, sinf(angle) * 7.0f );
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		Device->SetTransform(D3DTS_VIEW, &V);

		//
		// Draw the scene:
		//
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		for(int i = 0; i < 4; i++)
		{
			// set material and world matrix for ith object, then render
			// the ith object.
			Device->SetMaterial(&Mtrls[i]);
			Device->SetTransform(D3DTS_WORLD, &Worlds[i]);
			Objects[i]->DrawSubset(0);
		}

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

d3dtest5::d3dtest5(IDirect3DDevice9* device):TestRoot(device)
{
}


d3dtest5::~d3dtest5(void)
{
}
