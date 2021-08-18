#version 330 core
out vec4 FragColor;
out vec4 FragColor2;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture1, TexCoord);
	FragColor2 = texture(texture2, TexCoord);
}