#version 460
#extension GL_EXT_ray_tracing : require
#extension GL_GOOGLE_include_directive : require

#include "../utility/random.glsl"
#include "../utility/payload.glsl"

layout(set = 0, binding = 2, std430) readonly buffer VertexBuffer {
    Vertex vertices[];
} vertexBuffer;

layout(set = 0, binding = 3, std430) readonly buffer IndexBuffer {
    uint indices[];
} indexBuffer;

layout(set = 0, binding = 5, std430) readonly buffer MeshInfoBuffer {
    MeshInfo infos[];
} meshInfo;

layout(location = 0) rayPayloadInEXT HitData hit;
hitAttributeEXT vec2 barycentrics;

void main() {
    uint instance = gl_InstanceCustomIndexEXT;
    MeshInfo info = meshInfo.infos[instance];

    uint primitiveID = info.indexBase + gl_PrimitiveID * 3;
    uint vertexBase = info.vertexBase;

    uint idx0 = indexBuffer.indices[primitiveID + 0] + vertexBase;
    uint idx1 = indexBuffer.indices[primitiveID + 1] + vertexBase;
    uint idx2 = indexBuffer.indices[primitiveID + 2] + vertexBase;

    Vertex v0 = vertexBuffer.vertices[idx0];
    Vertex v1 = vertexBuffer.vertices[idx1];
    Vertex v2 = vertexBuffer.vertices[idx2];

    float u = barycentrics.x;
    float v = barycentrics.y;
    float w = 1.0 - u - v;

    vec3 objPos = v0.position * w + v1.position * u + v2.position * v;
    vec3 objNrm = normalize(v0.normal * w + v1.normal * u + v2.normal * v);

    vec3 worldPos = (gl_ObjectToWorldEXT * vec4(objPos, 1.0)).xyz;
    vec3 worldNrm = normalize(transpose(mat3(gl_WorldToObjectEXT)) * objNrm);

    hit.position = worldPos;
    hit.normal = worldNrm;
    hit.materialIndex = info.materialIndex;
    hit.didHit = true;
}
