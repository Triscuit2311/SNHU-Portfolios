/*
 *
 *	Author: Dante Trisciuzzi
 *	Purpose: CS330 Project 2
 *	Date: 4.10.2023
 *
 */

#pragma once

class RandomHelpers
{
public:

	static float GetOneOrZero()
	{
		return rand() % 2 == 0 ? 1.0f : 0.0f;
	}

	static float GetLightColValF()
	{
		return GetFloatInRange(0.3f, 0.7f);
	}

	static float GetFloatInRange(const float min, const float max)
	{
		return min + static_cast <float> (rand()) / (RAND_MAX / (max - min));
	}

	static int GetIntInRange(const int min, const int max)
	{
		return min + (rand()) / (RAND_MAX / (max - min));
	}


	static void Init()
	{
		// seed for random genny
		srand(static_cast <unsigned> (time(nullptr)));
	}
};