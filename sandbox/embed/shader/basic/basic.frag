#version 450

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragCoord;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform sampler2D textureSampler;

void main() {
    outColor = texture(textureSampler, fragCoord) * fragColor;
}
