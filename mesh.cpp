#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glew.h>
#include <assert.h>
#include "mesh.h"

#define BUFFER_OFFSET(i) ((char*)NULL + (i))
using namespace std;

int Mesh::VertexDataSize()
{
    return (*this).gVertices.size() * 3 * sizeof(GLfloat);
}

int Mesh::NormalDataSize()
{
	return (*this).gNormals.size() * 3 * sizeof(GLfloat);
}

int Mesh::IndexDataSize()
{
	return (*this).gFaces.size() * 3 * sizeof(GLuint);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    cout << "vao = " << VAO << endl;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	assert(glGetError() == GL_NONE);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	assert(VBO > 0 && EBO > 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLfloat* vertexData = new GLfloat [gVertices.size() * 3];
	GLfloat* normalData = new GLfloat [gNormals.size() * 3];
	GLuint* indexData = new GLuint [gFaces.size() * 3];

    float minX = 1e6, maxX = -1e6;
    float minY = 1e6, maxY = -1e6;
    float minZ = 1e6, maxZ = -1e6;

	for (int i = 0; i < gVertices.size(); ++i)
	{
		vertexData[3*i] = gVertices[i].x;
		vertexData[3*i+1] = gVertices[i].y;
		vertexData[3*i+2] = gVertices[i].z;

        minX = min(minX, gVertices[i].x);
        maxX = max(maxX, gVertices[i].x);
        minY = min(minY, gVertices[i].y);
        maxY = max(maxY, gVertices[i].y);
        minZ = min(minZ, gVertices[i].z);
        maxZ = max(maxZ, gVertices[i].z);
	}

	for (int i = 0; i < gNormals.size(); ++i)
	{
		normalData[3*i] = gNormals[i].x;
		normalData[3*i+1] = gNormals[i].y;
		normalData[3*i+2] = gNormals[i].z;
	}

	for (int i = 0; i < gFaces.size(); ++i)
	{
		indexData[3*i] = gFaces[i].vIndex[0];
		indexData[3*i+1] = gFaces[i].vIndex[1];
		indexData[3*i+2] = gFaces[i].vIndex[2];
	}


	glBufferData(GL_ARRAY_BUFFER, VertexDataSize() + VertexDataSize(), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, VertexDataSize(), vertexData);
	glBufferSubData(GL_ARRAY_BUFFER, VertexDataSize(), NormalDataSize(), normalData);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexDataSize(), indexData, GL_STATIC_DRAW);

	// done copying; can free now
	delete[] vertexData;
	delete[] normalData;
	delete[] indexData;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(VertexDataSize()));
}  

void Mesh::drawMesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(VertexDataSize()));

	glDrawElements(GL_TRIANGLES, gFaces.size() * 3, GL_UNSIGNED_INT, 0);
}