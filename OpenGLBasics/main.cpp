#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"


GLuint program;

void render();
void init();


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Basics");

	glClearColor(1.0, 0.0, 0.0, 1.0); // Clear Window

	glewInit();
	init();

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	

	// Register callbacks
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); // clear red

	glUseProgram(program);
	
	glDrawArrays(GL_TRIANGLES, 0, 3); // GL_POINTS, GL_LINES

	glUseProgram(0);

	glutSwapBuffers();

}

void init()
{
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("VertexShader.vs", "FragmentShader.fs");
}