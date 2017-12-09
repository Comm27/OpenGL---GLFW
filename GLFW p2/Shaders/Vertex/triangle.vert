#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform float offset;
out vec3 myColor;

vec3 newPos;
void main()
{
    newPos = aPos + offset;
    gl_Position = vec4(newPos, 1.0);
    myColor = newPos;
}