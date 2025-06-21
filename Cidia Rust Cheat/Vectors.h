#pragma once
#include <algorithm>
class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y);
	~Vector2();

	float x, y;

	Vector2 operator *(Vector2 a);
	Vector2 operator /(Vector2 a);
	Vector2 operator +(Vector2 a);
	Vector2 operator -(Vector2 a);
	bool operator ==(Vector2 a);
	bool operator !=(Vector2 a);


	bool IsZero() const;

	static Vector2 Zero();

	static float Distance(Vector2 a, Vector2 b);

	float length() const
	{
		return sqrt((x * x) + (y * y));
	}

	Vector2 normalized() const
	{
		return { x / length(), y / length() };
	}

	float dot_product(Vector2 input) const
	{
		return (x * input.x) + (y * input.y);
	}

	bool empty() const
	{
		return x == 0.f && y == 0.f;
	}

/*
	void times(float input) const
	{
		x *= input;
		y *= input;
	}
*/

};

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();

	float x, y, z;

	Vector3 operator *(Vector3 a);
	Vector3 operator *(float f);
	Vector3 operator /(Vector3 a);
	Vector3 operator /(float f);
	Vector3 operator +(Vector3 a);
	Vector3 operator -(Vector3 a);
	bool operator ==(Vector3 a);
	bool operator !=(Vector3 a);

	bool IsZero() const;

	static float Dot(Vector3 left, Vector3 right);
	static float Distance(Vector3 a, Vector3 b);
	static int FormattedDistance(Vector3 a, Vector3 b);
	static Vector3 Zero();
	static Vector3 Lerp(Vector3 a, Vector3 b, float t);

	float dot_product(Vector3 input);

	float Length() const;
	float LengthSqr() const;

	float length_sqr() const;
	float length() const;

	Vector3 Clamp() const;

	float unity_magnitude()
	{
		return (float)sqrt((double)(x * x + y * y + z * z));
	}

	Vector3 Cross(Vector3 rhs)
	{
		return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}



	Vector3 normalize();

	Vector3 unity_Normalize()
	{
		float num = unity_magnitude();
		if (num > 1E-05f)
		{
			x /= num;
			y /= num;
			z /= num;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}

		return { x,y,z };
	}

};

struct ViewMatrix
{
public:
	float matrix[4][4];

	Vector3 Transform(const Vector3 vector) const;
};

class Vector4
{
public:
	Vector4()
	{
		x = y = z = w = 0.f;
	}

	Vector4(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}

	float x, y, z, w;

	Vector4 operator+(const Vector4& input) const
	{
		return Vector4{ x + input.x, y + input.y, z + input.z, w + input.w };
	}

	Vector4 operator-(const Vector4& input) const
	{
		return Vector4{ x - input.x, y - input.y, z - input.z, w - input.w };
	}

	Vector4 operator/(float input) const
	{
		return Vector4{ x / input, y / input, z / input, w / input };
	}

	Vector4 operator*(float input) const
	{
		return Vector4{ x * input, y * input, z * input, w * input };
	}

	Vector4& operator-=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	Vector4& operator/=(float input)
	{
		x /= input;
		y /= input;
		z /= input;
		w /= input;
		return *this;
	}

	Vector4& operator*=(float input)
	{
		x *= input;
		y *= input;
		z *= input;
		w *= input;
		return *this;
	}

	bool operator==(const Vector4& input) const
	{
		return x == input.x && y == input.y && z == input.z && w == input.w;
	}

	void make_absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
		w = std::abs(w);
	}

	float length_sqr() const
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	float length() const
	{
		return sqrt(length_sqr());
	}

	float length_2d() const
	{
		return sqrt((x * x) + (y * y));
	}

	Vector4 normalized() const
	{
		return { x / length(), y / length(), z / length(), w / length() };
	}

	float dot_product(Vector4 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z) + (w * input.w);
	}

	float distance(Vector4 input) const
	{
		return (*this - input).length();
	}

	float distance_2d(Vector4 input) const
	{
		return (*this - input).length_2d();
	}
	void clamp()
	{
		static_cast<void>(std::clamp(x, -89.f, 89.f));
		static_cast<void>(std::clamp(y, -180.f, 180.f));

		z = 0.f;
		w = 0.f;
	}

	bool empty() const
	{
		return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
	}

	static Vector4 QuaternionLookRotation(Vector3 forward, Vector3 up)
	{
		Vector3 vector = forward.unity_Normalize();
		Vector3 vector2 = (up).Cross(vector).unity_Normalize();
		Vector3 vector3 = (vector).Cross(vector2);
		auto m00 = vector2.x;
		auto m01 = vector2.y;
		auto m02 = vector2.z;
		auto m10 = vector3.x;
		auto m11 = vector3.y;
		auto m12 = vector3.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;


		float num8 = (m00 + m11) + m22;
		auto quaternion = Vector4();
		if (num8 > 0.f)
		{
			auto num = (float)sqrt(num8 + 1.f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			auto num7 = (float)sqrt(((1.f + m00) - m11) - m22);
			auto num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;
			return quaternion;
		}
		if (m11 > m22)
		{
			auto num6 = (float)sqrt(((1.f + m11) - m00) - m22);
			auto num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion;
		}
		auto num5 = (float)sqrt(((1.f + m22) - m00) - m11);
		auto num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion;
	}



};
