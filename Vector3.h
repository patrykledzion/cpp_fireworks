#pragma once
class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3& operator += (Vector3 v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}

	Vector3& operator *= (Vector3 v)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		return *this;
	}

	Vector3& operator *= (float number)
	{
		this->x *= number;
		this->y *= number;
		this->z *= number;
		return *this;
	}

	Vector3& operator /= (Vector3 v)
	{
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
		return *this;
	}

	Vector3& operator /= (float number)
	{
		this->x /= number;
		this->y /= number;
		this->z /= number;
		return *this;
	}

	Vector3& operator -= (Vector3 v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}

	Vector3 operator + (Vector3 v)
	{
		return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vector3 operator - (Vector3 v)
	{
		return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	Vector3 operator * (Vector3 v)
	{
		return Vector3(this->x * v.x, this->y * v.y, this->z * v.z);
	}

	Vector3 operator * (float number)
	{
		return Vector3(this->x * number, this->y * number, this->z *number);
	}

	Vector3 operator / (Vector3 v)
	{
		return Vector3(this->x / v.x, this->y / v.y, this->z / v.z);
	}

	Vector3 operator / (float number)
	{
		return Vector3(this->x / number, this->y / number, this->y / number);
	}
};

