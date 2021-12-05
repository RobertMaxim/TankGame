#version 330 core
layout(location = 0) in vec3 aPos;
layout(location=1) in vec3 Color;
layout(location=2) in vec2 aTex;
layout(location = 3) in vec3 normal;

out vec3 position;
out vec3 color;
out vec2 textureVec;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    position=aPos;
    color=Color;
    textureVec=aTex;
    Normal=normal;
    gl_Position=projection*view*model*vec4(aPos,1.f);
}