#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    color = mix(texture(ourTexture1, TexCoords), texture(ourTexture2, TexCoords), 0.2);
}