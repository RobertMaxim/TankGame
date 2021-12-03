#pragma once
#include "GenerateNoiseMap.h"

class MapGenerator {
public:
	int mapWidth;
	int mapHeight;
	float noiseScale;

	void Generate() {
		float* noiseMap = GenerateNoiseMap::GenerateMap(mapWidth, mapHeight, noiseScale);
	}
};