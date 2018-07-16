#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <map>


class ShaderLoader
{
	// Functions
	private:

		std::string ReadShader(char *filename);
		GLuint CreateShader(GLenum shaderType,
							std::string source,
							char* shaderName);
		// Save the shader --> Add it to the savedShaders
		void SaveShader(char* shaderName, GLuint shaderType);
		// LoadShader --> Check if the shader with the same name exists
		GLuint ProgramExists(char *filename);
		GLuint VertexShaderExist(char *filename);
		GLuint FragmentShaderExist(char *filename);

	public:
		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgram(char* VertexShaderFilename,
							char* FragmentShaderFilename);

	// Variables
	private:
		std::map<char*, GLuint> savedVertexShaders;
		std::map<char*, GLuint> savedFragmentShaders;
		std::map<char*, GLuint> savedPrograms;


};
