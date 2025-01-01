#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
#include "Vector3.h"
#include "Color.h"
#define SEGMENTS 10
#define PI 3.14159

class Drawing
{

public: 
	static int elCount;
	static void DrawPoint(Vector3 pos, float w, Color color);
	static void DrawCircle(Vector3 pos, float r, Color color);
	static void DrawLine(Vector3 from, Vector3 to, float width, Color color);
};

