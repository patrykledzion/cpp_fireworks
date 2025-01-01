#include "Firework.h"
#include "Program.h"

Firework::Firework(Vector3 startPos, Vector3 startForce, Color color, bool first, float mass, Program* program)
	: pos(startPos), color(color), first(first), mass(mass)
{
	this->ApplyForce(startForce);
	this->program = program;
	this->destroy = false;
	this->trail = new std::vector<Firework*>();
}

Firework::~Firework()
{
	if(this->trail!= nullptr) delete this->trail;
}

void Firework::Init()
{ 
}

void Firework::Update()
{
	//Move
	this->pos += this->speed;

	//"Gravity"
	this->speed -= Vector3{0, 1, 0};
	if (this->speed.y < 10)
	{
		this->Explode();
	}

	if (!this->first)
	{
		this->mass *= 0.95;
		if (this->mass < 0.1f)this->destroy = true;
	}

	//trail
	this->trail->push_back(new Firework(this->pos, {0,0,0}, this->color, false, this->mass * 0.8, this->program));
	int _i = 0;
	while (this->trail->size() > this->trailSize)
	{
		delete this->trail->at(_i++);
		this->trail->erase(this->trail->begin());
	}

	for (int i = 0; i < this->trail->size(); i++)
	{
		auto t = this->trail->at(i);
		t->mass *= 0.5f;
		if (t->mass < 0.1f)
		{
			delete t;
			this->trail->erase(this->trail->begin() + i);
		}
	}
}

void Firework::Draw()
{
	Drawing::DrawCircle(this->pos, this->mass, this->color);
	for(int i=0;i<this->trail->size();i++)
	{
		auto t = this->trail->at(i);
		auto t_prev = i > 0 ? this->trail->at(i - 1) : nullptr;
		if (t_prev != nullptr)
		{
			Drawing::DrawLine(t_prev->pos, t->pos, this->mass * 2, this->color);
		}
		t->Draw();
	}
}

void Firework::ApplyForce(Vector3 force)
{
	this->speed += (force / (mass)) * 0.5;
	this->speed.x = floorf(this->speed.x);
	this->speed.y = floorf(this->speed.y);
	this->speed.z = floorf(this->speed.z);
}

void Firework::Explode()
{
	if (!this->first)return;
	int n = Utils::Random(50, 80);
	for (int i = 0; i < n; i++)
	{
		float force1 = Utils::Random(-100, 100) + this->speed.x * this->mass / 10;
		float force2 = Utils::Random(0, 170) + this->speed.y * this->mass / 10;
		float force3 = Utils::Random(-20, 20) + this->speed.z * this->mass / 10;

		Vector3 force = Vector3{ force1, force2, force3 };
		this->program->AddFirework(new Firework(this->pos, force, this->color, false, this->mass, this->program));
	}
	this->destroy = true;
}
