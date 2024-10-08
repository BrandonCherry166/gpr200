#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor; 

out vec4 ourColor;
uniform float uTime;
void main()
{
vec3 pos = aPos;
pos.y += (sin(uTime * 6.0 * pos.x) / 8.0) + sin(uTime * 3.0) / 4.0;
			
gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
ourColor = aColor;

}