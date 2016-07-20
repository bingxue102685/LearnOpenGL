#version 330 core

uniform sampler2D texture_diffuse1;  //漫反射的颜色为纹理的颜色
uniform sampler2D texture_specular1; //


in vec2 TexCoords; //纹理坐标
out vec4 color;

void main()
{
    //color = vec4(vec3(1.0f, 1.0f, 1.0f), 1.0f);
    color = vec4(texture(texture_diffuse1, TexCoords));
}
