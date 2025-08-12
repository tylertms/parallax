#ifndef UTILITY_RANDOM_GLSL
#define UTILITY_RANDOM_GLSL

// https://www.reedbeta.com/blog/hash-functions-for-gpu-rendering/
float rand(inout uint state) {
    state = state * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    word = (word >> 22u) ^ word;
    return word / 4294967295.0;
}

float randNormal(inout uint state) {
    float theta = 6.2831853072 * rand(state);
    float rho = sqrt(-2 * log(rand(state)));
    return rho * cos(theta);
}

vec3 randDir(inout uint state) {
    float x = randNormal(state);
    float y = randNormal(state);
    float z = randNormal(state);
    return normalize(vec3(x, y, z));
}

vec3 randHemisphereDir(vec3 normal, inout uint state) {
    vec3 dir = randDir(state);
    return dir * sign(dot(normal, dir));
}

vec2 randUnitCircle(inout uint state) {
    float angle = rand(state) * 6.2831853072;
    vec2 point = vec2(cos(angle), sin(angle));
    return point * sqrt(rand(state));
}

uint hash32(uint x) {
    x ^= x >> 16;
    x *= 0x7feb352du;
    x ^= x >> 15;
    x *= 0x846ca68bu;
    x ^= x >> 16;
    return x | 1u;
}

#endif
