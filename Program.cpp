#include "Program.h"

Program::Program()
{
	srand(time(NULL));
	this->window = new Window(1200, 1000, "aaa");
	this->fireworks = new std::vector<Firework*>();
	this->prev_frame = clock();
}

void Program::Init()
{
	Firework* firework = new Firework(Vector3{ 600,0,0 }, Vector3{ 10,250,0 }, Color{ 1,0,0 }, true, 3, this);
	this->fireworks->push_back(firework);
}

void Program::Draw()
{
	clock_t start = clock();
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < this->fireworks->size(); i++)
	{
		this->fireworks->at(i)->Draw();
	}
	glFinish();
	clock_t end = clock(); 
}

void Program::Update()
{
	this->window->Update();
	if (this->prev_frame + 17 > clock())return;
	this->prev_frame = clock();
	int r = Utils::Random(0, 30);
	if (r == 0)
	{
		Firework* _firework = new Firework(Vector3{ Utils::Random(30,1170,0),0,0}, 
			Vector3{Utils::Random(-10,10,0),Utils::Random(180,210,0),0}, 
			Color{ Utils::Random(0,1,1),Utils::Random(0,1,1),Utils::Random(0,1,1)},
			true, 3, this);
		this->fireworks->push_back(_firework);
	}
	
	int z = 5;
	for (int i = 0; i < this->fireworks->size(); i++) 
	{ 
		auto firework = this->fireworks->at(i);
		firework->Update();
	}

	for (int i = 0; i < this->fireworks->size(); i++) 
	{
		auto firework = this->fireworks->at(i);
		if (firework->destroy)
		{
			delete firework;
			this->fireworks->erase(this->fireworks->begin() + i);
		}
	}
}

void Program::AddFirework(Firework* firework)
{
	this->fireworks->push_back(firework);
}
