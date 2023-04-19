/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#pragma once
#include "pch.h"

namespace Math
{
	// default vert is gray 0,0,0
	struct Vertex
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float n_x = 0.0f;
		float n_y = 0.0f;
		float n_z = 0.0f;
		float u = 0.0f;
		float v = 0.0f;
	};

	// default tri is 0,0,0
	struct Tri
	{
		int a = 0;
		int b = 0;
		int c = 0;
	};

	struct Vec3f
	{
		float x;
		float y;
		float z;
	};

	struct Euler
	{
		float Pitch;
		float Yaw;
		float Roll;
	};


	// Converts a euler angle to a glm::vec3
	// .. normalized this vector to provide a ray direction
	inline glm::vec3 NormalizedDirectionFromEulerAngle(const Euler angles)
	{
		glm::vec3 direction;

		direction.x = cos(glm::radians(angles.Yaw)) * cos(glm::radians(angles.Pitch));
		direction.y = sin(glm::radians(angles.Pitch));
		direction.z = sin(glm::radians(angles.Yaw)) * cos(glm::radians(angles.Pitch));

		return glm::normalize(direction);
	}

	// Clamps a value in provided range
	template <typename T>
	T Clamp(T value, T min, T max)
	{
		return value > max ? max : value < min ? min : value;
	}

	// converts verts into raw floats
	inline std::vector<float> FloatVectorFromVerts(const std::vector<Math::Vertex>& verts)
	{
		std::vector<float> ret;
		ret.reserve(verts.size() * sizeof(Math::Vertex));

		for (auto v : verts)
		{
			ret.emplace_back(v.x);
			ret.emplace_back(v.y);
			ret.emplace_back(v.z);
			ret.emplace_back(v.n_x);
			ret.emplace_back(v.n_y);
			ret.emplace_back(v.n_z);
			ret.emplace_back(v.u);
			ret.emplace_back(v.v);
		}
		return ret;
	}

	// converts tris into raw floats
	inline std::vector<unsigned short> ShortVectorFromTris(const std::vector<Math::Tri>& tris)
	{
		std::vector<unsigned short> ret;
		ret.reserve(tris.size() * sizeof(Math::Tri));

		for (auto v : tris)
		{
			ret.emplace_back(v.a);
			ret.emplace_back(v.b);
			ret.emplace_back(v.c);
		}
		return ret;
	}

	/**
	 * Returns a set of x,y coords for points on a circle's circumference.
	 */
	inline std::vector<std::pair<float, float>> GetCirclePoints(
		const float originX, const float originY, const float radius, const int numPoints)
	{
		// Setup and reserve vec
		std::vector<std::pair<float, float>>points;
		points.reserve(numPoints);

		// constant angle between each point
		const auto angle = 
			360.0f / static_cast<float>(numPoints) * glm::pi<float>() / 180;

		// calculate points
		for (int i = 0; i < numPoints; i++)
		{
			points.emplace_back(
				originX + radius * glm::cos(angle * static_cast<float>(i)),
				originY - radius * glm::sin(angle * static_cast<float>(i))
			);
		}
		return points;
	}


}
