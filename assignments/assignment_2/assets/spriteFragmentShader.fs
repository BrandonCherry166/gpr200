#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
uniform float uTime;
uniform vec4 uColor = vec4(0.5);
uniform sampler2D texture1;

void main()
{
    vec2 scaledTexCoord = (TexCoord - 0.5) * 4 + 0.5;
    scaledTexCoord = clamp(scaledTexCoord, 0.0, 1.0);
    FragColor = texture(texture1, scaledTexCoord);
}