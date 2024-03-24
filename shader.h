#ifndef _shader_included_
#define _shader_included_
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
#include "parser.h"

using namespace std;

class Shader
{
    public:
        int program;
        GLint modelingMatrixLoc;
        GLint viewingMatrixLoc;
        GLint projectionMatrixLoc;
        GLint eyePosLoc;

        void init(const char* vertexShaderName, const char* fragShaderName)
        {
            // Create the programs

            program = glCreateProgram();

            // Create the shaders for both programs

            GLuint VS = createVS(vertexShaderName);
            GLuint FS = createFS(fragShaderName);

            // Attach the shaders to the programs

            glAttachShader(program, VS);
            glAttachShader(program, FS);

            
            glLinkProgram(program);
            GLint status;
            glGetProgramiv(program, GL_LINK_STATUS, &status);

            if (status != GL_TRUE)
            {
                cout << "Program link failed" << endl;
                exit(-1);
            }

            modelingMatrixLoc = glGetUniformLocation(program, "modelingMatrix");
            viewingMatrixLoc = glGetUniformLocation(program, "viewingMatrix");
            projectionMatrixLoc = glGetUniformLocation(program, "projectionMatrix");
            eyePosLoc = glGetUniformLocation(program, "eyePos");
        };

    private:
        GLuint createVS(const char* shaderName)
        {
            string shaderSource;

            string filename(shaderName);
            if (!Parser::ReadDataFromFile(filename, shaderSource))
            {
                cout << "Cannot find file name: " + filename << endl;
                exit(-1);
            }

            GLint length = shaderSource.length();
            const GLchar* shader = (const GLchar*) shaderSource.c_str();

            GLuint vs = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vs, 1, &shader, &length);
            glCompileShader(vs);

            char output[1024] = {0};
            glGetShaderInfoLog(vs, 1024, &length, output);
            printf("VS compile log: %s\n", output);

            return vs;
        };

        GLuint createFS(const char* shaderName)
        {
            string shaderSource;

            string filename(shaderName);
            if (!Parser::ReadDataFromFile(filename, shaderSource))
            {
                cout << "Cannot find file name: " + filename << endl;
                exit(-1);
            }

            GLint length = shaderSource.length();
            const GLchar* shader = (const GLchar*) shaderSource.c_str();

            GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fs, 1, &shader, &length);
            glCompileShader(fs);

            char output[1024] = {0};
            glGetShaderInfoLog(fs, 1024, &length, output);
            printf("FS compile log: %s\n", output);

            return fs;
        };
};

#endif 