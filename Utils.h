#pragma once
#include <cstdlib>
#include <cmath>
#include "Vector3.h"
class Utils
{
public:
	//RANDOM .000
	static float Random(float from, float to, int decimals)
	{
		float _from = from;
		float _to = to;
		int r = rand() % ((int)_to * (int)pow(10,decimals) - (int)_from * (int)pow(10, decimals) + 1) + _from * (int)pow(10, decimals);
		return (float)r / pow(10, decimals);
	}

	static int Random(float from, float to)
	{
		int _from = from;
		int _to = to;
		return rand() % (_to - _from + 1) +  _from;
	}

	static float Distance(Vector3 pos1, Vector3 pos2)
	{
		float dx = pos1.x - pos2.x;
		float dy = pos1.y - pos2.y;
		return std::sqrt(dx * dx + dy * dy);
	}
};

