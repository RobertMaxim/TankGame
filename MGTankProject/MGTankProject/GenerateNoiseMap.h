#pragma once
#include "PerlinNoise.h"


class GenerateNoiseMap : PerlinNoise {
public:
	static float* GenerateMap(int mapWidth, int mapHeight, float scale) {
		float* noiseMap = new float[mapWidth, mapHeight];

		if (scale <= 0) {
			scale = 0.00001f;
		}

		for (int y = 0; y < mapHeight; y++)
		{
			for (int x = 0; x < mapWidth; x++)
			{
				float sampleX = x / scale;
				float sampleY = y / scale;
				PerlinNoise p(std::default_random_engine::default_seed);
				float PerlinValue = p.noise2D(sampleX, sampleY);
				noiseMap[x, y] = PerlinValue;
			}
		}
		return noiseMap;
	}
};