#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT {
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} vs_out;

out PLANET {
    vec4 originalPos;
    uint layer;
} vs_planet;

#define SELECTION_MAX 60
uniform int selectedVertices[SELECTION_MAX];

void main() {

    vs_planet.originalPos = projection * view * model * vec4(aPos, 1.0);

    bool selected = false;
    for (int i=0; i<SELECTION_MAX; ++i)
        if (gl_VertexID == selectedVertices[i])
            selected = true;

    if (selected) {
        gl_Position = projection * view * model * vec4(aPos * 0.8, 1.0);
        vs_planet.layer = 1;
        vs_out.color = vec3(1.0, 0.0, 0.0);
    } else {
        gl_Position = vs_planet.originalPos;
        vs_planet.layer = 0;
        vs_out.color = aColor;
    }

    vs_out.normal = aNormal;
    vs_out.texCoord = aTexCoord;
}
