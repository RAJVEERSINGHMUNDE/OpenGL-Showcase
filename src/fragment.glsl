#version 460 core

in vec2 TexCoord;

uniform sampler2D Ourtexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(Ourtexture, TexCoord);
}