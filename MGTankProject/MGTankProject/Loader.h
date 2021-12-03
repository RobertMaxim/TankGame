#pragma once
#include "DisplayManager.h"
#include "VAO.h"
#include <vector>
class Loader {
public:
	VAO loadToVAO(float* positions) {
		int VaoID = CreateVAO();
		storeDataInAttribList(0, positions);
		unbindVAO();

	}

	int CreateVAO() {
		int vaoID = glGenVertexArrays(;
	}

	void storeDataInAttribList(int attributeNumber, float* data) {

	}

	void unbindVAO() {

	}
};