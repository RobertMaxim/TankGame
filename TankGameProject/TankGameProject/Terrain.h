#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_

#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
#include <stdio.h>
using namespace DirectX;
using namespace std;

class TerrainClass
{
private:

	struct HeightMapType
	{
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};


	struct VectorType
	{
		float x, y, z;
	};

public:
	TerrainClass();
	//TerrainClass(const TerrainClass&);
	//~TerrainClass();

	bool Initialize(ID3D11Device*, char*);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool LoadSetupFile(char*);
	bool LoadRawFile();
	void ShutdownHeightMap();
	void SetTerrainCoordinates();
	bool CalculateNormals();
	bool LoadColorMap();
	bool BuildTerrainModel();
	void ShutdownTerrainModel();
	void CalculateTerrainVectors();

	void ShutdownBuffers();

private:
	int m_vertexCount, m_indexCount;
	int m_terrainHeight, m_terrainWidth;
	float m_heightScale;
	char* m_terrainFilename, * m_colorMapFilename;
	HeightMapType* m_heightMap;
};

#endif