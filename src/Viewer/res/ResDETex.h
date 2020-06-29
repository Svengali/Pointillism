//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2017 Marc Hernandez
#pragma once




class ResDETex : public Resource
{
public:
	CLASS( ResDETex, Resource );

	static ResourcePtr Create( const char * const pFilename, const util::Symbol &type );

	virtual ~ResDETex();
	
	
	virtual void Load  ( const char * const pFilename );
	

private:

};



PtrDef( ResDETex );















// -