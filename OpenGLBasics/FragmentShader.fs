#version 450 core

in vec3 fragmentColor;

out vec4 color;

uniform float currentTime;

void main()
{
	vec3 changingColor = fragmentColor * abs(sin(currentTime));
	color = vec4(changingColor, 1.0);
}