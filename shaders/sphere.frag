#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightPos;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diffuse = max(dot(normal, lightDir), 0.0);

    float ambient = 0.2;

    vec3 color = objectColor * (ambient + diffuse);

    FragColor = vec4(color, 1.0);
}