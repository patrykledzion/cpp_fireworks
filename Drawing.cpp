#include "Drawing.h"

int Drawing::elCount = 0;

void Drawing::DrawPoint(Vector3 pos, float w, Color color)
{
	glColor3f(color.r, color.g, color.b);
	glPointSize(w);
	glBegin(GL_POINTS);
	glVertex2f(pos.x, pos.y);
	glEnd();
}

void Drawing::DrawCircle(Vector3 pos, float r, Color color)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= SEGMENTS; i++)
	{
		float angle = 2 * PI * i / SEGMENTS;
		float x = r * cosf(angle) + pos.x;
		float y = r * sinf(angle) + pos.y;
		glVertex2f(x, y);
	}
	glEnd();
}

void Drawing::DrawLine(Vector3 from, Vector3 to, float width, Color color)
{
	glColor3f(color.r, color.g, color.b);
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2f(from.x, from.y);
	glVertex2f(to.x, to.y);
	glEnd();
}


