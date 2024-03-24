#ifndef _mesh_included_
#define _mesh_included_

#include <GL/glew.h>
#include <vector> 
class Vertex
{
    public:
        Vertex(GLfloat inX, GLfloat inY, GLfloat inZ) : x(inX), y(inY), z(inZ) { }
        GLfloat x, y, z;
};

class Texture
{
    public:
        Texture(GLfloat inU, GLfloat inV) : u(inU), v(inV) { }
        GLfloat u, v;
};

class Normal
{
    public:
        Normal(GLfloat inX, GLfloat inY, GLfloat inZ) : x(inX), y(inY), z(inZ) { }
        GLfloat x, y, z;
};

class Face
{
    public:
        Face(int v[], int t[], int n[]) {
            vIndex[0] = v[0];
            vIndex[1] = v[1];
            vIndex[2] = v[2];
            tIndex[0] = t[0];
            tIndex[1] = t[1];
            tIndex[2] = t[2];
            nIndex[0] = n[0];
            nIndex[1] = n[1];
            nIndex[2] = n[2];
        }
        GLuint vIndex[3], tIndex[3], nIndex[3];
};

class Mesh
{
    public:
        std::vector<Vertex> gVertices;
        std::vector<Texture> gTextures;
        std::vector<Normal> gNormals;
        std::vector<Face> gFaces;

        int VertexDataSize();
        int NormalDataSize();
        int IndexDataSize();

        unsigned int VAO, VBO, EBO;
        void setupMesh();
        void drawMesh();
};

#endif 