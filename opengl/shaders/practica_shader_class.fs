#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
//    FragColor = mix(texture(texture1, TexCoord), vec4(ourColor, 1.0),0.5);
    FragColor = texture(texture1,  vec2(TexCoord.x, 1 - TexCoord.y));
//    FragColor = vec4(ourColor, 1.0f);
}
