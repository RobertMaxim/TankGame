#version 330 core

in vec3 position;
in vec3 color;
in vec2 textureVec;
in vec3 Normal;

out vec4 fragColor;

uniform float mixValue;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    fragColor=mix(texture(texture1, textureVec), texture(texture2, textureVec), mixValue);
}