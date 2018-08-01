#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"


GLuint program, program2;
GLuint VBO; // Vertex buffer Object
GLuint VAO; // vertex array object
GLuint EBO; // Element Buffer Object
GLuint texture;
std::string filePath = "Rayman.jpg";

GLfloat currentTime;
GLfloat vertices[] = {
	// position			// color			// Tex Coords
	-0.5f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,	// Top Left
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	// Bottom Left
	 0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// Bottom Right
	 0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f	// Top Right

};

GLuint indices[] = {
	0, 1, 3, // First Triangle
	2, 3, 1  // Second Triangle
};

void Render();
void Initialise();
void Update();


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Basics");

	glClearColor(1.0, 0.0, 0.0, 1.0); // Clear Window

	glewInit();
	Initialise();


	// Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutMainLoop();
	return 0;
}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); // clear red

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glBindVertexArray(VAO);
	
	// glDrawArrays(GL_TRIANGLES, 0, 6); // GL_POINTS, GL_LINES
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime"); 
	glUniform1f(currentTimeLocation, currentTime);

	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
	

}

void Initialise()
{
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
	program2 = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");

	// create vertex buffer and array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Load data
	glBufferData (
		GL_ARRAY_BUFFER, 
		sizeof(vertices), 
		vertices, 
		GL_STATIC_DRAW);

	

	// Connect vertex buffer with array
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	

	// Connect second attribute pointer for color
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride of the single vertex (pos + color)
		(GLvoid*)(3 * sizeof(GLfloat)));	// offset from beginning of Vertex

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6* sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// This has to happen after enabling
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW);


	// Do Culling
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	// Texture creation
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, channels;
	unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Update()
{
	// Update game information
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000.0f; // Now it's seconds instead of miliseconds

	glutPostRedisplay();
}
