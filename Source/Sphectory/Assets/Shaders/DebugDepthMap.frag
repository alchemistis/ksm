#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D depthMap;
uniform float nearPlane;
uniform float farPlane;

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0);
}

// required when using a perspective projection matrix
// FragColor = vec4(vec3(LinearizeDepth(depthValue) / farPlane), 1.0); // perspective
//float LinearizeDepth(float depth);
/*
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}
*/
