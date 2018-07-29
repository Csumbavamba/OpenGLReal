#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"


GLuint program, program2;
GLuint VBO; // Vertex buffer Object
GLuint VAO; // vertex array object
GLfloat currentTime;
GLfloat vertices[] = {
	// position			// color
	0.0f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f, // Top
	0.5f,  0.0f, 0.0f,	0.0f, 1.0f, 0.0f, // Right
	-0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f, // Left

	// position			// color
	0.0f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f, // Bottom
	-0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 1.0f, // Left
	0.5f,  0.0f, 0.0f,	0.0f, 1.0f, 0.0f, // Right

};

void Render();
void Initialise();
void CalculateTime();
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
	glBindVertexArray(VAO);
	
	glDrawArrays(GL_TRIANGLES, 0, 6); // GL_POINTS, GL_LINES

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
		6 * sizeof(GLfloat),
		(GLvoid*)0);
	

	// Connect second attribute pointer for color
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),				// Stride of the single vertex (pos + color)
		(GLvoid*)(3 * sizeof(GLfloat)));	// offset from beginning of Vertex

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

}

void Update()
{
	// Update game information
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime / 1000.0f; // Now it's seconds instead of miliseconds

	glutPostRedisplay();
}
