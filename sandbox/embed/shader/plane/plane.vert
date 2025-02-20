#version 450

layout(set = 0, binding = 0) uniform VP {
    mat4 view;
    mat4 projection;
} vp;

layout(location = 1) out vec3 nearPoint;
layout(location = 2) out vec3 farPoint;
layout(location = 3) out mat4 fragView;
layout(location = 7) out mat4 fragProj;


vec3 gridPlane[6] = vec3[] (
    vec3( 1,  1, 0), vec3(-1, -1, 0), vec3(-1,  1, 0),
    vec3(-1, -1, 0), vec3( 1,  1, 0), vec3( 1, -1, 0)
);

vec3 unproject(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    vec3 p = gridPlane[gl_VertexIndex].xyz;

    nearPoint = unproject(p.x, p.y, 0.0, vp.view, vp.projection).xyz;
    farPoint = unproject(p.x, p.y, 1.0, vp.view, vp.projection).xyz;
    fragView = vp.view;
    fragProj = vp.projection;

    gl_Position = vec4(p, 1.0);
}