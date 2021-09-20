#version 330 core
out vec4 FragColor;
in vec3 myColor;
uniform float myValue;

void main()
{
   // FragColor = vec4(0.866f, 0.537f, 0.211f, 1.0f);
   FragColor = vec4(myColor, 1.0) * myValue;
}