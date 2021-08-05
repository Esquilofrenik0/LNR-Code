#include "Compass.h"

float UCompass::RotationToCircleDegrees(int value)
{
	if(value < 0) return (value + 360)%360;
	else return value;
}

float UCompass::GetDelta(int a, int b, bool clockwise)
{
	a %= 360;
	b %= 360;
	if(clockwise)
	{
		if (a > b) return 360-(a-b);
		else if (a < b) return b-a;
		else return 0;
	}
	else
	{
		if (a > b) return a-b;
		else if (a < b) return 360-(b-a);		
		else return 0;
	}
}
