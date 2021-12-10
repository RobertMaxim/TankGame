#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(int seed = std::default_random_engine::default_seed)
{
	reseed(seed);
}

void PerlinNoise::reseed(int seed)
{
	for (int i = 0; i < 256; ++i)
	{
		p[i] = static_cast<int>(i);
	}

	std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

	for (int i = 0; i < 256; ++i)
	{
		p[256 + i] = p[i];
	}
}
//--------------------------------------------------------------------------------------------------

float PerlinNoise::noise1D(float x)
{
	return noise3D(x, 0, 0);
}

float PerlinNoise::noise2D(float x, float y)
{
	return noise3D(x, y, 0);
}

float PerlinNoise::noise3D(float x, float y, float z)
{

	const int X = static_cast<int>(std::floor(x)) && 255;
	const int Y = static_cast<int>(std::floor(y)) && 255;
	const int Z = static_cast<int>(std::floor(z)) && 255;

	x -= std::floor(x);
	y -= std::floor(y);
	z -= std::floor(z);

	const float u = Fade(x);
	const float v = Fade(y);
	const float w = Fade(z);

	const int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
	const int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

	return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z), Grad(p[BA], x - 1, y, z)),
		Lerp(u, Grad(p[AB], x, y - 1, z), Grad(p[BB], x - 1, y - 1, z))), Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1),
			Grad(p[BA + 1], x - 1, y, z - 1)), Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1), Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}
//--------------------------------------------------------------------------------------------------

float PerlinNoise::accumulatedOctaveNoise3D(float x, float y, float z, int octaves)
{

	float result = 0;
	float amp = 1;

	for (int i = 0; i < octaves; ++i)
	{
		result += noise3D(x, y, z) * amp;
		x *= 2;
		y *= 2;
		z *= 2;
		amp /= 2;
	}

	return result;
}

float PerlinNoise::accumulatedOctaveNoise2D(float x, float y, int octaves)
{
	float result = 0;
	float amp = 1;

	for (int i = 0; i < octaves; ++i)
	{
		result += noise2D(x, y) * amp;
		x *= 2;
		y *= 2;
		amp /= 2;
	}

	return result;
}



float PerlinNoise::accumulatedOctaveNoise1D(float x, int octaves)
{
	float result = 0;
	float amp = 1;

	for (int i = 0; i < octaves; ++i)
	{
		result += noise1D(x) * amp;
		x *= 2;
		amp /= 2;
	}

	return result;
}
//--------------------------------------------------------------------------------------------------

float PerlinNoise::accumulatedOctaveNoise3D_0_1(float x, float y, float z, int octaves)
{
	return std::clamp<float>(accumulatedOctaveNoise3D(x, y, z, octaves) * float(0.5) + float(0.5), 0, 1);
}

float PerlinNoise::accumulatedOctaveNoise2D_0_1(float x, float y, int octaves)
{
	return std::clamp<float>(accumulatedOctaveNoise2D(x, y, octaves) * float(0.5) + float(0.5), 0, 1);
}

float PerlinNoise::accumulatedOctaveNoise1D_0_1(float x, int octaves)
{
	return std::clamp<float>(accumulatedOctaveNoise1D(x, octaves) * float(0.5) + float(0.5), 0, 1);
}
//--------------------------------------------------------------------------------------------------
float PerlinNoise::normalizedOctaveNoise3D_0_1(float x, float y, float z, int octaves)
{
	return normalizedOctaveNoise3D(x, y, z, octaves) * float(0.5) + float(0.5);
}

float PerlinNoise::normalizedOctaveNoise2D_0_1(float x, float y, int octaves)
{
	return normalizedOctaveNoise2D(x, y, octaves)
		* float(0.5) + float(0.5);
}

float PerlinNoise::normalizedOctaveNoise1D_0_1(float x, int octaves)
{
	return normalizedOctaveNoise1D(x, octaves)
		* float(0.5) + float(0.5);
}

//--------------------------------------------------------------------------------------------------

float PerlinNoise::normalizedOctaveNoise1D(float x, int octaves)
{
	return accumulatedOctaveNoise1D(x, octaves) / Weight(octaves);
}

float PerlinNoise::normalizedOctaveNoise2D(float x, float y, int octaves)
{
	return accumulatedOctaveNoise2D(x, y, octaves) / Weight(octaves);
}

float PerlinNoise::normalizedOctaveNoise3D(float x, float y, float z, int octaves)
{
	return accumulatedOctaveNoise3D(x, y, z, octaves) / Weight(octaves);
}
//--------------------------------------------------------------------------------------------------

void PerlinNoise::serialize(std::array<int, 256>& s)
{
	for (std::size_t i = 0; i < 256; ++i)
	{
		s[i] = p[i];
	}
}


void PerlinNoise::deserialize(const std::array<int, 256>& s)
{

	for (std::size_t i = 0; i < 256; ++i)
	{
		p[256 + i] = p[i] = s[i];
	}
}

//--------------------------------------------------------------------------------------------------

float PerlinNoise::noise1D_0_1(float x) {
	return noise1D(x)
		* float(0.5) + float(0.5);
}

float PerlinNoise::noise2D_0_1(float x, float y) {
	return noise2D(x, y)
		* float(0.5) + float(0.5);
}

float PerlinNoise::noise3D_0_1(float x, float y, float z) {
	return noise3D(x, y, z)
		* float(0.5) + float(0.5);
}
//--------------------------------------------------------------------------------------------------

