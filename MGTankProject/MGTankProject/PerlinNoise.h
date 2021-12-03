#pragma once
#include <cstdint>
#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>
#include <random>
#include <type_traits>

class PerlinNoise {
private:
	
	int p[512];
	static float Fade(float t) {
		return t * t * t * (t * (t * 6 - 15) + 10);
	}
	static float Lerp(float t, float a, float b) {
		return a + t * (b - a);
	}

	static float Grad(int hash, float x, float y, float z) {
		int h = hash & 15;
		float u = h < 8 ? x : y;
		float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	static float Weight(int octaves)
	{
		float amp = 1;
		float value = 0;
		for (int i = 0; i < octaves; i++)
		{
			value += amp;
			amp /= 2.0;
		}
		return value;
	}
public:
	PerlinNoise(int seed);

	template <class URNG, std::enable_if_t<!std::is_arithmetic_v<URNG>>* = nullptr>
	PerlinNoise(URNG&& urng) {
		reseed(std::forward<URNG>(urng));
	}
	void reseed(int seed);

	float noise1D(float x);
	float noise2D(float x, float y);
	float noise3D(float x, float y, float z);
	
	float noise1D_0_1(float x);
	float noise2D_0_1(float x, float y);
	float noise3D_0_1(float x, float y, float z);

	float accumulatedOctaveNoise3D(float x, float y, float z, int octaves);
	float accumulatedOctaveNoise2D(float x, float y, int octaves);
	float accumulatedOctaveNoise1D(float x, int octaves);
	
	float normalizedOctaveNoise3D(float x, float y, float z, int octaves);
	float normalizedOctaveNoise2D(float x, float y, int octaves);
	float normalizedOctaveNoise1D(float x, int octaves);
	
	float accumulatedOctaveNoise3D_0_1(float x, float y, float z, int octaves);
	float accumulatedOctaveNoise2D_0_1(float x, float y, int octaves);
	float accumulatedOctaveNoise1D_0_1(float x, int octaves);

	float normalizedOctaveNoise3D_0_1(float x, float y, float z, int octaves);	
	float normalizedOctaveNoise2D_0_1(float x, float y, int octaves);
	float normalizedOctaveNoise1D_0_1(float x, int octaves);

	void serialize(std::array<int, 256>& s);
	void deserialize(const std::array<int, 256>& s);
	
	

};

