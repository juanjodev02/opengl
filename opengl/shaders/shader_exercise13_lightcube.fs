#version 330 core
out vec4 FragColor;

uniform vec4 ligthColor;

void main()
{
    FragColor = ligthColor; // set alle 4 vector values to 1.0
}
