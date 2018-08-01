#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragmentColor;
out vec2 fragTexCoord;

void main(void)
{                                                                 
	gl_Position = vec4(position, 1.0);    
	fragmentColor = color;
	fragTexCoord = texCoord;
}