#ifndef UTILITY_PAYLOAD_GLSL
#define UTILITY_PAYLOAD_GLSL

struct Vertex {
    vec3 position;
    vec3 normal;
};

struct Material {
    vec3 color;
    float roughness;
    vec3 emissiveColor;
    float emissiveIntensity;
};

struct MeshInfo {
    vec3 position;
    uint vertexBase;
    vec3 rotation;
    uint vertexCount;
    vec3 scale;
    uint indexBase;
    uint indexCount;
    uint materialIndex;
};

struct Ray {
    vec3 origin;
    vec3 direction;
    uint depth;
};

struct HitData {
    vec3 position;
    vec3 normal;
    bool didHit;
    uint materialIndex;
};

#endif
