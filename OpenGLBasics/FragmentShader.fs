#version 450 core

in vec3 fragmentColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D tex;

void main()
{
	vec3 changingColor = fragmentColor * abs(sin(currentTime));
    color = texture(tex, fragTexCoord);
	// color = vec4(changingColor, 1.0);
}