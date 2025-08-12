#version 460
#extension GL_EXT_ray_tracing : require
#extension GL_GOOGLE_include_directive : require

#include "../utility/payload.glsl"

layout(location = 0) rayPayloadInEXT HitData hit;

void main() {
    hit.didHit = false;
}
