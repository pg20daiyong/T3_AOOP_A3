//
// + Random.cpp
// helpers for producing random numbers
//

#include <cstdlib>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

int RandomInt( int nMax )
{
	return rand() % ( nMax + 1 );
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

//
// https://stackoverflow.com/questions/686353/random-float-number-generation
//

float RandomFloat( float fMin, float fMax )
{
	const float fValue = fMin + static_cast<float>(rand()) / ( static_cast<float>( RAND_MAX / ( fMax - fMin ) ) );
	return fValue;
}
