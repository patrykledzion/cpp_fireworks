#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "Vector3.h"
#include "Color.h"
#include "Drawing.h"
#include "Utils.h" 

class Program;
class Firework
{
private:
	Vector3 pos;
	Vector3 speed;
	bool first;
	float mass;
	Program* program;
	std::vector<Firework*>* trail;
	int trailSize = 20;
public:

	Color color;
	bool destroy;
public:
	Firework(Vector3 startPos, Vector3 startForce, Color color, bool first, float mass, Program* program);
	~Firework();
	void Init();
	void Update();
	void Draw();

	void ApplyForce(Vector3 force);
	void Explode();
};

