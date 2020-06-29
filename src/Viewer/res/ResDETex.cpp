//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez

#include "stdafx.h"


#include ".\ResDETex.h"



ResourcePtr ResDETex::Create( const char * const pFilename, const util::Symbol &type )
{
/*
	ResDETexPtr ResDETex( new ResDETex() );
	
	ResDETex->Load( pFilename );

	return ResDETex;
	*/

	return ResourcePtr(NULL);
}


ResDETex::~ResDETex(void)
{
//	if( m_pMeshTexture != NULL )
//	{
//		m_pMeshTexture->Release();
//	}
}

void ResDETex::Load( const char * const pFilename )
{
/*
	ASSERT( m_pMeshTexture == NULL );

	WCHAR wszBuf[MAX_PATH];
	MultiByteToWideChar( CP_ACP, 0, pFilename, -1, wszBuf, MAX_PATH );
	wszBuf[MAX_PATH - 1] = L'\0';
	//DXUTFindDXSDKMediaFileCch( strPath, 512, wszBuf );

	// Load the texture
	const HRESULT hr = D3DXCreateTextureFromFile( DXUTGetD3D9Device(), wszBuf, &m_pMeshTexture );
	
	hr;
	
	//gD3DUtil::ShowHR( hr );
*/
}














// -