#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;

out vec4 FragPos;
out vec4 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position=position;
    gl_Normal=normal;
}