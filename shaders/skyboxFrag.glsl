#version 330 core
out vec4 FragColor;

in vec3 v_texCoord;

uniform samplerCube cubemap;

void main()
{
        FragColor = texture(cubemap, v_texCoord);
}
