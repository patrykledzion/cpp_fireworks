#pragma once
#include <vector>
#include <time.h>
#include "Window.h"
#include "Vector3.h"
#include "Firework.h"

class Program
{
private:
	Window* window;
	Vector3 size;
	std::vector<Firework*>* fireworks;
	clock_t prev_frame;
public:
	Program();
	void Init();
	void Draw();
	void Update();
	void AddFirework(Firework* firework);
};

