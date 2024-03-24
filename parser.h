#ifndef _parser_included_
#define _parser_included_
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <vector>
#include "mesh.h"

using namespace std;

class Parser
{
    public:
        static bool ParseObj(const string& fileName, Mesh& mesh)
        {
            fstream myfile;

            // Open the input 
            myfile.open(fileName.c_str(), std::ios::in);

            if (myfile.is_open())
            {
                string curLine;

                while (getline(myfile, curLine))
                {
                    stringstream str(curLine);
                    GLfloat c1, c2, c3;
                    GLuint index[9];
                    string tmp;

                    if (curLine.length() >= 2)
                    {
                        if (curLine[0] == 'v')
                        {
                            if (curLine[1] == 't') // texture
                            {
                                str >> tmp; // consume "vt"
                                str >> c1 >> c2;
                                mesh.gTextures.push_back(Texture(c1, c2));
                            }
                            else if (curLine[1] == 'n') // normal
                            {
                                str >> tmp; // consume "vn"
                                str >> c1 >> c2 >> c3;
                                mesh.gNormals.push_back(Normal(c1, c2, c3));
                            }
                            else // vertex
                            {
                                str >> tmp; // consume "v"
                                str >> c1 >> c2 >> c3;
                                mesh.gVertices.push_back(Vertex(c1, c2, c3));
                            }
                        }
                        else if (curLine[0] == 'f') // face
                        {
                            str >> tmp; // consume "f"
                            char c;
                            int vIndex[3],  nIndex[3], tIndex[3];
                            str >> vIndex[0]; str >> c >> c; // consume "//"
                            str >> nIndex[0]; 
                            str >> vIndex[1]; str >> c >> c; // consume "//"
                            str >> nIndex[1]; 
                            str >> vIndex[2]; str >> c >> c; // consume "//"
                            str >> nIndex[2]; 

                            assert(vIndex[0] == nIndex[0] &&
                                vIndex[1] == nIndex[1] &&
                                vIndex[2] == nIndex[2]); // a limitation for now

                            // make indices start from 0
                            for (int c = 0; c < 3; ++c)
                            {
                                vIndex[c] -= 1;
                                nIndex[c] -= 1;
                                tIndex[c] -= 1;
                            }

                            mesh.gFaces.push_back(Face(vIndex, tIndex, nIndex));
                        }
                        else
                        {
                            cout << "Ignoring unidentified line in obj file: " << curLine << endl;
                        }
                    }

                    //data += curLine;
                    if (!myfile.eof())
                    {
                        //data += "\n";
                    }
                }

                myfile.close();
            }
            else
            {
                return false;
            }

            /*
            for (int i = 0; i < gVertices.size(); ++i)
            {
                Vector3 n;

                for (int j = 0; j < gFaces.size(); ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        if (gFaces[j].vIndex[k] == i)
                        {
                            // face j contains vertex i
                            Vector3 a(gVertices[gFaces[j].vIndex[0]].x, 
                                    gVertices[gFaces[j].vIndex[0]].y,
                                    gVertices[gFaces[j].vIndex[0]].z);

                            Vector3 b(gVertices[gFaces[j].vIndex[1]].x, 
                                    gVertices[gFaces[j].vIndex[1]].y,
                                    gVertices[gFaces[j].vIndex[1]].z);

                            Vector3 c(gVertices[gFaces[j].vIndex[2]].x, 
                                    gVertices[gFaces[j].vIndex[2]].y,
                                    gVertices[gFaces[j].vIndex[2]].z);

                            Vector3 ab = b - a;
                            Vector3 ac = c - a;
                            Vector3 normalFromThisFace = (ab.cross(ac)).getNormalized();
                            n += normalFromThisFace;
                        }

                    }
                }

                n.normalize();

                gNormals.push_back(Normal(n.x, n.y, n.z));
            }
            */

            assert(mesh.gVertices.size() == mesh.gNormals.size());

            return true;
        }

        static bool ReadDataFromFile(const std::string& fileName, std::string& data)
        {
            fstream myfile;
            // Open the input 
            myfile.open(fileName.c_str(), std::ios::in);

            if (myfile.is_open())
            {
                string curLine;

                while (getline(myfile, curLine))
                {
                    data += curLine;
                    if (!myfile.eof())
                    {
                        data += "\n";
                    }
                }

                myfile.close();
            }
            else
            {
                return false;
            }

            return true;
        }
};
#endif 