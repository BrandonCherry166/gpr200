#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor; 
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 TexCoord;

uniform float uTime;
void main()
{

vec3 pos = aPos;
pos.y += (sin(uTime * 6.0 * pos.x) / 18.0) + sin(uTime * 3.0) / 6.0;	
gl_Position = vec4(pos.x, pos.y, pos.z, 0.5);
ourColor = aColor;
TexCoord = aTexCoord;
}