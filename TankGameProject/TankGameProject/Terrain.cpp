#include "Terrain.h"

struct HeightMapType
{
    float x, y, z;
    float nx, ny, nz;
    float r, g, b;
};

bool TerrainClass::LoadRawFile()
{
    int error, i, j, index;
    FILE* filePtr;
    unsigned long long imageSize, count;
    unsigned short* rawImage;


    // Create the float array to hold the height map data.
    m_heightMap = new HeightMapType[m_terrainWidth * m_terrainHeight];
    if (!m_heightMap)
    {
        return false;
    }

    // Open the 16 bit raw height map file for reading in binary.
    error = fopen_s(&filePtr, m_terrainFilename, "rb");
    if (error != 0)
    {
        return false;
    }

    // Calculate the size of the raw image data.
    imageSize = m_terrainHeight * m_terrainWidth;

    // Allocate memory for the raw image data.
    rawImage = new unsigned short[imageSize];
    if (!rawImage)
    {
        return false;
    }

    // Read in the raw image data.
    count = fread(rawImage, sizeof(unsigned short), imageSize, filePtr);
    if (count != imageSize)
    {
        return false;
    }

    // Close the file.
    error = fclose(filePtr);
    if (error != 0)
    {
        return false;
    }

    // Copy the image data into the height map array.
    for (j = 0; j < m_terrainHeight; j++)
    {
        for (i = 0; i < m_terrainWidth; i++)
        {
            index = (m_terrainWidth * j) + i;

            // Store the height at this point in the height map array.
            m_heightMap[index].y = (float)rawImage[index];
        }
    }

    // Release the bitmap image data.
    delete[] rawImage;
    rawImage = 0;

    // Release the terrain filename now that it has been read in.
    delete[] m_terrainFilename;
    m_terrainFilename = 0;

    return true;
}